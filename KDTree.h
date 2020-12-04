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
