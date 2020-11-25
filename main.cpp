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

  //For files with extra data (ie. Coffee shops, Police stations):
  int dimensions = std::stoi(argv[2]);
  std::vector<double> coords;
  std::vector<std::string> extraData;
  int dimensions2 = std::stoi(argv[4]);
  std::vector<double> coords2;
  std::vector<std::string> extraData2;
  withExtra(argv[1], dimensions, coords, extraData);
  withExtra(argv[3], dimensions2, coords2, extraData2);
  //regularData(argv[1], coords);
  
  int k = 0;
  std::vector<std::shared_ptr<BaseLocation>> locationList;
  for (int i = 0; i < coords.size(); i+=dimensions)
  {
    std::vector<double> temp;
    for (int j = 0; j < dimensions; j++)
    {
      temp.push_back(coords[i+j]);
    }
    locationList.push_back(std::shared_ptr<CoffeeShops>(new CoffeeShops(temp,extraData,k)));
    k++;
    temp.clear();
  }
  k = 0;
  for (int i = 0; i < coords2.size(); i+=dimensions2)
  {
    std::vector<double> temp;
    for (int j = 0; j < dimensions2; j++)
    {
      temp.push_back(coords2[i+j]);
    }
    locationList.push_back(std::shared_ptr<PoliceStations>(new PoliceStations(temp,extraData2,k)));
    k++;
    temp.clear();
  }

  KDT test = KDT(locationList, dimensions);
  std::ostringstream oss;
  test.inorder(test.getRoot(), oss);
  std::cout << oss.str() << std::endl;
}

