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
  private: 
    // Data
    Node* left = NULL;
    Node* right = NULL;
    std::shared_ptr<BaseLocation> location;

    // Methods
    void destroy();

  public:
    Node(std::shared_ptr<BaseLocation> input);
    ~Node();
  friend class KDT;
};

#endif
