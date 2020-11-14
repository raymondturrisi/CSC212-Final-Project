#include "Node2D.h"
#include <vector>
#ifndef NULL
#define NULL 0x00
#endif

template<class node_type>
class KDT {

  private:
    node_type * root = NULL;

    void insert(std::vector<node_type> & input_list);
    void insert(node_type input);

    void destroy();

  public:
    KDT();
    ~KDT();

};

// Note: These function definitions must be placed in the same file as the class
// declaration, a restriction which occurs when using templated classes.

template<class node_type> void KDT<node_type>::insert(std::vector<node_type> & input_list){

}

template<class node_type> void KDT<node_type>::insert(node_type input){

}

template<class node_type> void KDT<node_type>::destroy(){

}

template<class node_type> KDT<node_type>::KDT(){

}

template<class node_type> KDT<node_type>::~KDT(){

}
