#include <vector>
#include <string>
#include <map>

#include "DataClasses.h"


class DataProcessing
{
    public:
        //Class Mechanics
        DataProcessing(std::string fname, int dimensions);//Process files with coords + extra data
        DataProcessing(std::string fname);//Process files with just coords

        //Data
        std::vector<double> coords;//coords
        std::vector<std::string> extraData;//extra data
};


DataProcessing::DataProcessing(std::string fName, int dimensions)
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
