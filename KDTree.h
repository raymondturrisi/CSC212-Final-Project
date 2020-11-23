#include "Node.h"
#include "median.h"
#include <vector>

#ifndef NULL
#define NULL 0x00
#endif

template<class specific_data>
class KDT {

  private:
    Node<specific_data> * root = NULL;
    int numOfDimensions = 0;

    Node<specific_data>* insert(Node<specific_data>* node_to_insert, Node<specific_data>* root, int dimension);

    Node<specific_data> find_nearest_neighbor(std::vector<double> & coordinate_vector);

    void destroy();

  public:
    KDT(std::vector<Node<specific_data>> input_list);
    void insert(Node<specific_data>* node_to_insert, int dimension);
    ~KDT();

};

// Note: These function definitions must be placed in the same file as the class
// declaration, a restriction which occurs when using templated classes.

// ------- Outline For Defining Methods on Templated Classes ---------
// template<class |param1_name, ... , paramN_name|>
// |return type| |class name|::|function name and params| { |code| }
// -------------------------------------------------------------------

template<class specific_data>
Node<specific_data>* KDT<specific_data>::insert(Node<specific_data>* node_to_insert, Node<specific_data>* root, int dimension)
{
  if (dimension = numOfDimensions)
  {
    dimension = 0;
  }
  if (!root)
  {
    return node_to_insert;
  }

  if(node_to_insert->coordinate_data[dimension] < root->coordinate_data[dimension])
  {
    root->left = insert(node_to_insert, root->left, dimension+1);
  }
  else
  {
    root->right = insert(node_to_insert, root->right, dimension+1);
  }
  return root;
}

template<class specific_data>
void KDT<specific_data>::insert(Node<specific_data>* node_to_insert, int dimension)
{
  this->root = this->insert(node_to_insert, this->root, dimension);
}

template<class specific_data>
Node<specific_data> KDT<specific_data>::find_nearest_neighbor(std::vector<double> & coordinate_search_vector){

}

template<class specific_data>
void KDT<specific_data>::destroy(){
  //TODO: Recursively destroy data structure.
}

template<class specific_data>
KDT<specific_data>::KDT(std::vector<Node<specific_data>> input_list)
{
  int dimension = 0;
  MedianOfMedians<specific_data> findMedian = MedianOfMedians<specific_data>(input_list, dimension);
  for(int i = 0; i < input_list.size(); i++)
  {
    int medianIdx = floor(input_list.size()/2);
    Node<specific_data> median = findMedian.select(0, (input_list.size()-1), medianIdx);

    //    Insert the median Node
    insert(median, dimension);

    //    Remove the median Node from the input list
    input_list.erase(input_list.begin() + medianIdx);
    dimension++;
    if (dimension = numOfDimensions)
    {
      dimension = 0;
    }
    findMedian.reset(input_list, dimension);
  }
}

template<class specific_data>
KDT<specific_data>::~KDT()
{
  destroy();
}