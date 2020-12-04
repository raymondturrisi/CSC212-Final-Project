#ifndef MEDIAN_H
#define MEDIAN_H
#include <vector>
#include <memory>
#include "DataClasses.h"

#ifndef NULL
#define NULL nullptr
#endif


class Node
{
  friend class KDT;
  public: //Typedefs (have to be defined first)
    typedef std::shared_ptr<Node> SPtr;
  private:
    // Data
    Node::SPtr left = NULL;
    Node::SPtr right = NULL;
    BaseLocation::SPtr location;

    // Methods
    void destroy();

  public: //Class Mechanics
    Node(BaseLocation::SPtr input);
    ~Node();
};

#endif
