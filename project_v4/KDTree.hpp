/*
    Raymond Turrisi, Alfred Timperley, Brennan Richards
    KDTree templated class
    Can work with any class which has an attribute "coords" or which has inherited the KDTree_Key. See dataStructs.hpp for example
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    <THIS FILE>
    Templated class, where class declaration is at the top of the file, and the definitions are at the bottom of this file - must be kept together to avoid conflicts in templated classes

    <KDTree.hpp>
        /*.hpp
        /*.cpp
    </KDTree.hpp>

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
#define DBL_MAXT 10000000000000000000.000000000000000000 /*a max value */

template <class t>
class KDTree {
    public:
        Node<t>* head;
        int nodes = 0;
        int height = 0;
        int dimensions = 0;

        //constructors
        KDTree<t>(unsigned int _dimensions);/*
        {
            Main constructor if class is declared without any other arguments, at tree declaration the number of dimensions must be known which is used by all other functions
            KDTree<t> tree(int);
            1. Sets head to a nullptr
            2. Passes the number of dimensions to the class
        }
        */

        KDTree<t>(t data);/*
        {
            Constructor with one argument of passed class
            KDTree<t> tree(data);
            1. Sets head to a new Node<t>
            2. Gets number of dimensions from checking the size of the coordinate vectors, which is either default in the passed class as "std::vector<double>coords" or the same argument passed from the KDTree_Key class
            3. Adds to number of tracked nodes
            4. Adds to the height

        }
        */

        KDTree<t>(std::vector<t> vector_of_structs);/*
        {
            Constructor when passed a vector of template classes
            1. Gets number of dimensions from vector_of_structs[0].std::vector<double>coords.size()
            2. Iterates for the length of the vector and inserts template classes to the tree with the insert function

        }
        */

        //insert
        void insert(t data); /*
        {
            Calls private recursive helper function (below)
            Inserts and element on an existing tree and is called in implementation level
            KDTree tree(int);

            1. tree.insert(Template class);
                Calls void insert_r(Node<t> *node, t data, unsigned int depth_r) recursively to place node in correct location based off of "std::vector<double>coords" attribute.

        }
        */

        //remove
        void remove_node(Node<t>* node);/*
        {


        }
        */

        //nearest neighbor
        double dist_from_to(t data, Node<t>* node);/*
        {
            For nearest neighbor algorithms
            Finds euclidian distance for all dimensions in passed parameters by
            for i in size while i < dimensions
                a_dim1 = data.coords[i]
                a_dim2 = node->struct_of_data.coords[i]
                a_dim2 -= a_dim1
                sum+=pow(a_dim2,2)

            return sqrt(sum)
        }
        */

        double dist_from_to(std::vector<double> local_coords, Node<t>* node);/*
        {
            For nearest neighbor algorithms
            Finds euclidian distance for all dimensions in passed parameters by
            for i in size while i < dimensions
                a_dim1 = data.coords[i]
                a_dim2 = node->struct_of_data.coords[i]
                a_dim2 -= a_dim1
                sum+=pow(a_dim2,2)

            return sqrt(sum)

        }
        */

        //search for element
        bool search_for_element(t data);/*
        {
            Calls private recursive helper function (below)

            Checks if a passed class exists in a KDTree
            **Compares class entirely, therefore passed class must have an overloaded comparison operator to check if all attributes are equal

            Takes parameters and calls recursive search function
        }
        */


        //from class object
        t nearest_neighbor(t data);/*
        {   Calls private recursive helper function (below)

            Looks for the nearest neighbor of a passed class
            Calls helper function to recursively iterate through all the elements
            Returns a copy of the class
        }
        */

        //from class object
        t nearest_neighbor(t data, double &best_distance);/*
        {Calls private recursive helper function (below)

            Looks for the nearest neighbor of a passed class, with an additional argument if one would like to return what the distance between the two neighbors are
            Calls helper function to recursively iterate through all the elements
            Returns a copy of the class

        }
        */


