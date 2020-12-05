
#ifndef NODE_CLASS
#define NODE_CLASS

#include <iostream>
#include "dataStructs.hpp"

template <typename t>
class Node {
    //friend class KDTree<t>;
    private:


    public:
        t struct_of_data;
        Node<t>* left_child = NULL;
        Node<t>* right_child = NULL;


        Node<t>();
        Node<t>(t _struct_of_data);
        void print_cords();
        ~Node<t>();
};

template <typename t>
Node<t>::Node() {

}

template <typename t>
Node<t>::Node(t _struct_of_data) {
    this->struct_of_data = _struct_of_data;
}

template <typename t>
void Node<t>::print_cords() {
    for(int i = 0; i < this->struct_of_data.coords.size(); i++) {
        std::cout << this->struct_of_data.coords[i] << " ";
    }
    std::cout << std::endl;
}

template <typename t>
Node<t>::~Node() {

}

#endif