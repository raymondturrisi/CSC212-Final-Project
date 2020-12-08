#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <map>
#include <chrono>
// Custom classes
#include "KDTree.hpp"
#include "dataStructs.hpp"
#include "Node.hpp"

//Returns vector of locations
std::vector<DefaultLocation> getData(std::string fname);
std::string pwd_for_cpp();

void withExtra(std::string fName, int dimensions, std::vector<long double>& coords, std::vector<std::string>& extraData)
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
        std::string entry;
        while (count < dimensions && std::getline(myss, entry, ','))
        {
            count++;
            coords.push_back(std::stod(entry));
        }
        count = 0;
        while (std::getline(myss, entry, ','))//puts extra data into extraData vector
        {
            extraData.push_back(entry);
        }
    }
}

int main(int argc, char *args[])
{
  if (argc == 0)
  {
    std::cout<< "Please input data in the form of: /n {File name}, {# of Dimensions} /n OR /n {File name}"<< std::endl;
  }

  //CURRENT SETUP:
  //Two Files (with same number of dimensions) into one tree

  //For files with extra data (ie. Coffee shops, Police stations):

  int dimensions = std::stoi(args[1]);//dimensions of files
  std::vector<long double> coords;//coords of first file
  std::vector<std::string> extraData;//extra data of first file

  //Assign coords and extra data to appropriate vectors
  withExtra(args[2], dimensions, coords, extraData);
  /*withExtra(argv[3], dimensions, coords, extraData);
  withExtra(argv[4], dimensions, coords, extraData);
  withExtra(argv[5], dimensions, coords, extraData);
  withExtra(argv[6], dimensions, coords, extraData);
  withExtra(argv[7], dimensions, coords, extraData);
  withExtra(argv[8], dimensions, coords, extraData);
  withExtra(argv[9], dimensions, coords, extraData);
  withExtra(argv[10], dimensions, coords, extraData);
  withExtra(argv[11], dimensions, coords, extraData);
  withExtra(argv[12], dimensions, coords, extraData);
  withExtra(argv[13], dimensions, coords, extraData);
  withExtra(argv[14], dimensions, coords, extraData);
  withExtra(argv[15], dimensions, coords, extraData);*/

  //If you had a tree without extra data
  //regularData(argv[1], coords);
  

  //BUILDING THE VECTORS
  //For every object type you will have to build it in a different for loop
  //If two files have different number of dimensions you cannot combine them in the same tree like I am doing below

  //Coffee Shop vector
  int k = 0;
  std::vector<DefaultLocation*> locationList;
  for (int i = 0; i < coords.size(); i+=dimensions)
  {
    std::vector<long double> temp;
    for (int j = 0; j < dimensions; j++)
    {
      temp.push_back(coords[i+j]);
    }
    locationList.push_back(new DefaultLocation(temp, extraData, k));
    k++;
    temp.clear();
  }

  //Create tree and initialize it with locations list and the number of dimensions
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  unsigned int d = dimensions;
  KDTree<DefaultLocation> test = KDTree<DefaultLocation>(locationList, d);

  end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout<< elapsed_seconds.count();
}


//std::vector<std::string> other_files_ri = {"automotives.csv"};
    //std::vector<std::string> other_files_ma = {};
    //std::vector<std::string> available_files_ri = { "alcohols.csv", "banks.csv", "barbers.csv", "coffee.csv", "hikings.csv", "hotels.csv", "landscapings.csv", "lawyers.csv", "polices.csv", "schools.csv", "steak.csv", "theaters.csv", "towings.csv"};
    //std::vector<std::string> available_files_ma = {"MA_alcohols.csv", "MA_automotives.csv", "MA_banks.csv", "MA_barbers.csv", "MA_coffees.csv", "MA_hikings.csv", "MA_hotels.csv",  "MA_landscapings.csv", "MA_lawyers.csv", "MA_polices.csv", "MA_schools.csv", "MA_steaks.csv", "MA_theaters.csv", "MA_towings.csv"};




std::string pwd_for_cpp() {
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    return ((std::string)cwd + "\\");
};


//Returns vector of locations
std::vector<DefaultLocation> getData(std::string fname) {
    //C: 1[Longitude] 2[Latitude] 3[type] 4[Name] 5[website url] 6[stars] 7[Street] 8[City] 9[State] 10[zip code] 11[phone number] 12[review count]

    //opens file under passed file name
    std::ifstream ifs;
    ifs.open(fname);

    //list of params
    long double longitude, latitude;
    std::string type, name, url, stars, street, city, state, zip, phone, rcount;

    std::string line, entry;
    int entryNum;
    unsigned int elems = 0;
    std::vector<DefaultLocation> data_Vector;
    DefaultLocation dl;


    while(std::getline(ifs, line)){
        std::stringstream streamline(line);
        //std::cout << line << std::endl;
        try{
          	while(std::getline(streamline, entry, ',')){

                //std::cout << entry << std::endl;
          	    if(entryNum == 0) {
              	    longitude = std::stod(entry);
              	}else if(entryNum == 1) {
              	    latitude = std::stod(entry);
              	    dl.coords.push_back(longitude);
              	    dl.coords.push_back(latitude);
              	}else if(entryNum == 2) {
                    dl.type = entry;
              	}else if(entryNum == 3) {
                    dl.name = entry;
              	}else if(entryNum == 4) {
                    dl.yelp_url = entry;
              	}else if(entryNum == 5) {
                    dl.stars = entry;
              	}else if(entryNum == 6) {
                    dl.street_address = entry;
              	}else if(entryNum == 7) {
                    dl.city = entry;
              	}else if(entryNum == 8) {
                    dl.state = entry;
              	}else if(entryNum == 9) {
                    dl.zip_code = entry;
              	}else if(entryNum == 10) {
                    dl.phone_number = entry;
              	}else if(entryNum == 11) {
                    dl.review_count = entry;
              	}else {
              	    break;
              	}
          	    entryNum++;
          	}
            //C: 1[Longitude] 2[Latitude] 3[type] 4[Name] 5[website url] 6[stars] 7[Street] 8[City] 9[State] 10[zip code] 11[phone number] 12[review count]

            //std::cout << longitude << " " << latitude << " " << type << " " << name << " " << url << " " << stars << street << " " << city << " " << state << " " << zip << " " << phone << " " << longitude << " " << rcount << std::endl;
          	data_Vector.push_back(dl);
          	dl.coords.clear();
          	entryNum = 0;
          	elems++;
        }
        catch(const std::invalid_argument& ia) {
            continue;
        }
        catch(std::exception& e) {
            continue;
        }
    }
    ifs.close();
    std::cout << "Number of counted elements: " << elems << std::endl;
    return data_Vector;
};
