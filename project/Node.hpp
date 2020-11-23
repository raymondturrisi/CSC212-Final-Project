
#ifndef NODE_CLASS
#define NODE_CLASS

#include <iostream>
#include "dataStructs.hpp"

template <typename t>
class Node {
    friend class KDTree;
    private:
        t struct_of_data;
        float x;
        float y;
        Node<t>* left_child = nullptr;
        Node<t>* right_child = nullptr;

    public:
        Node<t>();
        Node<t>(t _struct_of_data);
        void print_cords();
        ~Node<t>();
};

template <typename t>
Node<t>::Node() {
    this->x = NULL;
    this->y = NULL;
}

template <typename t>
Node<t>::Node(t _struct_of_data) {
    this->struct_of_data = _struct_of_data;
    this->x = _struct_of_data.x;
    this->y = _struct_of_data.y;
}

template <typename t>
void Node<t>::print_cords() {
    std::cout << this->x << " " << this->y << std::endl;
}

template <typename t>
Node<t>::~Node() {

}

#endif