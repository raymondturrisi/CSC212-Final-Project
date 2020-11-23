#include "DataStructs.h"
#include <iostream>
#include <fstream>
#include <sstream>

//Definitions of these structs are in dataStructs.h file. I had to declare them here for some reason.
CoffeeShops::CoffeeShops(int coordsCount, std::vector<std::string>& extraData)
{
    stars = std::stoi(extraData[coordsCount*terms]);
    std::istringstream(extraData[coordsCount*(terms+1)]) >> std::boolalpha >> public_bathroom;
    std::istringstream(extraData[coordsCount*(terms+2)]) >> std::boolalpha >> free_Wifi;
}

PoliceStations::PoliceStations(int coordsCount, std::vector<std::string>& extraData)
{
    std::istringstream(extraData[coordsCount*terms]) >> std::boolalpha >> is_equiped;
    std::istringstream(extraData[coordsCount*(terms+1)]) >> std::boolalpha >> k9;
    std::istringstream(extraData[coordsCount*(terms+2)]) >> std::boolalpha >> swat;
}
