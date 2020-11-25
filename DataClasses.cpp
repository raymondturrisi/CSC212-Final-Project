#include "DataClasses.h"
#include <sstream>

BaseLocation::~BaseLocation()
{

}

CoffeeShops::CoffeeShops(std::vector<double>& coords, std::vector<std::string>& extra, int& k)
{
    this->dimensions_data = coords;//makes a copy
    this->stars = std::stoi(extra[k*this->terms]);
    std::istringstream(extra[k*this->terms+1]) >> std::boolalpha >> this->public_bathroom;
    std::istringstream(extra[k*this->terms+2]) >> std::boolalpha >> this->free_wifi;
}
int CoffeeShops::getStars()
{
    return this->stars;
}
bool CoffeeShops::getPublicBathroom()
{
    return this->public_bathroom;
}
bool CoffeeShops::getFreeWifi()
{
    return this->free_wifi;
}

CoffeeShops::~CoffeeShops()
{

}

PoliceStations::PoliceStations(std::vector<double>& coords, std::vector<std::string>& extra, int& k)
{
    this->dimensions_data = coords;//makes a copy
    std::istringstream(extra[k*this->terms]) >> std::boolalpha >> is_equiped;
    std::istringstream(extra[k*this->terms+1]) >> std::boolalpha >> k9;
    std::istringstream(extra[k*this->terms+2]) >> std::boolalpha >> swat;
}
bool PoliceStations::getIsEquiped()
{
    return this->is_equiped;
}
bool PoliceStations::getK9()
{
    return this->k9;
}
bool PoliceStations::getSwat()
{
    return this->swat;
}

PoliceStations::~PoliceStations()
{
}