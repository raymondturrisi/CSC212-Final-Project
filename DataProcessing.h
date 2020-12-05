#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

#include <vector>
#include <string>
#include <map>

#include "dataStructs.h"

class DataProcessing
{
    private:
        std::vector<std::string> extraData;//internal vector for collecting the extra data
    public:
        DataProcessing(std::string fname, int dimensions, std::string typeOfLocation);//Process files with coords + extra data
        DataProcessing(std::string fname);//Process files with just coords

        std::vector<double> coords;//coords

        //String will be all coords concatenated together ex(x = 6.4 y = 7.23 z = 9.6 would be a string "6.47.239.6"
        //and would serve as a unique identifier)
        std::map<std::string, CoffeeShops> listOfCoffeeShops;//All extra data mapped to their coords
        std::map<std::string, PoliceStations> listOfPoliceStations;//All extra data mapped to their coords
        //To add more locations to handle just add more maps. Make sure you define the structs in dataStructs.h

};


#endif
