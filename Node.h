#ifndef MEDIAN_H
#define MEDIAN_H
#include <vector>


template<class specific_data>
class KDT;

template<class specific_data>
class Node {
friend class KDT<specific_data>;
  private:
    // Points to any class you pass as <specficic_data> arg
    specific_data other_data;
    Node* left;
    Node* right;

    

    void destroy();

  public:
    Node(std::vector<double> & coordinate_data, specific_data & other_data);
    Node(std::vector<double> & coordinate_data);
    std::vector<double> coordinate_data;
    ~Node();
};

// Note: These function definitions must be placed in the same file as the class
// declaration, a restriction which occurs when using templated classes.

// ------- Outline For Defining Methods on Templated Classes ---------
// template<class |param1_name, ... , paramN_name|>
// |return type| |class name|::|function name and params| { |code| }
// -------------------------------------------------------------------

template<class specific_data>
Node<specific_data>::Node(std::vector<double> & coordinate_data, specific_data & other_data)
{
  this->other_data = other_data;
  this->coordinate_data = coordinate_data;
}

template<class specific_data>
Node<specific_data>::Node(std::vector<double> & coordinate_data)
{
  this->coordinate_data = coordinate_data;
}


template<class specific_data>
Node<specific_data>::~Node(){
  destroy();
}

template<class specific_data>
void Node<specific_data>::destroy(){
  destroy();
}

#endif
