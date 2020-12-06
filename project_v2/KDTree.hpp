/*
    Raymond Turrisi, Alfred Timperley, Brennan Richards
    KDTree templated class
    Can work with any class which has an attribute "coords" or which has inherited the KDTree_Key. See dataStructs.hpp for example
*/

#ifndef KDTREE_CLASS
#define KDTREE_CLASS

//Required Libraries
#include "Node.hpp"
#include <fstream>
#include <string>
#include <unistd.h>
#include <cmath>

//templated class
template <class t>
class KDTree {
    private:
        #define DBL_MAX 10000000000000000000.000000000000000000 /* max value */
        //#define DBL_MAX 1.7976931348623158*pow(10,308) /* max value */
    public:
        Node<t>* head;
        int nodes = 0;
        int height = 0;
        int dimensions = 0;

        //constructors
        KDTree<t>(unsigned int _dimensions);

        KDTree<t>(t data);

        KDTree<t>(std::vector<t> vector_of_structs);

        //insert
        void insert(t data); /*
        {
            Inserts and element on an existing tree and is called in implementation level
            Tree.insert(Template class);

            Calls void insert_r(Node<t> *node, t data, unsigned int depth_r) recursively to place node in correct location based off of "coords" attribute.

        }
        */
        Node<t>* insert_r(Node<t> *node, t data, unsigned int depth_r);

        //remove
        void remove_node(Node<t>* node);

        //nearest neighbor
        double dist_from_to(t data, Node<t>* node);

        double dist_from_to(std::vector<double> local_coords, Node<t>* node);

        //search for element
        bool search_for_element(t data);

        //search for element
        bool search_for_element_r(Node<t>* node, t data, unsigned int depth_r);

        //from class
        t nearest_neighbor(t data);

        //from class
        t nearest_neighbor(t data, double &best_distance);

        //from local coords
        t nearest_neighbor(std::vector<double> local_coords);

        //from local coords
        t nearest_neighbor(std::vector<double> local_coords, double &best_distance);

        //from local coords
        void nearest_neighbor_r(Node<t>* node, t &data, t &result, unsigned int depth_r, double &best_dist);


        //destroy tree, public
        void destroy();

        //destroy tree recursive, local
        void destroy_r(Node<t>* node);

        //post-order
        void postOrder();
        void postOrder_r(Node<t>* node);

        //inorder
        void inOrder();
        void inOrder_r(Node<t>* node);

        //preorder
        void preOrder();
        void preOrder_r(Node<t>* node);

        //output .dot file formatting
        void dotOut_r(Node<t>* node, std::ofstream &ofs, unsigned int depth_r);
        void dotOut(std::string fname_out);
        std::string colors_678436859937850983[147] = { "aquamarine", "bisque", "black", "blue", "blueviolet", "brown", "burlywood", "cadetblue", "chartreuse", "chocolate", "coral", "cornflowerblue", "crimson", "cyan", "darkgoldenrod", "darkgreen", "darkgrey", "darkkhaki", "darkolivegreen", "darkorange", "darkorchid", "darksalmon", "darkseagreen", "darkslateblue", "darkslategray", "darkturquoise", "darkviolet", "deeppink", "deepskyblue", "dimgray", "dimgrey", "dodgerblue", "firebrick", "forestgreen", "fuchsia", "gainsboro", "gold", "goldenrod", "gray", "grey", "green", "greenyellow", "honeydew", "hotpink", "indianred", "indigo", "ivory", "khaki", "lavender", "lavenderblush", "lawngreen", "lemonchiffon", "lightblue", "lightcoral", "lightcyan", "lightgoldenrodyellow", "lightgray", "lightgreen", "lightgrey", "lightpink", "lightsalmon", "lightseagreen", "lightskyblue", "lightslategray", "lightslategrey", "lightsteelblue", "lightyellow", "lime", "limegreen", "linen", "magenta", "maroon", "mediumaquamarine", "mediumblue", "mediumorchid", "mediumpurple", "mediumseagreen", "mediumslateblue", "mediumspringgreen", "mediumturquoise", "mediumvioletred", "midnightblue", "mintcream", "mistyrose", "moccasin", "navajowhite", "navy", "oldlace", "olive", "olivedrab", "orange", "orangered", "orchid", "palegoldenrod", "palegreen", "paleturquoise", "palevioletred", "papayawhip", "peachpuff", "peru", "pink", "plum", "powderblue", "purple", "red", "rosybrown", "royalblue", "saddlebrown", "salmon", "sandybrown", "seagreen", "seashell", "sienna", "silver", "skyblue", "slateblue", "slategray", "slategrey", "snow", "springgreen", "steelblue", "tan", "teal", "thistle", "tomato", "turquoise", "violet", "wheat", "white", "whitesmoke", "yellow", "yellowgreen" };
        std::string arb_dims_678436859937850983[9] = {"x","y","z","wx","wy","wz","nx","ny","nz"}; //up to nine dimensions, but this ain't string theory
};


