#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <utility>
#include <queue>
#include <cmath>
#include <memory>

// Custom classes
#include "KDTree.h"

void withExtra(std::string fName, int dimensions, std::vector<double>& coords, std::vector<std::string>& extraData)
{
    int val = 0;
    int count = 0;
    std::string data;
    std::ifstream infile(fName);
    std::string line;
    //Puts data into vectors
    while (std::getline(infile, line)) 
    {
        std::stringstream myss(line);
        while (count < dimensions && myss >> val) 
        {
            count++;
            coords.push_back(val);
        }
        count = 0;
        while (myss >> data)//puts extra data into extraData vector
        {
            extraData.push_back(data);
        }
    }
}


void regularData(std::string fName, std::vector<double>& coords)
{
    int val;
    std::ifstream infile(fName);
    std::string line;
    while (std::getline(infile, line)) 
    {
        std::stringstream myss(line);
        while (myss >> val) 
        {
            coords.push_back(val);
        }
    }
}


int main(int argc, char *argv[])
{
  if (argc == 0)
  {
    std::cout<< "Please input data in the form of: /n {File name}, {# of Dimensions} /n OR /n {File name}"<< std::endl;
  }

  //CURRENT SETUP:
  //Two Files (with same number of dimensions) into one tree

  //For files with extra data (ie. Coffee shops, Police stations):

  int dimensions = std::stoi(argv[2]);//dimensions of first file
  std::vector<double> coords;//coords of first file
  std::vector<std::string> extraData;//extra data of first file


  int dimensions2 = std::stoi(argv[4]);//dimensions of second file
  std::vector<double> coords2;//coords of second file
  std::vector<std::string> extraData2;//extra data of second file

  //Assign coords and extra data to appropriate vectors
  withExtra(argv[1], dimensions, coords, extraData);
  withExtra(argv[3], dimensions2, coords2, extraData2);

  //If you had a tree without extra data
  //regularData(argv[1], coords);
  

  //BUILDING THE VECTORS
  //For every object type you will have to build it in a different for loop
  //If two files have different number of dimensions you cannot combine them in the same tree like I am doing below

  //Coffee Shop vector
  int k = 0;
  KDT::BaseVector locationList;
  for (int i = 0; i < coords.size(); i+=dimensions)
  {
    std::vector<double> temp;
    for (int j = 0; j < dimensions; j++)
    {
      temp.push_back(coords[i+j]);
    }
    locationList.push_back(std::make_shared<CoffeeShops>(temp,extraData,k));
    k++;
    temp.clear();
  }

  //Police Shop Vector
  k = 0;
  for (int i = 0; i < coords2.size(); i+=dimensions2)
  {
    std::vector<double> temp;
    for (int j = 0; j < dimensions2; j++)
    {
      temp.push_back(coords2[i+j]);
    }
    locationList.push_back(std::make_shared<PoliceStations>(temp,extraData2,k));
    k++;
    temp.clear();
  }

  //Create tree and initialize it with locations list and the number of dimensions
  KDT test = KDT(locationList, dimensions);

  //Printing the tree
  std::ostringstream oss;
  test.inorder(test.getRoot(), oss);
  std::cout << oss.str() << std::endl;
}

