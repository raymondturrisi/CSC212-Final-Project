#include "Node.h"
#include <vector>

#ifndef NULL
#define NULL 0x00
#endif

template<class num_type, class specific_data>
class KDT {

  private:
    Node<num_type, specific_data> * root = NULL;

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

  // **** Should this function be converted to a recursive one ?? ****
  // https://en.wikipedia.org/wiki/K-d_tree#Construction

  // This function constructs a KDTree when many input Nodes are available.
  // Selecting the points by always inserting the median keeps the tree more
  // balanced, and keeps performance closer to O(logn).
  // Calls the single node input function (below) to handle insertion

  // Assumes input is a list of Nodes already created based on input file

  // i = 0, while i < input_list.length()
  // For each Node that we want to insert into the tree
  for(int i = 0; i < input_list.length(); i ++){

    //    Pick the median Node
    // NOTE: Right now, grabs element at i but should be median.
    // NOTE: Do we select our median based on any specific axis? (if
    // so, then we'd be better off finding it within our single node
    // insertion function.)

    Node<num_type, specific_data> median = input_list[i];

    //    Insert the median Node
    // Should the height be passed as 0 or 1?
    insert(median, this->root, 0);

    //    Remove the median Node from the input list
    input_list.erase(i);

  }



}


template<class num_type, class specific_data>
void KDT<num_type, specific_data>::insert(Node<num_type, specific_data> node_to_insert, Node<num_type, specific_data> root, int height){

  // This function handles the insertion of any single Node into the tree.

  int axis = height % node_to_insert.coordinate_data.length();

  // If this is the first node being inserted
  if(!root){
    root = node_to_insert;
  }

  // recursive insertion
  // Else if node_to_insert < current in axis of interest:
  //    insert(node_to_insert, current.left, height + 1);
  else if(node_to_insert.coordinate_data[axis] < root.coordinate_data[axis]){
    return insert(node_to_insert->left, root, height + 1);
  }

  // Else if node_to_insert > current in axis of interest:
  //    insert(node_to_insert->right, height + 1);
  else if(node_to_insert.coordinate_data[axis] > root.coordinate_data[axis]){
    return insert(node_to_insert->right, root, height + 1);
  }

  return node_to_insert;

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
