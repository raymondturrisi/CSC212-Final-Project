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
  if (argc == 0)
  {
    std::cout<< "Please input data in the form of: /n {File name}, {# of Dimensions} /n OR /n {File name}"<< std::endl;
  }

  //For files with extra data (ie. Coffee shops, Police stations):
  int dimensions = std::stoi(argv[2]);
  DataProcessing<CoffeeShops> DP = DataProcessing<CoffeeShops>(argv[1], dimensions);
  //For file with just coordinate data:
  //      DataProcessing DP = DataProcessing(argv[1]);
  //Can access coordinate data by:
  //      DP.coords[index]
  //      DP.outputExtraData[index]
  
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

  KDT<CoffeeShops> test = KDT<CoffeeShops>(nodeList, dimensions);
}
