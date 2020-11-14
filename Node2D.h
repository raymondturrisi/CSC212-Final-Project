
template<class data_type>
class Node2D {

  private:
    int x, y;

    data_type * left, right;

  public:
    Node2D();
    ~Node2D();

};

// Note: These function definitions must be placed in the same file as the class
// declaration, a restriction which occurs when using templated classes.

template<class data_type> Node2D<data_type>::Node2D(){

}

template<class data_type> Node2D<data_type>::~Node2D(){

}
