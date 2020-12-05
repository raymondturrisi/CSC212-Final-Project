#include "KDTree.h"
#include <vector>

//PRIVATE METHODS:
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



/* bool KDT::find_nearest_neighbor(std::vector<double> & coordinate_vector, int& dimension, Node::SPtr& root, int& kNeighbors, KDT::BaseVectorOfPairs& output, std::vector<double>& distances)
{
  if (dimension == numOfDimensions)
  {
    dimension = 0;
  }
  if (!root)
  {
    return true;
  }
  if (coordinate_vector[dimension] < root->location->dimensions_data[dimension])
  {
    if(output.size() < kNeighbors)
    {

    }
  }
}

KDT::BaseVector KDT::find_nearest_neighbor(std::vector<double> & coordinate_vector, int& dimension, Node::SPtr& root, int& kNeighbors, BaseVector output)
{

}

KDT::BaseVector KDT::find_nearest_neighbor(std::vector<double> & coordinate_vector, int& kNeighbors)
{
  int dimension = 0;
  KDT::BaseVector output(kNeighbors);
  find_nearest_neighbor(coordinate_vector, dimension, this->root, kNeighbors, output);
}

KDT::BaseVectorOfPairs KDT::find_nearest_neighbor(std::vector<double> & coordinate_vector, int& kNeighbors, bool& distance)
{
  int dimension = 0;
  KDT::BaseVector output(kNeighbors);
  std::vector<double> distances(kNeighbors);
  find_nearest_neighbor(coordinate_vector, dimension, this->root, kNeighbors, output, distance);
}
 */

//Insert method called at construction if input is a vector of locations
//Via the medians of medians algorithm method
//Allows the creation of a balanced tree in nlog(n) time from an unsorted list
Node::SPtr KDT::insertDuringConstruct(BaseVector& input_list, Node::SPtr& root,  int depth)
{
  int inputSize = input_list.size();

  //Keeps track of depth of tree
  if (depth > depthOfTree)
  {
    depthOfTree = depth;
  }

  //If it is a vector of size 1 just return a new node
  if (inputSize == 1)
  {
    numOfNodes++;
    return std::make_shared<Node>(input_list[0]);
  }

  //Compute what the median index of the array should be
  //An even array selects the index skewed right
  //ex {10,11,12,13} would select index 2 as size is 4, picking value 12 as median 
  int medianIdx = floor(inputSize/2);

  //Resets the median of medians algorithm to operate on correct list and at the correct dimension
  findMedian.reset(input_list, depth%numOfDimensions);

  //Returns out the value of the median and reorders the list so all values less than median are placed to the left of the median and all values greater than to the right
  BaseLocation::SPtr median = findMedian.select(0,(inputSize-1),medianIdx);
  
  //Places median value in node
  root = std::make_shared<Node>(median);
  numOfNodes++;

  //Creates new vectors with the left half (all values less than median) and right half (all values greater than median), ignoring the median value
  BaseVector leftHalf(input_list.begin(), input_list.begin()+medianIdx);
  BaseVector rightHalf(input_list.begin()+medianIdx+1, input_list.end());


  if (leftHalf.size() > 0)
  {
    root->left = this->insertDuringConstruct(leftHalf, root->left, depth+1);//Recursively operates on left half of vector
  }
  if (rightHalf.size() > 0)
  {
    root->right = this->insertDuringConstruct(rightHalf, root->right, depth+1);//Recursively operates on right half of vector
  }
  return root;
}

//For inserting a node one at a time, this method cannot guarentee that the tree will be balanced
Node::SPtr KDT::insert(BaseLocation::SPtr input, Node::SPtr& root,  int depth)
{
  if (!root)
  {
    numOfNodes++;
    return std::make_shared<Node>(input);
  }
  if(input->dimensions_data[depth%numOfDimensions] < root->location->dimensions_data[depth%numOfDimensions])//If input is less than root go to the left node
  {
    root->left = insert(input, root->left, depth+1);
  }
  else //If input is greater than or equal to the root then go to the right node
  {
    root->right = insert(input, root->right, depth+1);
  }
  return root;
}


//PUBLIC METHODS:
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



