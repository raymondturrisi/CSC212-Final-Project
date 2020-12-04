#include "KDTree.h"
#include <vector>

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
Node::SPtr KDT::insert(KDT::BaseVector& input_list, Node::SPtr& root,  int dimension)//vector
{
  int inputSize = input_list.size();
  if (inputSize == 1)
  {
    return std::make_unique<Node>(input_list[0]);
  }
  if (dimension == numOfDimensions)
  {
    dimension = 0;
  }

  int medianIdx = floor(inputSize/2);
  findMedian.reset(input_list, dimension);
  BaseLocation::SPtr median = findMedian.select(0,(inputSize-1),medianIdx);
  
  root = std::make_unique<Node>(median);
  KDT::BaseVector leftHalf(input_list.begin(), input_list.begin()+medianIdx);
  KDT::BaseVector rightHalf(input_list.begin()+medianIdx+1, input_list.end());
  if (leftHalf.size() > 0)
  {
    root->left = this->insert(leftHalf, root->left, dimension+1);
  }
  if (rightHalf.size() > 0)
  {
    root->right = this->insert(rightHalf, root->right, dimension+1);
  }
  return std::move(root);
}

Node::SPtr KDT::insert(BaseLocation::SPtr input, Node::SPtr& root,  int dimension)
{
  if (dimension == numOfDimensions)
  {
    dimension = 0;
  }
  if (!root)
  {
    return std::make_unique<Node>(input);
  }
  if(input->dimensions_data[dimension] < root->location->dimensions_data[dimension])
  {
    root->left = insert(input, root->left, dimension+1);
  }
  else
  {
    root->right = insert(input, root->right, dimension+1);
  }
  return std::move(root);
}

void KDT::insert(KDT::BaseVector& input_list)//vector
{
  this->root = this->insert(input_list, this->root, 0);
}

void KDT::insert(BaseLocation::SPtr& input)//single location
{
  this->root = this->insert(input, this->root, 0);
}

/* Node KDT::find_nearest_neighbor(std::vector<double> & coordinate_search_vector)
{

} */

void KDT::preorder(Node::SPtr& root, std::ostream& os)
{
  if(!root)
  {
      return;
  }
  for (int i = 0; i < numOfDimensions; i++)
  {
    os << root->location->dimensions_data[i] << ", ";
  }
  this->preorder(root->left, os);
  this->preorder(root->right, os);

  return;
}

void KDT::inorder(Node::SPtr& root, std::ostream& os)
{
    if(!root)
    {
        return;
    }

    this->inorder(root->left, os);
    for (int i = 0; i < numOfDimensions; i++)
    {
      os << root->location->dimensions_data[i] << ", ";
    }
    os << std::endl;
    this->inorder(root->right, os);

    return;
}

void KDT::inorderDot(Node::SPtr& root, std::ostream& os)
{
    if(!root)
    {
        return;
    }

    this->inorderDot(root->left, os);
    if (root->left)
    {
      os << "<" << root->location->dimensions_data[0] << "," << root->location->dimensions_data[1] << "> -> <" << root->left->location->dimensions_data[0] << "," << root->left->location->dimensions_data[1] << ">;" << "\n";
    }
    if (root->right)
    {
      os << "<" << root->location->dimensions_data[0] << "," << root->location->dimensions_data[1] << "> -> <" << root->right->location->dimensions_data[0] << "," << root->right->location->dimensions_data[1] << ">;"  << "\n";
    }
    this->inorderDot(root->right, os);

    return;
}

void KDT::postorder(Node::SPtr& root, std::ostream& os)
{
    if(!root)
    {
        return;
    }

    this->postorder(root->left, os);
    this->postorder(root->right, os);
    for (int i = 0; i < numOfDimensions; i++)
    {
      os << root->location->dimensions_data[i] << ", ";
    }

    return;
}

Node::SPtr& KDT::getRoot()
{
  return this->root;
}

void KDT::destroy(){
  //TODO: Recursively destroy data structure.
}

KDT::KDT(KDT::BaseVector& input_list, int& numOfDimensions)
: findMedian(MedianOfMedians(input_list,0))
{
    this->numOfDimensions = numOfDimensions;
    this->insert(input_list);
}

KDT::~KDT()
{
  destroy();
}