        //from local coords
        t nearest_neighbor(std::vector<double> local_coords);/*
        {Calls private recursive helper function (below)

            Looks for the nearest neighbor of passed coordinates
            Creates a blank Class of t with coordinates, and calls the same recursive function as the other NN functions
            Calls helper function to recursively iterate through all the elements
            Returns a instantiated blank class becomes the result of the passed argument

        }
        */

        //from local coords
        t nearest_neighbor(std::vector<double> local_coords, double &best_distance);/*
        {Calls private recursive helper function (below)

            Looks for the nearest neighbor of passed coordinates, with an additional argument if one would like to return what the distance between the two neighbors are
            Creates a blank Class of t with coordinates, and calls the same recursive function as the other NN functions
            Calls helper function to recursively iterate through all the elements
            Returns a instantiated blank class becomes the result of the passed argument

        }
        */


        //from class object
        t nearest_neighbor_oftype(t data, std::string wanted_type);/*
        {Calls private recursive helper function (below)

            Looks for the nearest neighbor of a passed class of a particular type, this field is for <DefaultLocation> class, but can be changed to another attribute of the class stored in the tree
            Calls helper function to recursively iterate through all the elements
            Returns a copy of the class

        }
        */

        //from class object
        t nearest_neighbor_oftype(t data, std::string wanted_type, double &best_distance);/*
        {Calls private recursive helper function (below)

            Looks for the nearest neighbor of a passed class of a particular type, this field is for <DefaultLocation> class, but can be changed to another attribute of the class stored in the tree
            Can return the best distance if a number is passed by reference
            Calls helper function to recursively iterate through all the elements
            Returns a copy of the class

        }
        */

        //from local coords
        t nearest_neighbor_oftype(std::vector<double> local_coords, std::string wanted_type);/*
        {Calls private recursive helper function (below)

            Looks for the nearest neighbor of passed coordinates of a particular type, this field is for <DefaultLocation> class, but can be changed to another attribute of the class stored in the tree
            Calls helper function to recursively iterate through all the elements
            Returns a copy of the class

        }
        */

        //from local coords
        t nearest_neighbor_oftype(std::vector<double> local_coords, std::string wanted_type, double &best_distance);/*
        {Calls private recursive helper function (below)

            Looks for the nearest neighbor of passed coordinates of a particular type, this field is for <DefaultLocation> class, but can be changed to another attribute of the class stored in the tree
            Can return the best distance if a number is passed by reference
            Calls helper function to recursively iterate through all the elements
            Returns a copy of the class

        }
        */


        //from class object
        t nearest_neighbor_best(t data);/*
        {   Calls private recursive helper function (below)

            Looks for the nearest neighbor of a passed class
            Calls helper function to recursively iterate through all the elements
            Returns a copy of the class
        }
        */

        //from class object
        t nearest_neighbor_best(t data, double &best_distance);/*
        {Calls private recursive helper function (below)

            Looks for the nearest neighbor of a passed class, with an additional argument if one would like to return what the distance between the two neighbors are
            Calls helper function to recursively iterate through all the elements
            Returns a copy of the class

        }
        */


        //from local coords
        t nearest_neighbor_best(std::vector<double> local_coords);/*
        {Calls private recursive helper function (below)

            Looks for the nearest neighbor of passed coordinates
            Creates a blank Class of t with coordinates, and calls the same recursive function as the other NN functions
            Calls helper function to recursively iterate through all the elements
            Returns a instantiated blank class becomes the result of the passed argument

        }
        */

        //from local coords
        t nearest_neighbor_best(std::vector<double> local_coords, double &best_distance);/*
        {Calls private recursive helper function (below)

            Looks for the nearest neighbor of passed coordinates, with an additional argument if one would like to return what the distance between the two neighbors are
            Creates a blank Class of t with coordinates, and calls the same recursive function as the other NN functions
            Calls helper function to recursively iterate through all the elements
            Returns a instantiated blank class becomes the result of the passed argument

        }
        */


