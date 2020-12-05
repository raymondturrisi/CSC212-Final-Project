#ifndef KDTREE_CLASS
#define KDTREE_CLASS

#include "Node.hpp"
#include <fstream>
#include <string>
#include <unistd.h>
template <class t>
class KDTree {
    private:

    public:
        //head
        Node<t>* head;
        int nodes = 0;
        int depth = 0;
        int dimensions = 0;
        //constructors
        KDTree<t>();

        KDTree<t>(t data);

        KDTree<t>(std::vector<t> vector_of_structs);

        //insert
        void insert(t data);
        Node<t>*  insert_r(Node<t> *node, t data, unsigned int depth);

        //remove

        //balance

        //nearest neighbor

        //destroy tree, public
        void destroy();

        //destroy tree recursive, local
        void destroy_r(Node<t>* node);

        //post-order
        void postOrder();
        void postOrder(Node<t>* node);
        //inorder
        void inOrder();
        void inOrder(Node<t>* node);
        //preorder
        void preOrder();
        void preOrder(Node<t>* node);
        //output .dot file formatting
        void dotOut_r(Node<t>* node, std::ofstream &ofs);
        void dotOut(std::string fname_out);

};


template <typename t>
KDTree<t>::KDTree() {
    //this->head = new Node<t>();
    this->head = nullptr;
}

template <typename t>
KDTree<t>::KDTree(t data) {
    //for insantiating a new KDtree
    this->head = new Node<t>(data);
    this->dimensions = data.coords.size();
    this->nodes++;
}

template <typename t>
KDTree<t>::KDTree(std::vector<t> vector_of_structs) {

}

template <typename t>
void KDTree<t>::destroy_r(Node<t> *node) {
    if(!node) {
        return;
    }

    this->destroy_r(node->left_child);
    this->destroy_r(node->right_child);
    delete node->left;
    delete node->right;
}

template <typename t>
void KDTree<t>::destroy() {
    this->destroy_r(this->head);
}

template <typename t>
Node<t>* KDTree<t>::insert_r(Node<t>* node, t data, unsigned int depth) {

    //compare current index as discriminator = depth/dimensions
    int i = depth%(this->dimensions);

    //std::cout <<node->struct_of_data.coords[i] << " " << data.coords[i] << std::endl;
    if(node->struct_of_data.coords[i] < data.coords[i]) {
        if(!node->right_child) {
            this->nodes++;
            node->right_child = new Node<t>(data);
            return node->right_child;
        }
        insert_r(node->right_child, data, depth+1);
    } else {
        //std::cout << "left: " << node->left_child << std::endl;
        if(!node->left_child) {
            this-nodes++;
            node->left_child = new Node<t>(data);
            //std::cout << "inserted: " << data.name << " at depth " << depth << " " << &node << " " << this->nodes << std::endl;
            return node->left_child;
        }
        insert_r(node->left_child, data, depth+1);
    }

    return node;
}

template <typename t>
void KDTree<t>::insert(t data) {
    if(!this->head) {
        this->head = new Node<t>(data);
        //std::cout << "in insert\n";
        return;
    } else {
        insert_r(this->head, data, 0);
    }
}


//post-order, called from program
template <typename t>
void KDTree<t>::postOrder() {
    postOrder(this->head);
}

//post-order, recursive in class
template <typename t>
void KDTree<t>::postOrder(Node<t>* node) {
    if(!node) return;
    postOrder(node->left_child);
    postOrder(node->right_child);
    std::cout << "<"<< node->struct_of_data.name << ": "<< node->struct_of_data.coords[0] << "," << node->struct_of_data.coords[1] << ">\n";
    return;
}

//inorder
template <typename t>
void KDTree<t>::inOrder(Node<t>* node) {

}
//preorder
template <typename t>
void KDTree<t>::preOrder(Node<t>* node) {

}

//prints pretty dot formatting, recursive for use in class
template <typename t>
void KDTree<t>::dotOut_r(Node<t>* node, std::ofstream &ofs) {

    if(!node) return;
    dotOut_r(node->left_child, ofs);
    dotOut_r(node->right_child, ofs);

    if(node->left_child) {
        //from 1
        ofs << "\t<"<< node->struct_of_data.name << ": "<< node->struct_of_data.coords[0] << "," << node->struct_of_data.coords[1] << "> ->";

        //to 1
        ofs << "\t<"<< node->left_child->struct_of_data.name << ": "<< node->left_child->struct_of_data.coords[0] << "," << node->left_child->struct_of_data.coords[1] << ">\n";
    }
    if(node->right_child) {
        //from 2
        ofs << "\t<"<< node->struct_of_data.name << ": "<< node->struct_of_data.coords[0] << "," << node->struct_of_data.coords[1] << "> ->";

        //to 2
        ofs << "\t<"<< node->right_child->struct_of_data.name << ": "<< node->right_child->struct_of_data.coords[0] << "," << node->right_child->struct_of_data.coords[1] << ">\n";
    }
    return;
}

//prints pretty dot formatting, on class
template <typename t>
void KDTree<t>::dotOut(std::string fname_out) {
    std::ofstream ofs;
    std::string fn = "to_be_deleted.dot";
    ofs.open(fn);
    ofs << "digraph G {\n";

    dotOut_r(this->head, ofs);

    ofs << "}\n";

    ofs.close();

    std::string newfn = "filename.png";
    std::string cmd = "dot -Tpng -o " + fname_out + " " + fn;
    const char *cmd2 = cmd.c_str();
    system(cmd2);
    sleep(5);
    cmd = "rm " + fn;
    cmd2 = cmd.c_str();
    system(cmd2);
    return;
}


#endif