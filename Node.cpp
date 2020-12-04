#include "Node.h"
#include "DataClasses.h"
#include <vector>



Node::Node(std::shared_ptr<BaseLocation> input)
    : location(input)
{
}

Node::~Node(){
  destroy();
}

void Node::destroy()
{
  //code
}