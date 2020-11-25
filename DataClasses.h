
#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#include <vector>
#include <string>

class BaseLocation
{
    public:
        virtual ~BaseLocation() = 0;
        std::vector<double> dimensions_data;
    protected:
        int terms;
};

class CoffeeShops : public BaseLocation
{
    private:    //data
        int stars;
        bool public_bathroom;
        bool free_wifi;
    public:     //data
        const int terms = 3;
    private:    //methods and functions

    protected:  //methods and functions

    public:     //class mechanics
        CoffeeShops(std::vector<double>& coords, std::vector<std::string>& extra, int& k);
        int getStars();
        bool getPublicBathroom();
        bool getFreeWifi();
        ~CoffeeShops();
};

class PoliceStations : public BaseLocation
{
    private:    //data
        bool is_equiped;
        bool k9;
        bool swat;
    public:     //data
        int terms = 3;
    private:    //methods and functions

    protected:  //methods and functions

    public:     //class mechanics
        PoliceStations(std::vector<double>& coords, std::vector<std::string>& extra, int& k);
        bool getIsEquiped();
        bool getK9();
        bool getSwat();
        ~PoliceStations();
};

/* struct CoffeeShops
{
    int terms = 3;
    int stars;
    bool public_bathroom;
    bool free_Wifi;
    CoffeeShops(int coordsCount, std::vector<std::string>& extraData);
    CoffeeShops();
};
struct PoliceStations
{
    int terms = 3;
    bool is_equiped;
    bool k9;
    bool swat;
    PoliceStations(int coordsCount, std::vector<std::string>& extraData);
    PoliceStations();
}; */

//To create more stucts simply define more structs!

#endif