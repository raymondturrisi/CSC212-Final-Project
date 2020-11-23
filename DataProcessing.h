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
        outputExtraData.push_back(specific_data(coordCount, extraData));
    }
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