//constructor, need to start with the number of dimensions for tree
template <typename t>
KDTree<t>::KDTree(unsigned int _dimensions) {
    //this->head = new Node<t>();
    this->head = nullptr;
    this->dimensions = _dimensions;
}

//constructor with first struct
template <typename t>
KDTree<t>::KDTree(t data) {
    //for insantiating a new KDtree
    this->head = new Node<t>(data);
    this->dimensions = data.coords.size();
    this->nodes++;
    this->height++;
}


//constructor from a vector
template <typename t>
KDTree<t>::KDTree(std::vector<t> vector_of_structs) {

}

//destroy recursively, called from within class
template <typename t>
void KDTree<t>::destroy_r(Node<t> *node) {
    if(!node) {
        return;
    }
    this->destroy_r(node->left_child);
    this->destroy_r(node->right_child);
    delete node->left_child;
    delete node->right_child;
}

//destroy tree, called from implementation
template <typename t>
void KDTree<t>::destroy() {
    this->destroy_r(this->head);
    delete this->head;
    this->head = nullptr;
    this->height = 0;
    this->nodes = 0;
}

//insert recursively, called from within
template <typename t>
Node<t>* KDTree<t>::insert_r(Node<t>* node, t data, unsigned int depth_r) {
    if(depth_r+1 > this->height) {
        this->height = depth_r+1;
    }
    //compare current index as discriminator = depth/dimensions
    int i = depth_r%(this->dimensions);

    if(node->struct_of_data.coords[i] < data.coords[i]) {
        if(!node->right_child) {
            this->nodes++;
            node->right_child = new Node<t>(data);
            return node->right_child;
        }
        insert_r(node->right_child, data, depth_r+1);
    } else {
        if(!node->left_child) {
            this-nodes++;
            node->left_child = new Node<t>(data);
            return node->left_child;
        }
        insert_r(node->left_child, data, depth_r+1);
    }

    return node;
}

//insert template class of data, called from within implementation
template <typename t>
void KDTree<t>::insert(t data) {
    if(!this->head) {
        this->head = new Node<t>(data);
        this->nodes++;
        this->height++;
        return;
    } else {
        insert_r(this->head, data, 0);
    }
}

//remove
template <typename t>
void KDTree<t>::remove_node(Node<t>* node) {

}

//nearest neighbor
    //from class of data
template <typename t>
double KDTree<t>::dist_from_to(t data, Node<t>* node) {
    double sum = 0.00000;
    double a_dim1 = 0.00000, a_dim2 = 0.00000;
    for(int i = 0; i < data.coords.size(); i++) {
        a_dim1 = data.coords[i];
        a_dim2 = node->struct_of_data.coords[i];
        a_dim1 -= a_dim2;
        sum+=pow(a_dim1,2);
    }

    return sqrt(sum);
}

    //from local coords
template <typename t>
double KDTree<t>::dist_from_to(std::vector<double> local_coords, Node<t>* node) {
    double sum = 0.00000;
    double a_dim1 = 0.00000, a_dim2 = 0.00000;
    for(int i = 0; i < local_coords.size(); i++) {
        a_dim1 = local_coords[i];
        a_dim2 = node->struct_of_data.coords[i];
        a_dim1 -= a_dim2;
        sum+=pow(a_dim1,2);
    }

    return sqrt(sum);
}

