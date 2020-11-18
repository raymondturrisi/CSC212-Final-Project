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
    void insert(Node<num_type, specific_data> input, int height);

    Node<num_type, specific_data> find_nearest_neighbor(std::vector<num_type> & coordinate_vector);

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

  // This function constructs a KDTree when many input Nodes are available.
  // Selecting the points by always inserting the median keeps the tree more
  // balanced, and keeps performance closer to O(logn).
  // Calls the single node input function (below) to handle insertion


  // COULD create Nodes from input file here, and forego passing as a parameter.


  // (Queue for storing the axis being used)
  // or (int axis = depth % Node.coordinate_data.size())


  // List insertion pseudocode...

  // i = 0, while i < input_list.length()

  //    Pick the median Node/point

  //    Cycle the axis

  //    Insert the median Node/point

  //    Remove the median Node/point from the input list


}

template<class num_type, class specific_data>
void KDT<num_type, specific_data>::insert(Node<num_type, specific_data> input, Node<num_type, specific_data> current, int height){

  int axis = height % input.coordinate_data.length();

  if(this->root_node == NULL){
    this->root_node = input;
  }
  else{

    // recursive insertion
    // If input < current in axis of interest:
    //    insert(input, current.left, height + 1);
    // Else:
    //    insert(input, current.right, heigh + 1);

  }

}

template<class num_type, class specific_data>
Node<num_type, specific_data> KDT<num_type, specific_data>::find_nearest_neighbor(std::vector<num_type> & coordinate_search_vector){

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
