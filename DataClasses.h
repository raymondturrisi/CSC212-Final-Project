
#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#include <vector>
#include <string>
#include <memory>

class BaseLocation//Abstract class
{
    public:
        typedef std::shared_ptr<BaseLocation> SPtr;

    public:
        std::vector<double> dimensions_data;
        
    protected:
        int terms;

    public:

        virtual ~BaseLocation() = 0;

        BaseLocation() : terms(-1)
        { }

        BaseLocation(const BaseLocation& other)
            : terms(other.terms)
        {
            dimensions_data = other.dimensions_data;
        }

 /*       BaseLocation(BaseLocation&& other)
            : p{ other.p }
        {
            other.p = nullptr;
        }*/

        BaseLocation& operator=(const BaseLocation& other)
        {
            if (&other != this) {
                terms = other.terms;
                dimensions_data = other.dimensions_data;
            }
            return *this;
        }

        //BaseLocation& operator=(BaseLocation&& other)
        //{
        //    if (&other != this) {
        //        delete p;
        //        p = other.p;
        //        other.p = nullptr;
        //    }
        //    return *this;
        //}
};

class DefaultLocation : public BaseLocation
{

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

        CoffeeShops(const CoffeeShops& other)
            : BaseLocation(other)
        {
            this->stars = other.stars;
            this->public_bathroom = other.public_bathroom;
            this->free_wifi = other.free_wifi;
        }

        CoffeeShops& operator=(const CoffeeShops& other)
        {
            if (&other != this) {
                this->stars = other.stars;
                this->public_bathroom = other.public_bathroom;
                this->free_wifi = other.free_wifi;
            }
            return *this;
        }
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

        PoliceStations(const PoliceStations& other)
            : BaseLocation(other)
        {
            this->is_equiped = other.is_equiped;
            this->k9 = other.k9;
            this->swat = other.swat;
        }

        PoliceStations& operator=(const PoliceStations& other)
        {
            if (&other != this) {
                this->is_equiped = other.is_equiped;
                this->k9 = other.k9;
                this->swat = other.swat;
            }
            return *this;
        }
};
#endif