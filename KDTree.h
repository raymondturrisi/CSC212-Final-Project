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
  private:
    Node* root = NULL;
    int numOfDimensions = 0;
    MedianOfMedians findMedian;


    Node* insert(std::vector<std::shared_ptr<BaseLocation>> input_list, Node* root, int dimension);
    Node* insert(std::shared_ptr<BaseLocation> input, Node* root,  int dimension);
    Node find_nearest_neighbor(std::vector<double> & coordinate_vector);
    void insert(std::vector<std::shared_ptr<BaseLocation>>& input_list);

    void destroy();
  public:
    KDT(std::vector<std::shared_ptr<BaseLocation>>& input_list, int& numOfDimensions);
    void insert(std::shared_ptr<BaseLocation>& input);
    void preorder(Node* root, std::ostream& os);
    void postorder(Node* root, std::ostream& os);
    void inorder(Node* root, std::ostream& os);
    Node* getRoot();

    ~KDT();
};
