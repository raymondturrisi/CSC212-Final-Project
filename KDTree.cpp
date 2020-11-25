#include "KDTree.h"
#include <vector>

Node* KDT::insert(std::vector<std::shared_ptr<BaseLocation>> input_list, Node* root,  int dimension)
{
  int inputSize = input_list.size();
  if (inputSize == 1)
  {
    return new Node(input_list[0]);
  }
  if (dimension == numOfDimensions)
  {
    dimension = 0;
  }

  int medianIdx = floor(inputSize/2);
  findMedian.reset(input_list,dimension);
  std::shared_ptr<BaseLocation> median = findMedian.select(0,(inputSize-1),medianIdx);
  
  root = new Node(median);
  std::vector<std::shared_ptr<BaseLocation>> leftHalf(input_list.begin(), input_list.begin()+medianIdx);
  std::vector<std::shared_ptr<BaseLocation>> rightHalf(input_list.begin()+medianIdx+1, input_list.end());
  if (leftHalf.size() > 0)
  {
    root->left = this->insert(leftHalf, root->left, dimension+1);
  }
  if (rightHalf.size() > 0)
  {
    root->right = this->insert(rightHalf, root->right, dimension+1);
  }
  return root;
}

Node* KDT::insert(std::shared_ptr<BaseLocation> input, Node* root,  int dimension)
{
  if (dimension == numOfDimensions)
  {
    dimension = 0;
  }
  if (!root)
  {
    return new Node(input);
  }
  if(input->dimensions_data[dimension] < root->location->dimensions_data[dimension])
  {
    root->left = insert(input, root->left, dimension+1);
  }
  else
  {
    root->right = insert(input, root->right, dimension+1);
  }
  return root;
}

void KDT::insert(std::vector<std::shared_ptr<BaseLocation>>& input_list)
{
  this->root = this->insert(input_list, this->root, 0);
}

void KDT::insert(std::shared_ptr<BaseLocation>& input)
{
  this->root = this->insert(input, this->root, 0);
}

/* Node KDT::find_nearest_neighbor(std::vector<double> & coordinate_search_vector)
{

} */

void KDT::preorder(Node* root, std::ostream& os)
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

void KDT::inorder(Node* root, std::ostream& os)
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
    this->inorder(root->right, os);

    return;
}

void KDT::postorder(Node* root, std::ostream& os)
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

Node* KDT::getRoot()
{
  return this->root;
}

void KDT::destroy(){
  //TODO: Recursively destroy data structure.
}

KDT::KDT(std::vector<std::shared_ptr<BaseLocation>>& input_list, int& numOfDimensions)
: findMedian(MedianOfMedians(input_list,0))
{
    this->numOfDimensions = numOfDimensions;
    this->insert(input_list);
}

KDT::~KDT()
{
  destroy();
}