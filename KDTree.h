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