//search for element
template <typename t>
bool KDTree<t>::search_for_element_r(Node<t>* node, t data, unsigned int depth_r) {
    if(!node) {
        return false;
    }
    if(data == node->struct_of_data) {
        return true;
    }
    //compare current index as discriminator = depth/dimensions
    int i = depth_r%(this->dimensions);

    if(data.coords[i] < node->struct_of_data.coords[i]) {
        return search_for_element_r(node->left_child, data, depth_r+1);;
    } else {
        return search_for_element_r(node->right_child, data, depth_r+1);;
    }
}

//search for element
template <typename t>
bool KDTree<t>::search_for_element(t data) {
    return search_for_element_r(this->head, data, 0);
}


//from class
template <typename t>
void KDTree<t>::nearest_neighbor_r(Node<t>* node, t &data, t &result, unsigned int depth_r, double &best_dist) {
    //std::cout << "here1\n";
    //compare current index as discriminator = depth/dimensions
    //std::cout << best_dist << std::endl;

    int i = depth_r%(this->dimensions);

    double dist = dist_from_to(data, node);
    //std::cout << dist << std::endl << std::endl;
    if(node->struct_of_data.coords[i] < data.coords[i]) {

        if(!node->right_child) {

            if((best_dist > dist) && (node->struct_of_data != data)) {
                //
                //std::cout << "yes\n";
                best_dist = dist;
                result = node->struct_of_data;
            }

            return;
        }

        nearest_neighbor_r(node->right_child, data, result, depth_r+1, best_dist);

    } else {

        if(!node->left_child) {

            if(best_dist >= dist && node->struct_of_data != data) {
                best_dist = dist;
                result = node->struct_of_data;

            }

            return;
        }

        nearest_neighbor_r(node->left_child, data, result, depth_r+1, best_dist);
    }

    if(best_dist > dist && node->struct_of_data != data) {
        best_dist = dist;
        result = node->struct_of_data;
    }
    return;
}

//from class
template <typename t>
t KDTree<t>::nearest_neighbor(t data) {
    //Starting with the root node, the algorithm moves down the tree recursively, in the same way that it would if the search point were being inserted (i.e. it goes left or right depending on whether the point is lesser than or greater than the current node in the split dimension).
    t result(this->dimensions);
    double best_dist = DBL_MAX; // << literally the worst case
    nearest_neighbor_r(this->head, data, result, 0, best_dist);
    //std::cout << best_dist*88 << std::endl; //to miles
    return result;
}

template <typename t>
t KDTree<t>::nearest_neighbor(t data, double &best_dist) {
    //Starting with the root node, the algorithm moves down the tree recursively, in the same way that it would if the search point were being inserted (i.e. it goes left or right depending on whether the point is lesser than or greater than the current node in the split dimension).
    t result(this->dimensions);
    nearest_neighbor_r(this->head, data, result, 0, best_dist);
    //std::cout << best_dist*88 << std::endl; //to miles
    return result;
}

//from class
template <typename t>
t KDTree<t>::nearest_neighbor(std::vector<double> local_coords) {
    //Starting with the root node, the algorithm moves down the tree recursively, in the same way that it would if the search point were being inserted (i.e. it goes left or right depending on whether the point is lesser than or greater than the current node in the split dimension).
    t result;
    t data;
    for(int i = 0; i <local_coords.size(); i++){
        data.coords.push_back(local_coords[i]);
    }
    double best_dist = DBL_MAX; // << literally the worst case
    nearest_neighbor_r(this->head, data, result, 0, best_dist);
    return result;
}

//from class
template <typename t>
t KDTree<t>::nearest_neighbor(std::vector<double> local_coords, double &best_dist) {
    //Starting with the root node, the algorithm moves down the tree recursively, in the same way that it would if the search point were being inserted (i.e. it goes left or right depending on whether the point is lesser than or greater than the current node in the split dimension).
    t result;
    t data;
    for(int i = 0; i <local_coords.size(); i++){
        data.coords.push_back(local_coords[i]);
    }
    nearest_neighbor_r(this->head, data, result, 0, best_dist);
    return result;
}

//post-order, called from program
template <typename t>
void KDTree<t>::postOrder() {
    postOrder_r(this->head);
}

//post-order, called from program
template <typename t>
void KDTree<t>::inOrder() {
    inOrder_r(this->head);
}
//post-order, called from program
template <typename t>
void KDTree<t>::preOrder() {
    preOrder_r(this->head);
}

