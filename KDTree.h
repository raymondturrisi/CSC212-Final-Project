#include "Node.h"
#include <vector>

#ifndef NULL
#define NULL 0x00
#endif

template<class num_type, class specific_data>
class KDT {

  private:
    Node<num_type, specific_data> * root = NULL;

    void insert(std::vector<Node<num_type, specific_data>> & input_list, int depth);
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
KDT<num_type, specific_data> KDT<num_type, specific_data>::insert(std::vector<Node<num_type, specific_data>> & input_list, int depth){

  // **** Should this function be a recursive one? Yes. ****
  // https://en.wikipedia.org/wiki/K-d_tree#Construction

  // - This function constructs a KDTree when many input Nodes are available.
  // - Selecting the points by always inserting the median in the current axis
  //   keeps the tree more balanced, and keeps performance closer to O(logn).

  // Select axis based on depth so that axis cycles through all valid values
  int axis = depth % input_list[0].coordinate_vector.size();

  // Sort Nodes list and choose median as pivot element

  // Modify the input to be sorted based on the axis, and keep track of the median Node.
  // The find_median() function hiddenly operates on the median_node_index variable.
  int median_node_index = 0;
  Node<num_type, specific_data> & median_node = this->find_median(input_list, axis, median_node_index);

  // If this is the first node being inserted
  if(!root){
    this->root = median_node;
    return;
  }
  else{
    // Make left and right halves.
    //
    // Is it direly important that this functions in better than Theta(n) time?
    // Does this perform in Theta(logn) times since the size of the list is always cut in half?
    //
    // When would this function ever come across a large enough sized list to cause
    // it to take a longer than acceptable time to execute?
    std::vector<Node<num_type, specific_data>> left_half = {};
    std::vector<Node<num_type, specific_data>> right_half = {};

    for(int i = 0; i < input_list; i++){
      if(i < median_node_index){
        left_half.append(input_list[i]);
      }
      else if(i > median_node_index){
        right_half.append(input_list[i]);
      }
    }

    // Construct subtrees with left and right halves recursively.
    median_node.left_child = insert(left_half, depth + 1);
    median_node.right_child = insert(right_half, depth + 1);
     
    // Insert the median_node
    return median_node;
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
