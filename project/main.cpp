/*
 * Raymond Turrisi, Alfred Timperley, Brennan Richards
 * Main test file: open the data and flex on dees methods
 *
 *
 *
*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <signal.h>

#include "Node.hpp"
#include "dataStructs.hpp"
#include "KDTree.hpp"


int main(int argc, char *argv[]) {
    //declares inputs
    char* input_file = argv[1];
    //declares some important variables
    std::string line;
    std::string entry;
    std::ifstream inname(input_file);
    std::vector<coffeeShops> data;
    float x, y;
    int i = 0;
    //gets input from file (coffeeShops.txt)
    while(std::getline(inname, line)) {
        std::istringstream streamline(line);
        i = 0;
        while(std::getline(streamline, entry, ',')) {
            if(i == 0) {
                x = std::stof(entry);
            } else {
                y = std::stof(entry);
            }
            i++;
            data.push_back(coffeeShops(x,y));
        }
    }

    //prints x and y coordinates from data, received
    /*
    for(int i = 0; i < data.size(); i++) {
        std::cout << data[i].x << " " << data[i].y << std::endl;
    }
    */
    Node<coffeeShops> node(data[1]);

    node.print_cords();






    return 0;
}