#include "Node.h"
#include <vector>
#ifndef NULL
#define NULL 0x00
#endif

class KDT {

  private:
    Node * root_node = 0x00;

    void insert(std::vector<Node> & input_list);
    void insert(Node input);

    Node find();

    void destroy();

  public:
    KDT();
    ~KDT();

};

// Note: These function definitions must be placed in the same file as the class
// declaration, a restriction which occurs when using templated classes.

void KDT::insert(std::vector<Node> & input_list){

}

void KDT::insert(Node input){

}

Node KDT::find(){

}

void KDT::destroy(){

}

KDT::KDT(){

}

KDT::~KDT(){
  destroy();
}
