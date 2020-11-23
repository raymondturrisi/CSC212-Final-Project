#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

#include <vector>
#include <string>
#include <map>

#include "dataStructs.h"

template<class specific_data>
class DataProcessing
{
    private:
        std::vector<std::string> extraData;//internal vector for collecting the extra data
    public:
        DataProcessing(std::string fname, int dimensions);//Process files with coords + extra data
        DataProcessing(std::string fname);//Process files with just coords

        std::vector<double> coords;//coords
        std::vector<specific_data> outputExtraData;
        //std::vector<PoliceStations> listOfPoliceStations;

        //String will be all coords concatenated together ex(x = 6.4 y = 7.23 z = 9.6 would be a string "6.47.239.6"
        //and would serve as a unique identifier) 
        //std::map<std::string, CoffeeShops> listOfCoffeeShops;//All extra data mapped to their coords
        //std::map<std::string, PoliceStations> listOfPoliceStations;//All extra data mapped to their coords
        //To add more locations to handle just add more maps. Make sure you define the structs in dataStructs.h
        
};

template<class specific_data>
DataProcessing<specific_data>::DataProcessing(std::string fName, int dimensions)
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
    for (int i = 0; i < coords.size(); i+=dimensions)
    {
        extraData.push_back(specific_data(coordCount, extraData));
    }
    /* if (typeOfLocation == "coffee")
    {
        for (int i = 0; i < coords.size(); i+=dimensions)
        {
            std::string keyValue = "";
            for (int j = 0; j < dimensions; j++)
            {
                keyValue += std::to_string(coords[i+j]);//concatenates unique key of coords for accessing later
            }
            listOfCoffeeShops.emplace(keyValue, CoffeeShops(coordCount, extraData));//Creating the map
            listOfCoffeeShops.push_back(CoffeeShops(coordCount, extraData));
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
            listOfPoliceStations.push_back(PoliceStations(coordCount, extraData));
            coordCount++;
        }
        coordCount = 0;
    } */
    //For more locations simply add more else-if statements with the code above copied, make sure to properly change
    //listOf[BLANK] to proper location and confirm that you are emplacing the right struct.
}

template<class specific_data>
DataProcessing<specific_data>::DataProcessing(std::string fName)
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


#endif