        //from class object
        t nearest_neighbor_oftype_best(t data, std::string wanted_type);/*
        {Calls private recursive helper function (below)

            Looks for the nearest neighbor of a passed class of a particular type, this field is for <DefaultLocation> class, but can be changed to another attribute of the class stored in the tree
            Calls helper function to recursively iterate through all the elements
            Returns a copy of the class

        }
        */

        //from class object
        t nearest_neighbor_oftype_best(t data, std::string wanted_type, double &best_distance);/*
        {Calls private recursive helper function (below)

            Looks for the nearest neighbor of a passed class of a particular type, this field is for <DefaultLocation> class, but can be changed to another attribute of the class stored in the tree
            Can return the best distance if a number is passed by reference
            Calls helper function to recursively iterate through all the elements
            Returns a copy of the class

        }
        */

        //from local coords
        t nearest_neighbor_oftype_best(std::vector<double> local_coords, std::string wanted_type);/*
        {Calls private recursive helper function (below)

            Looks for the nearest neighbor of passed coordinates of a particular type, this field is for <DefaultLocation> class, but can be changed to another attribute of the class stored in the tree
            Calls helper function to recursively iterate through all the elements
            Returns a copy of the class

        }
        */

        //from local coords
        t nearest_neighbor_oftype_best(std::vector<double> local_coords, std::string wanted_type, double &best_distance);/*
        {Calls private recursive helper function (below)

            Looks for the nearest neighbor of passed coordinates of a particular type, this field is for <DefaultLocation> class, but can be changed to another attribute of the class stored in the tree
            Can return the best distance if a number is passed by reference
            Calls helper function to recursively iterate through all the elements
            Returns a copy of the class

        }
        */

        //destroy tree, public
        void destroy(); /*
        {Calls private recursive helper function (below)


            //Called on the object to destroy the data in it
            //Tree is reset with 0 nodes, however it maintains the number of dimesions so it can be used by the same types of classes
            //Dimensions is left public so this can be modified if the same class can have varying number of dimensions, such as <DefaultLocation>

        }
        */


        //post-order
        void postOrder();/*
        {Calls private recursive helper function (below)


            //Calls recursive helper function and prints tree in a post order notation, this is currently for a <DefaultLocation>, but can be modified to call a print command on the passed template

        }
        */


        //inorder
        void inOrder(); /*
        {Calls private recursive helper function (below)


            //Calls recursive helper function and prints tree in an in order notation, this is currently for a <DefaultLocation>, but can be modified to call a print command on the passed template

        }
        */


        //preorder
        void preOrder(); /*
        {Calls private recursive helper function (below)


            //Calls recursive helper function and prints tree in a pre order notation, this is currently for a <DefaultLocation>, but can be modified to call a print command on the passed template

        }
        */