//Inserting a vector into tree
//Checks to see if the root is empty, if so treats it as a constructor call and builds a balanced tree
//If root is already there calls the regular insert method, does not guarentee a balanced tree
void KDT::insert(BaseVector& input_list, int& dimensions)
{
  if (dimensions != numOfDimensions)
  {
    std::cout << "This tree contains objects with " << numOfDimensions << " dimensions. You cannot insert a object of " << dimensions << " into this tree." << std::endl;
  }
  else
  {
    if (!root)
    {
      this->root = this->insertDuringConstruct(input_list, this->root, 0);
    }
    else
    {
      for (BaseLocation::SPtr loc : input_list)
      {
        this->root = this->insert(loc, this->root, 0);
      }
    }
  }
}

//Inserting a single locaiton into the tree
void KDT::insert(BaseLocation::SPtr& input, int& dimensions)
{
  if (dimensions != numOfDimensions)
  {
    std::cout << "This tree contains objects with " << numOfDimensions << " dimensions. You cannot insert a object of " << dimensions << " into this tree." << std::endl;
  }
  else
  {
    this->root = this->insert(input, this->root, 0);
  }
}

//Prints the tree in a preorder method in the .dot file format
void KDT::preorder(Node::SPtr& root, std::ostream& os)
{
  if(!root)
  {
      return;
  }
  if (root->left)
  {
    os << "<" << root->location->dimensions_data[0] << "," << root->location->dimensions_data[1] << "> -> <" << root->left->location->dimensions_data[0] << "," << root->left->location->dimensions_data[1] << ">;" << std::endl;
  }
  if (root->right)
  {
    os << "<" << root->location->dimensions_data[0] << "," << root->location->dimensions_data[1] << "> -> <" << root->right->location->dimensions_data[0] << "," << root->right->location->dimensions_data[1] << ">;"  << std::endl;
  }
  this->preorder(root->left, os);
  this->preorder(root->right, os);

  return;
}

//Prints the tree in a inorder method in the .dot file format
void KDT::inorder(Node::SPtr& root, std::ostream& os)
{
    if(!root)
    {
        return;
    }

    this->inorder(root->left, os);
    if (root->left)
    {
      os << "<" << root->location->dimensions_data[0] << "," << root->location->dimensions_data[1] << "> -> <" << root->left->location->dimensions_data[0] << "," << root->left->location->dimensions_data[1] << ">;" << std::endl;
    }
    if (root->right)
    {
      os << "<" << root->location->dimensions_data[0] << "," << root->location->dimensions_data[1] << "> -> <" << root->right->location->dimensions_data[0] << "," << root->right->location->dimensions_data[1] << ">;" << std::endl;
    }
    this->inorder(root->right, os);

    return;
}

//Prints the tree in a postorder method in the .dot file format
void KDT::postorder(Node::SPtr& root, std::ostream& os)
{
    if(!root)
    {
        return;
    }

    this->postorder(root->left, os);
    this->postorder(root->right, os);
    if (root->left)
    {
      os << "<" << root->location->dimensions_data[0] << "," << root->location->dimensions_data[1] << "> -> <" << root->left->location->dimensions_data[0] << "," << root->left->location->dimensions_data[1] << ">;" << std::endl;
    }
    if (root->right)
    {
      os << "<" << root->location->dimensions_data[0] << "," << root->location->dimensions_data[1] << "> -> <" << root->right->location->dimensions_data[0] << "," << root->right->location->dimensions_data[1] << ">;"  << std::endl;
    }

    return;
}

//Returns the root object
Node::SPtr& KDT::getRoot()
{
  return this->root;
}


//CONSTRUCTORS / DESTRUCTORS:
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



KDT::KDT(BaseVector& input_list, int& numOfDimensions)
: findMedian(MedianOfMedians(input_list,0))
{
    this->numOfDimensions = numOfDimensions;
    this->insertDuringConstruct(input_list, this->root, 0);
}

KDT::KDT(BaseLocation::SPtr& input, int& numOfDimensions)
: findMedian(MedianOfMedians())
{
  this->numOfDimensions = numOfDimensions;
  this->insert(input, numOfDimensions);
}

KDT::KDT()
: findMedian(MedianOfMedians())
{
}

KDT::~KDT()//I don't know how to make destructor for this, think we can just delete root and then delete the tree and be all good?
{
  //delete this;// :(
}