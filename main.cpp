#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <utility>
#include <queue>
#include <cmath>

// Custom classes
#include "KDTree.h"
#include "DataProcessing.h"


int main(int argc, char *argv[])
{

  //KDT<int, Location> my_kdt;

  // Instantiating a new node
  // Node<int, Location> = new_node;
  // my_kdt.append(new_node);

  // Can create a for loop to read in data from a file,
  // create Nodes and append them.
  // for line in file:
  //      Node<int, Location> = new_node;
  //      my_kdt.append(new_node);

  //For files with extra data (ie. Coffee shops, Police stations):
  int dimensions = std::stoi(argv[2]);
  DataProcessing<CoffeeShops> DP = DataProcessing<CoffeeShops>(argv[1], dimensions);
  //For file with just coordinate data:
  //      DataProcessing DP = DataProcessing(argv[1]);
  //Can access coordinate data by:
  //      DP.coords[index]
  //Can access extra data through a map:
  //      std::map<std::string, CoffeeShops> test = DP.listOfCoffeeShops;
  //The Key to the map is the coordinates of the shop concatenated together in a string (no spaces) in the format of lowest dimenstion to highest (ie. X + Y + Z + ...)
  
  //Creating Nodes
  std::vector<double>& outputCoords = DP.coords;
  std::vector<CoffeeShops>& outputExtraData = DP.outputExtraData;
  int k = 0;
  std::vector<Node<CoffeeShops>> nodeList;
  for (int i = 0; i < outputCoords.size(); i+=dimensions)
  {
    std::vector<double> temp;
    for (int j = 0; j < dimensions; j++)
    {
      temp.push_back(outputCoords[i+j]);
    }
    nodeList.push_back(Node<CoffeeShops>(temp,outputExtraData[k]));
    k++;
    temp.clear();
  }

  KDT<CoffeeShops> test = KDT<CoffeeShops>(nodeList);
}