        void dotOut(std::string fname_out);/*
        {Calls private recursive helper function (below)


            //Called on a tree in order to print out .dot file formatting and generate an SVG file named the passed argument "fname_out" i.e. "myfile.svg"
            Uses dot function called as a system argument, in order to call this function you must
            1. Be running a distribution of Linux
            2. Have graphviz installed locally
                cmd: sudo apt-get install graphviz
            3. If this is not installed locally, the .dot file formatting can still be ran, but you must go to the function and commend out system(cmd) calls
        }
        */
        std::string colors_678436859937850983[147] = { "aquamarine", "black", "blue", "blueviolet", "brown", "burlywood", "cadetblue", "chartreuse", "chocolate", "coral", "cornflowerblue", "crimson", "cyan", "darkgoldenrod", "darkgreen", "darkgrey", "darkkhaki", "darkolivegreen", "darkorange", "darkorchid", "darksalmon", "darkseagreen", "darkslateblue", "darkslategray", "darkturquoise", "darkviolet", "deeppink", "deepskyblue", "dimgray", "dimgrey", "dodgerblue", "firebrick", "forestgreen", "fuchsia", "gainsboro", "gold", "goldenrod", "gray", "grey", "green", "greenyellow", "honeydew", "hotpink", "indianred", "indigo", "ivory", "khaki", "lavender", "lavenderblush", "lawngreen", "lemonchiffon", "lightblue", "lightcoral", "lightcyan", "lightgoldenrodyellow", "lightgray", "lightgreen", "lightgrey", "lightpink", "lightsalmon", "lightseagreen", "lightskyblue", "lightslategray", "lightslategrey", "lightsteelblue", "lightyellow", "lime", "limegreen", "linen", "magenta", "maroon", "mediumaquamarine", "mediumblue", "mediumorchid", "mediumpurple", "mediumseagreen", "mediumslateblue", "mediumspringgreen", "mediumturquoise", "mediumvioletred", "midnightblue", "mintcream", "mistyrose", "moccasin", "navajowhite", "navy", "oldlace", "olive", "olivedrab", "orange", "orangered", "orchid", "palegoldenrod", "palegreen", "paleturquoise", "palevioletred", "papayawhip", "peachpuff", "peru", "pink", "plum", "powderblue", "purple", "red", "rosybrown", "royalblue", "saddlebrown", "salmon", "sandybrown", "seagreen", "seashell", "sienna", "silver", "skyblue", "slateblue", "slategray", "slategrey", "snow", "springgreen", "steelblue", "tan", "teal", "thistle", "tomato", "turquoise", "violet", "wheat", "white", "whitesmoke", "yellow", "yellowgreen" };/*
        {
            Used in dotOut function for coloring all equal depths of branches the same color, will support a tree with a height of 140, however your computer may not (Up to 6.969*10^41 nodes)

        }
        */

        std::string arb_dims_678436859937850983[9] = {"x","y","z","wx","wy","wz","nx","ny","nz"}; /*
        {
            Used in dotOut function for labeling the dimensions of the nodes, will support up to 9 dimensions, otherwise known as string theory level data
        }
        */
        private:


    Node<t>* insert_r(Node<t> *node, t data, unsigned int depth_r); /*
        {
            Called by insert(t data) and iterates recursively tracking the depth, obtaining the discriminator from the number of dimensions
            1. distriminator = depth mod dimensions
            2. Compares current nodes->struct_of_data.coords[distriminator] to data.coords[disriminator]
            3. Fines if it belongs to the left or right, and then if the correct sided child is not a nullptr, goes there and calls recursive insert again
            4. Base case is if correct sided child is a nullptr, if it is, then it makes the child a new Node<t>(data)
        }
        */

        //search for element
        bool search_for_element_r(Node<t>* node, t data, unsigned int depth_r);/*
        {
            Called by public method search_for_element
            Recursively terates through all the elements comparing the class member in the current node is equal to the the passed argument
            If it is found, returns true

        }
        */

        //from local coords
        void nearest_neighbor_rfast(Node<t>* node, t &data, t &result, unsigned int depth_r, double &best_dist);/*
        {
            Recursively iterates through tree looking for the nearest neighbor, in order to return the class, it has to track both the resulting class object and the best distance
            When the current distance between the nodes data and the passed data is less than the best data, sets a new best distances and copies the nodes data into the result
            Continues to iterate through until all leaves have been exhaused, then compares the best distance from other calls until the it has returned to the root node

        }
        */

        void nearest_neighbor_rbest(Node<t>* node, t &data, t &result, unsigned int depth_r, double &best_dist);/*
        {
            Recursively iterates through tree looking for the nearest neighbor, in order to return the class, it has to track both the resulting class object and the best distance
            When the current distance between the nodes data and the passed data is less than the best data, sets a new best distances and copies the nodes data into the result
            Continues to iterate through until all leaves have been exhaused, then compares the best distance from other calls until the it has returned to the root node

        }
        */

        void nearest_neighbor_oftype_rfast(Node<t>* node, t &data, std::string wanted_type, t &result, unsigned int depth_r, double &best_dist);/*
        {
            Recursively iterates through tree looking for the nearest neighbor of a particular type, in order to return the class, it has to track both the resulting class object and the best distance
            When the current distance between the nodes data and the passed data is less than the best data, sets a new best distances and copies the nodes data into the result
            Continues to iterate through until all leaves have been exhaused, then compares the best distance from other calls until the it has returned to the root node

        }
        */

