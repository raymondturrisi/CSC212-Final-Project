#include "DataProcessing.h"
#include <iostream>
#include <fstream>
#include <sstream>

//Definitions of these structs are in dataStructs.h file. I had to declare them here for some reason.
CoffeeShops::CoffeeShops(int coordsCount, std::vector<std::string>& extraData)
{
    stars = std::stoi(extraData[coordsCount*terms]);
    std::istringstream(extraData[coordsCount*terms+1]) >> std::boolalpha >> public_bathroom;
    std::istringstream(extraData[coordsCount*terms+2]) >> std::boolalpha >> free_Wifi;
}

PoliceStations::PoliceStations(int coordsCount, std::vector<std::string>& extraData)
{
    std::istringstream(extraData[coordsCount*terms]) >> std::boolalpha >> is_equiped;
    std::istringstream(extraData[coordsCount*terms+1]) >> std::boolalpha >> k9;
    std::istringstream(extraData[coordsCount*terms+2]) >> std::boolalpha >> swat;
}

//Here are the DataProcessing Constructors.

DataProcessing::DataProcessing(std::string fName, int dimensions, std::string typeOfLocation)
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
    int coordCount = 0;
    if (typeOfLocation == "coffee")
    {
        for (int i = 0; i < coords.size(); i+=dimensions)
        {
            std::string keyValue = "";
            for (int j = 0; j < dimensions; j++)
            {
                keyValue += std::to_string(coords[i+j]);//concatenates unique key of coords for accessing later
            }
            listOfCoffeeShops.emplace(keyValue, CoffeeShops(coordCount, extraData));//Creating the map
            coordCount++;
        }
        coordCount = 0;
    }
    else if (typeOfLocation == "police")
    {
        for (int i = 0; i < coords.size(); i+=dimensions)
        {
            std::string keyValue = "";
            for (int j = 0; j < dimensions; j++)
            {
                keyValue += std::to_string(coords[i+j]);//concatenates unique key of coords for accessing later
            }
            listOfPoliceStations.emplace(keyValue, PoliceStations(coordCount, extraData));//Creating the map
            coordCount++;
        }
        coordCount = 0;
    }
}

DataProcessing::DataProcessing(std::string fName)
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