#include "Node.h"
#include <vector>

#ifndef NULL
#define NULL 0x00
#endif

template<class num_type, class specific_data>
class KDT {

  private:
    Node<num_type, specific_data> * root_node = NULL;

    void insert(std::vector<Node<num_type, specific_data>> & input_list);
    void insert(Node<num_type, specific_data> input);

    Node<num_type, specific_data> find();

    void destroy();

  public:
    KDT();
    ~KDT();

};

// Note: These function definitions must be placed in the same file as the class
// declaration, a restriction which occurs when using templated classes.

// ------- Outline For Defining Methods on Templated Classes ---------
// template<class |param1_name, ... , paramN_name|>
// |return type| |class name|::|function name and params| { |code| }
// -------------------------------------------------------------------

template<class num_type, class specific_data>
void KDT<num_type, specific_data>::insert(std::vector<Node<num_type, specific_data>> & input_list){

}

template<class num_type, class specific_data>
void KDT<num_type, specific_data>::insert(Node<num_type, specific_data> input){

}

template<class num_type, class specific_data>
Node<num_type, specific_data> KDT<num_type, specific_data>::find(){

}

template<class num_type, class specific_data>
void KDT<num_type, specific_data>::destroy(){
  //TODO: Recursively destroy data structure.
}

template<class num_type, class specific_data>
KDT<num_type, specific_data>::KDT(){
  // Constructor
}

template<class num_type, class specific_data>
KDT<num_type, specific_data>::~KDT(){
  destroy();
}