        void nearest_neighbor_oftype_rbest(Node<t>* node, t &data, std::string wanted_type, t &result, unsigned int depth_r, double &best_dist);/*
        {
            Recursively iterates through tree looking for the nearest neighbor of a particular type, in order to return the class, it has to track both the resulting class object and the best distance
            When the current distance between the nodes data and the passed data is less than the best data, sets a new best distances and copies the nodes data into the result
            Continues to iterate through until all leaves have been exhaused, then compares the best distance from other calls until the it has returned to the root node

        }
        */


        //destroy tree recursive, local
        void destroy_r(Node<t>* node);/*
        {
            //Similar to nearest neighbors, it performs same sequence however destroys the children nodes when they're reached, truly evil

        }
        */

        void inOrder_r(Node<t>* node); /*
        {
            //Recursive call for printing in in order (left, root, right)

        }
        */

        void postOrder_r(Node<t>* node);/*
        {
            //Recursive call for printing in post order (left, right, root)

        }
        */

        void preOrder_r(Node<t>* node);/*
        {
            //Recursive call for printing in pre order (root, left, right)

        }
        */

        //output .dot file formatting
        void dotOut_r(Node<t>* node, std::ofstream &ofs, unsigned int depth_r);/*
        {
            //Called by dotOut public method
            //Recursive function call to print out the KDTree

        }
        */

};

/*
************************************************************************************************************
        DEFINITIONS ****************************************************************************************
************************************************************************************************************
*/


/////////////////////// CONSTRUCTORS SECTION


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

/////////////////////// METHODS SECTION


/////////// DESTROY
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

/////////// INSERT

