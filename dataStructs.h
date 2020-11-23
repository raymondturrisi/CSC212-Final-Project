#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#include <vector>
#include <string>

//Data types that we can handle. To add more simply add more structs here and define the constuctor in the 
//DataProcessing.cpp file. For some reason I have to declare them in that file and not a dataStructs.cpp file
//and idk why but it works.

struct CoffeeShops
{
    int terms = 3;
    int stars;
    bool public_bathroom;
    bool free_Wifi;
    CoffeeShops(int coordsCount, std::vector<std::string>& extraData);
};
struct PoliceStations
{
    int terms = 3;
    bool is_equiped;
    bool k9;
    bool swat;
    PoliceStations(int coordsCount, std::vector<std::string>& extraData);
};

//To create more stucts simply define more structs!

#endif