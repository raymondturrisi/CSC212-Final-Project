#ifndef KDTREE_CLASS
#define KDTREE_CLASS

#include "Node.hpp"

template <class t>
class KDTree {
    private:
        Node* head = nullptr;
        int nodes = 0;
        int depth = 0;
    public:
        //constructors
        KDTree<t>() {
            this->head = new Node();
        }
        KDTree<t>(t data) {
            //for insantiating a new KDtree
            this->head = new Node(data);
            this->node++;
        }

        //insert

        void insert(Node<t> moving_node, t dat, bool on_x_Axis) {
            //base case, reaches nullptr
            if(!moving_node->left_child) {
                moving_node->left_child = new Node<t>(dat);
                return;
            }
            if(!moving_node->right_child) {
                moving_node->right_child = new Node<t>(dat);
            }

            if(on_x_Axis) {
                if(if)
            }
        }
        //remove

        KDTree<t>(std::vector<t> vector_of_structs) {
            //builds a balanced KD tree from a vector of structs

            //to do this, you find the medians of all the x's and y's - this will be stored in a vector of points (see dataStructs.hpp)
            //this struct has a point, and the pointer to the node which it belongs to
            //sort the structs w/rt x and y
            //insert the medians of the points with the insert function
        }

        //balance

        //nearest neighbor

        //post-order

        //inorder

        //preorder
}

#endif