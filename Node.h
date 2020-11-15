#include <vector>
#ifndef NULL
#define NULL 0x00
#endif

template<class num_type, class specific_data>
class Node {

  private:
    // Points to any class you pass as <specficic_data> arg
    specific_data * other_data = 0x00；

    std::vector<num_type> coordinate_data = {};

  public:
    Node();
    ~Node();

};

// Note: These function definitions must be placed in the same file as the class
// declaration, a restriction which occurs when using templated classes.

template<class num_type, class specific_data> Node<num_type, specific_data>::Node(){

}

template<class num_type, class specific_data> Node<num_type, specific_data>::~Node(){

}
