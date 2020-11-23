
#ifndef DATA_STRUCTS
#define DATA_STRUCTS

//#include "Node.hpp"

struct point {
    float p = -99;
    void *node;

    point(float _p, void *_node) {
        this->p = _p;
        this->node = _node;
    }
};


struct coffeeShops {
    float x = -99;
    float y = -99;
    coffeeShops() {
        
    }
    coffeeShops(float _x, float _y) {
        this->x = _x;
        this->y = _y;

    }
};

struct emResponse {
    float x = -99;
    float y = -99;
    emResponse(float _x, float _y) {
        this->x = _x;
        this->y = _y;
    }
};


#endif