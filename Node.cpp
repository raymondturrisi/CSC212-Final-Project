#include "Node.h"
#include "DataClasses.h"
#include <vector>



Node::Node(BaseLocation::SPtr input)
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