//insert recursively, called from within
template <typename t>
Node<t>* KDTree<t>::insert_r(Node<t>* node, t data, unsigned int depth_r) {
    if(depth_r+1 > this->height) {
        this->height = depth_r+1;
    }
    //compare current index as discriminator = depth/dimensions
    int i = depth_r%(this->dimensions);

    if(node->struct_of_data.coords[i] <= data.coords[i]) {
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

/////////// REMOVE NODE (not implemented)

//remove
template <typename t>
void KDTree<t>::remove_node(Node<t>* node) {

}

/////////// DISTANCE FUNCTION

//nearest neighbor
    //from class of data
template <typename t>
double KDTree<t>::dist_from_to(t data, Node<t>* node) {
    double sum = 0.00000;
    double a_dim1 = 0.00000, a_dim2 = 0.00000;
    for(int i = 0; i < data.coords.size(); i++) {
        a_dim1 = data.coords[i];
        a_dim2 = node->struct_of_data.coords[i];
        a_dim2 -= a_dim1;
        sum+=pow(a_dim2,2);
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


/////////// SEARCH

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


/////////// NEAREST NEIGHBOR, APPROXIMATED FUNCTION CALL, PRIVATE RECURSIVE CALL

//from class
template <typename t>
void KDTree<t>::nearest_neighbor_rfast(Node<t>* node, t &data, t &result, unsigned int depth_r, double &best_dist) {
    int i = depth_r%(this->dimensions);
    double dist = dist_from_to(data, node);
    if(node->struct_of_data.coords[i] < data.coords[i]) {
        if(!node->right_child) {
            if((best_dist > dist) && (node->struct_of_data != data)) {
                best_dist = dist;
                result = node->struct_of_data;
            }
            return;
        }
        nearest_neighbor_rfast(node->right_child, data, result, depth_r+1, best_dist);
    } else {
        if(!node->left_child) {
            if(best_dist >= dist && node->struct_of_data != data) {
                best_dist = dist;
                result = node->struct_of_data;
            }
            return;
        }
        nearest_neighbor_rfast(node->left_child, data, result, depth_r+1, best_dist);
    }
    if(best_dist > dist && node->struct_of_data != data) {
        best_dist = dist;
        result = node->struct_of_data;
    }
    return;
}

/////////// NEAREST NEIGHBOR, EXACT CLOSEST NEIGHBOR, PRIVATE RECURSIVE CALL

template <typename t>
void KDTree<t>::nearest_neighbor_rbest(Node<t>* node, t &data, t &result, unsigned int depth_r, double &best_dist) {
    if(!node) {
        return;
    }
    nearest_neighbor_rbest(node->right_child, data, result, depth_r+1, best_dist);
    nearest_neighbor_rbest(node->left_child, data, result, depth_r+1, best_dist);

    double dist = dist_from_to(data, node);

    if (dist != 0 && best_dist > dist) {
        best_dist = dist;
        result = node->struct_of_data;
    }
}

/////////// NEAREST NEIGHBOR, DEFAULT, FAST
//from class
template <typename t>
t KDTree<t>::nearest_neighbor(t data) {

    t result(this->dimensions);
    double best_dist = DBL_MAXT; // << literally the worst case
    nearest_neighbor_rfast(this->head, data, result, 0, best_dist);
    return result;
}

template <typename t>
t KDTree<t>::nearest_neighbor(t data, double &best_dist) {
    t result(this->dimensions);
    nearest_neighbor_rfast(this->head, data, result, 0, best_dist);
    return result;
}


//from class
template <typename t>
t KDTree<t>::nearest_neighbor(std::vector<double> local_coords) {
    t result(this->dimensions);
    t data(this->dimensions);

    for(int i = 0; i <local_coords.size(); i++){
        data.coords[i] = (local_coords[i]);
    }
    double best_dist = DBL_MAXT; // << literally the worst case
    nearest_neighbor_rfast(this->head, data, result, 0, best_dist);
    return result;
}

//from class
template <typename t>
t KDTree<t>::nearest_neighbor(std::vector<double> local_coords, double &best_dist) {
    t result;
    t data;
    for(int i = 0; i <local_coords.size(); i++){
        data.coords.push_back(local_coords[i]);
    }
    nearest_neighbor_rfast(this->head, data, result, 0, best_dist);
    return result;
}

/////////// NEAREST NEIGHBOR, BEST
//from class
template <typename t>
t KDTree<t>::nearest_neighbor_best(t data) {

    t result(this->dimensions);
    double best_dist = DBL_MAXT; // << literally the worst case
    nearest_neighbor_rbest(this->head, data, result, 0, best_dist);
    return result;
}

template <typename t>
t KDTree<t>::nearest_neighbor_best(t data, double &best_dist) {
    t result(this->dimensions);
    nearest_neighbor_rbest(this->head, data, result, 0, best_dist);
    return result;
}


//from class
template <typename t>
t KDTree<t>::nearest_neighbor_best(std::vector<double> local_coords) {
    t result(this->dimensions);
    t data(this->dimensions);

    for(int i = 0; i <local_coords.size(); i++){
        data.coords[i] = (local_coords[i]);
    }
    double best_dist = DBL_MAXT; // << literally the worst case
    nearest_neighbor_rbest(this->head, data, result, 0, best_dist);
    return result;
}

//from class
template <typename t>
t KDTree<t>::nearest_neighbor_best(std::vector<double> local_coords, double &best_dist) {
    t result;
    t data;
    for(int i = 0; i <local_coords.size(); i++){
        data.coords.push_back(local_coords[i]);
    }
    nearest_neighbor_rbest(this->head, data, result, 0, best_dist);
    return result;
}


/////////// NEAREST NEIGHBOR, BEST, OF TYPE, RECURSIVE CALL
//of type
//from class
template <typename t>
void KDTree<t>::nearest_neighbor_oftype_rbest(Node<t>* node, t &data, std::string wanted_type, t &result, unsigned int depth_r, double &best_dist) {

    if(!node) {
        return;
    }

    nearest_neighbor_oftype_rbest(node->right_child, data, wanted_type, result, depth_r+1, best_dist);
    nearest_neighbor_oftype_rbest(node->left_child, data, wanted_type, result, depth_r+1, best_dist);
    double dist = dist_from_to(data, node);
    if (dist != 0 && best_dist > dist) {
        best_dist = dist;
        result = node->struct_of_data;
    }
}

/////////// NEAREST NEIGHBOR, APPROXIMATED, OF TYPE, RECURSIVE CALL

template <typename t>
void KDTree<t>::nearest_neighbor_oftype_rfast(Node<t>* node, t &data, std::string wanted_type, t &result, unsigned int depth_r, double &best_dist) {

    int i = depth_r%(this->dimensions);

    double dist = dist_from_to(data, node);
    if(node->struct_of_data.coords[i] < data.coords[i]) {

        if(!node->right_child) {

            if((best_dist > dist) && (node->struct_of_data != data && (node->struct_of_data.type == wanted_type))) {
                best_dist = dist;
                result = node->struct_of_data;
            }

            return;
        }

        nearest_neighbor_oftype_rfast(node->right_child, data, wanted_type, result, depth_r+1, best_dist);

    } else {

        if(!node->left_child) {

            if(best_dist >= dist && node->struct_of_data != data && (node->struct_of_data.type == wanted_type)) {
                best_dist = dist;
                result = node->struct_of_data;

            }

            return;
        }

        nearest_neighbor_oftype_rfast(node->left_child, data, wanted_type, result, depth_r+1, best_dist);
    }

    if(best_dist > dist && node->struct_of_data != data) {
        best_dist = dist;
        result = node->struct_of_data;
    }
    return;
}


/////////// NEAREST NEIGHBOR, OF TYPE, APPROXIMATED
//from class
template <typename t>
t KDTree<t>::nearest_neighbor_oftype(t data, std::string wanted_type) {
    t result(this->dimensions);
    double best_dist = DBL_MAXT; // << literally the worst case
    nearest_neighbor_oftype_rfast(this->head, data, wanted_type, result, 0, best_dist);
    return result;
}

template <typename t>
t KDTree<t>::nearest_neighbor_oftype(t data, std::string wanted_type, double &best_dist) {
    t result(this->dimensions);
    nearest_neighbor_oftype_rfast(this->head, data, wanted_type, result, 0, best_dist);
    return result;
}

//from class
template <typename t>
t KDTree<t>::nearest_neighbor_oftype(std::vector<double> local_coords, std::string wanted_type) {
    t result(this->dimensions);
    t data(this->dimensions);
    for(int i = 0; i <local_coords.size(); i++){
        data.coords.push_back(local_coords[i]);
    }
    double best_dist = DBL_MAXT; // << literally the worst case
    nearest_neighbor_oftype_rfast(this->head, data, wanted_type, result, 0, best_dist);
    return result;
}

//from class
template <typename t>
t KDTree<t>::nearest_neighbor_oftype(std::vector<double> local_coords, std::string wanted_type, double &best_dist) {
    t result(this->dimensions);
    t data(this->dimensions);
    for(int i = 0; i <local_coords.size(); i++){
        data.coords.push_back(local_coords[i]);
    }
    nearest_neighbor_oftype_rfast(this->head, data, wanted_type, result, 0, best_dist);
    return result;
}

/////////// NEAREST NEIGHBOR, OF TYPE, BEST
//from class
template <typename t>
t KDTree<t>::nearest_neighbor_oftype_best(t data, std::string wanted_type) {
    t result(this->dimensions);
    double best_dist = DBL_MAXT; // << literally the worst case
    nearest_neighbor_oftype_rbest(this->head, data, wanted_type, result, 0, best_dist);
    return result;
}

template <typename t>
t KDTree<t>::nearest_neighbor_oftype_best(t data, std::string wanted_type, double &best_dist) {
    t result(this->dimensions);
    nearest_neighbor_oftype_rbest(this->head, data, wanted_type, result, 0, best_dist);
    return result;
}

//from class
template <typename t>
t KDTree<t>::nearest_neighbor_oftype_best(std::vector<double> local_coords, std::string wanted_type) {
    t result(this->dimensions);
    t data(this->dimensions);
    for(int i = 0; i <local_coords.size(); i++){
        data.coords.push_back(local_coords[i]);
    }
    double best_dist = DBL_MAXT; // << literally the worst case
    nearest_neighbor_oftype_rbest(this->head, data, wanted_type, result, 0, best_dist);
    return result;
}

//from class
template <typename t>
t KDTree<t>::nearest_neighbor_oftype_best(std::vector<double> local_coords, std::string wanted_type, double &best_dist) {
    t result(this->dimensions);
    t data(this->dimensions);
    for(int i = 0; i <local_coords.size(); i++){
        data.coords.push_back(local_coords[i]);
    }
    nearest_neighbor_oftype_rbest(this->head, data, wanted_type, result, 0, best_dist);
    return result;
}

/////////// PRINT ORDERS
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

/////////// PRINT ORDERS, RECURSIVE CALLS
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


/////////// GENERATES .DOT FILE OF CURRENT TREE, USES LINUX/GNU BASH SYSTEM ARGUMENTS, NEED TO INSTALL GRAPH VIZ, << sudo apt-get install graphviz >>


//prints pretty dot formatting, recursive for use in class called by public member function
template <typename t>
void KDTree<t>::dotOut_r(Node<t>* node, std::ofstream &ofs, unsigned int depth_r) {

    if(!node) return;
    //uses a post order traversal but doesn't make a difference in how the graph is displayed
    dotOut_r(node->left_child, ofs, depth_r+1);
    dotOut_r(node->right_child, ofs, depth_r+1);
    if(node->left_child) {
        //from 1
        ofs << "\t\t<"<< node->struct_of_data.name << ": ";
        for(int i = 0; i < node->struct_of_data.coords.size()-1; i++) {
            ofs << node->struct_of_data.coords[i] << ",";
        }
        ofs << node->struct_of_data.coords.back() << "> ->";

        //to 1
        ofs << "\t<"<< node->left_child->struct_of_data.name << ": ";
        for(int i = 0; i < node->left_child->struct_of_data.coords.size()-1; i++) {
            ofs << node->left_child->struct_of_data.coords[i] << ",";
        }
        ofs << node->left_child->struct_of_data.coords.back();
        ofs << ">";
        ofs << "[color=\""<< colors_678436859937850983[depth_r] << "\"]\n";

    }
    if(node->right_child) {
        //from 2
        ofs << "\t\t<"<< node->struct_of_data.name << ": ";
        for(int i = 0; i < node->struct_of_data.coords.size()-1; i++) {
            ofs << node->struct_of_data.coords[i] << ",";
        }
        ofs << node->struct_of_data.coords.back() << "> ->";

        //to 2
        ofs << "\t<"<< node->right_child->struct_of_data.name << ": ";
        for(int i = 0; i < node->right_child->struct_of_data.coords.size()-1; i++) {
            ofs << node->right_child->struct_of_data.coords[i] << ",";
        }
        ofs << node->right_child->struct_of_data.coords.back();
        ofs << ">";
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
    //std::cout << "in dot out " << fname_out << std::endl;
    //std::cout << this->head->struct_of_data.type << std::endl;
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
    ofs << "\t\t}\n";
    ofs << "}\n";

    ofs.close();

    std::string newfn = "filename.png";
    std::string cmd = "dot -Tsvg -o " + fname_out + " " + fn;
    const char *cmd2 = cmd.c_str();
    std::cout << "\ndotDout: Make sure you've installed Graphviz, on a Linux/Ubuntu OS run:\n\tsudo apt-get install graphviz\nIn order to automatically go from .dot > .svg .\nElse, open \"recent_graph.dot\" and use another converter. Disable system(cmd2) in dotOut function.\n";
    system(cmd2);

    //sleep(5);
    cmd = "rm " + fn;
    cmd2 = cmd.c_str();
    //system(cmd2);
    return;
}



#endif