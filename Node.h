#include <vector>


template<class num_type, class specific_data>
class Node {

  private:
    // Points to any class you pass as <specficic_data> arg
    specific_data * other_data = NULL;

    std::vector<num_type> coordinate_data = {};

    void destroy();

  public:
    Node();
    ~Node();

};

// Note: These function definitions must be placed in the same file as the class
// declaration, a restriction which occurs when using templated classes.

// ------- Outline For Defining Methods on Templated Classes ---------
// template<class |param1_name, ... , paramN_name|>
// |return type| |class name|::|function name and params| { |code| }
// -------------------------------------------------------------------

template<class num_type, class specific_data>
Node<num_type, specific_data>::Node(){
// Constructor
}

template<class num_type, class specific_data>
Node<num_type, specific_data>::~Node(){
  destroy();
}

template<class num_type, class specific_data>
void Node<num_type, specific_data>::destroy(){
  destroy();
}