//post-order, recursive in class
template <typename t>
void KDTree<t>::postOrder_r(Node<t>* node) {
    if(!node) return;
    postOrder_r(node->left_child);
    postOrder_r(node->right_child);
    std::cout << "<"<< node->struct_of_data.name << ": "<< node->struct_of_data.coords[0] << "," << node->struct_of_data.coords[1] << ">\n";
    return;
}

//inorder, recursive in class
template <typename t>
void KDTree<t>::inOrder_r(Node<t>* node) {
    if(!node) return;
    inOrder_r(node->left_child);
    std::cout << "<"<< node->struct_of_data.name << ": "<< node->struct_of_data.coords[0] << "," << node->struct_of_data.coords[1] << ">\n";
    inOrder_r(node->right_child);
    return;
}
//preorder, recursive in class
template <typename t>
void KDTree<t>::preOrder_r(Node<t>* node) {
    if(!node) return;
    std::cout << "<"<< node->struct_of_data.name << ": "<< node->struct_of_data.coords[0] << "," << node->struct_of_data.coords[1] << ">\n";
    preOrder_r(node->left_child);
    preOrder_r(node->right_child);
    return;
}

//prints pretty dot formatting, recursive for use in class called by public member function
template <typename t>
void KDTree<t>::dotOut_r(Node<t>* node, std::ofstream &ofs, unsigned int depth_r) {

    if(!node) return;
    //uses a post order traversal but doesn't make a difference in how the graph is displayed
    dotOut_r(node->left_child, ofs, depth_r+1);
    dotOut_r(node->right_child, ofs, depth_r+1);
    if(node->left_child) {
        //from 1
        ofs << "\t\t<"<< node->struct_of_data.name << ": "<< node->struct_of_data.coords[0] << "," << node->struct_of_data.coords[1] << "> ->";

        //to 1
        ofs << "\t<"<< node->left_child->struct_of_data.name << ": "<< node->left_child->struct_of_data.coords[0] << "," << node->left_child->struct_of_data.coords[1] << ">";
        ofs << "[color=\""<< colors_678436859937850983[depth_r] << "\"]\n";

    }
    if(node->right_child) {
        //from 2
        ofs << "\t\t<"<< node->struct_of_data.name << ": "<< node->struct_of_data.coords[0] << "," << node->struct_of_data.coords[1] << "> ->";

        //to 2
        ofs << "\t<"<< node->right_child->struct_of_data.name << ": "<< node->right_child->struct_of_data.coords[0] << "," << node->right_child->struct_of_data.coords[1] << ">";
        ofs << "[color=\""<< colors_678436859937850983[depth_r] << "\"]\n";

    }
    return;
}

//prints pretty dot formatting, for use on class object from implemented program
template <typename t>
void KDTree<t>::dotOut(std::string fname_out) {
    std::ofstream ofs;
    std::string fn = "recent_graph.dot";
    ofs.open(fn);
    std::cout << "in dot out " << fname_out << std::endl;
    std::cout << this->head->struct_of_data.type << std::endl;
    ofs << "digraph G {\n";
    std::string dimDescriber;
    ofs << "\tsubgraph cluster_0 {\n\t\t";
    for(int i = 0; i <= this->height; i++) {
        dimDescriber = arb_dims_678436859937850983[i%dimensions];
        if(i == 0) {
            ofs <<"<root: " << dimDescriber << "> -> ";
        } else if(i == (this->height)) {
            ofs << "<" << i << ":" << dimDescriber << ">;\n\t}\n";
        } else {
            ofs << "<" << i << ":" << dimDescriber << "> -> ";
        }
    }

    ofs << "\tsubgraph cluster_1 {\n";
    dotOut_r(this->head, ofs, 0);
    ofs << "\t\n}";
    ofs << "}\n";

    ofs.close();

    std::string newfn = "filename.png";
    std::string cmd = "dot -Tsvg -o " + fname_out + " " + fn;
    const char *cmd2 = cmd.c_str();
    system(cmd2);
    //sleep(5);
    cmd = "rm " + fn;
    cmd2 = cmd.c_str();
    //system(cmd2);
    return;
}


#endif