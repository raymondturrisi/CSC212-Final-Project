#include "Node.h"
#include "median.h"
#include "DataClasses.h"
#include <vector>
#include <algorithm>

#ifndef NULL
#define NULL 0x00
#endif

class KDT
{
  public :

    typedef std::vector<BaseLocation::SPtr> BaseVector;
    typedef std::vector<std::pair<BaseLocation::SPtr, double>> BaseVectorOfPairs;

  private:
    Node::SPtr root = NULL;
    int numOfDimensions = 0;
    MedianOfMedians findMedian;


    Node::SPtr insert(BaseVector& input_list, Node::SPtr& root, int dimension);
    Node::SPtr insert(BaseLocation::SPtr input, Node::SPtr& root,  int dimension);
    void insert(BaseVector& input_list);//call something else

    bool find_nearest_neighbor(std::vector<double> & coordinate_vector, int& dimension, Node::SPtr& root, int& kNeighbors, KDT::BaseVector& output, std::vector<double>& distances);
    bool find_nearest_neighbor(std::vector<double> & coordinate_vector, int& dimension, Node::SPtr& root, int& kNeighbors, KDT::BaseVector& output);
    bool addToList(BaseVectorOfPairs& output, int& kNeighbors, BaseLocation::SPtr loc);
    bool addToList(BaseVector& output, int& kNeighbors, BaseLocation::SPtr loc);


    void destroy();
  public:
<<<<<<< HEAD
    KDT(BaseVector& input_list, int& numOfDimensions);
    //KDT() single element
    //KDT() empty
    void insert(BaseLocation::SPtr& input);
    //void insert(vector)
    BaseVectorOfPairs find_nearest_neighbor(std::vector<double> & coordinate_vector, int& kNeighbors, bool& distance);
    BaseVector find_nearest_neighbor(std::vector<double> & coordinate_vector, int& kNeighbors);
    void preorder(Node::SPtr& root, std::ostream& os);
    void postorder(Node::SPtr& root, std::ostream& os);
    void inorder(Node::SPtr& root, std::ostream& os);
    void inorderDot(Node::SPtr& root, std::ostream& os);
    Node::SPtr& getRoot();
/*
// copy constructor (always override default for safety, even if coincident)
KDT(const KDT &arg)
{
     //root = std::move(arg.root);
     root = arg.root;
     numOfDimensions = arg.numOfDimensions;
     findMedian = arg.findMedian;
=======
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
>>>>>>> d244cab7d8c25f6fc643fc80ec2ba0a85d7b7578
}

// copy assignment operator (member method, argument by constant reference) [5]p198
// always override compiler generated default for safety, even if coincident
KDT& operator=(const KDT &rhs)
{
if ( this != &rhs ) // avoid assignment to self [2]c17 [5]p238
 {
 // make assignments for all members (including base class members) [2]c16
     //root = std::move(rhs.root);
     root = rhs.root;
     numOfDimensions = rhs.numOfDimensions;
     findMedian = rhs.findMedian;
 }
return *this; // always return a reference to *this [2]c15
}
 */

    ~KDT();
};
=======
#include "Node.h"
#include "median.h"
#include "DataClasses.h"
#include <vector>
#include <algorithm>

#ifndef NULL
#define NULL 0x00
#endif

class KDT
{
  public :
    //Typedefs
    typedef std::vector<BaseLocation::SPtr> BaseVector;
    typedef std::vector<std::pair<BaseLocation::SPtr, double>> BaseVectorOfPairs;

  private:
    //Data
    Node::SPtr root = NULL;
    int numOfDimensions = 0;
    int depthOfTree = 0;
    int numOfNodes = 0;
    MedianOfMedians findMedian;

    //Insert Methods
    Node::SPtr insertDuringConstruct(BaseVector& input_list, Node::SPtr& root, int dimension);
    Node::SPtr insert(BaseLocation::SPtr input, Node::SPtr& root,  int dimension);

    //Nearest Neighbr methods
    bool find_nearest_neighbor(std::vector<double> & coordinate_vector, int& dimension, Node::SPtr& root, int& kNeighbors, BaseVector& output, std::vector<double>& distances);
    bool find_nearest_neighbor(std::vector<double> & coordinate_vector, int& dimension, Node::SPtr& root, int& kNeighbors, BaseVector& output);
    //bool addToList(BaseVectorOfPairs& output, int& kNeighbors, BaseLocation::SPtr loc);
    //bool addToList(BaseVector& output, int& kNeighbors, BaseLocation::SPtr loc);
  public:
    //Constructors and Destructors
    KDT(BaseVector& input_list, int& numOfDimensions);
    KDT(BaseLocation::SPtr& input, int& numOfDimensions);
    KDT();
    ~KDT();

    //Insert Methods
    void insert(BaseLocation::SPtr& input, int& dimensions);//Insert single location
    void insert(BaseVector& input_list, int& dimensions); //Insert a vector of locations

    //Nearest Neighbors Methods
    BaseVectorOfPairs find_nearest_neighbor(std::vector<double> & coordinate_vector, int& kNeighbors, bool& distance);
    BaseVector find_nearest_neighbor(std::vector<double> & coordinate_vector, int& kNeighbors);

    //Printing methods
    void preorder(Node::SPtr& root, std::ostream& os);
    void postorder(Node::SPtr& root, std::ostream& os);
    void inorder(Node::SPtr& root, std::ostream& os);

    //Access methods
    Node::SPtr& getRoot();

};
>>>>>>> 477a8341203f1aaff8ec3f24c2a16c43db49776c
