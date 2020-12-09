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
#include <algorithm>
#include <random>

// Custom classes
#include "KDTree.hpp"
#include "dataStructs.hpp"
#include "Node.hpp"

//Returns vector of locations
std::vector<DefaultLocation> getData(std::string fname);
std::string pwd_for_cpp();

int myrandom (int i) { return std::rand()%i;}

int main(int argc, char *args[]) {
    //std::string fname = args[1];
    //int elem = std::stoi(args[1]);
    std::string master_csv = "cleaned_master_sorted.csv";
    std::vector<std::string> other_files_ri = {"banks.csv"};
    std::vector<std::string> other_files_ma = {};
    std::vector<std::string> available_files_ri = { "automotives.csv", "alcohols.csv", "barbers.csv", "coffee.csv", "hikings.csv", "hotels.csv", "landscapings.csv", "lawyers.csv", "polices.csv", "schools.csv", "steak.csv", "theaters.csv", "towings.csv"};
    std::vector<std::string> available_files_ma = {"MA_alcohols.csv", "MA_automotives.csv", "MA_banks.csv", "MA_barbers.csv", "MA_coffees.csv", "MA_hikings.csv", "MA_hotels.csv",  "MA_landscapings.csv", "MA_lawyers.csv", "MA_polices.csv", "MA_schools.csv", "MA_steaks.csv", "MA_theaters.csv", "MA_towings.csv"};


    std::string working_directory = pwd_for_cpp();
    std::string fname;


    unsigned int expected_dimensions = 2;
    KDTree<DefaultLocation> tree(expected_dimensions);
    fname = working_directory + master_csv;

        std::vector<DefaultLocation> myDat = getData(fname);
        std::random_shuffle(myDat.begin(), myDat.end(), myrandom);

        //std::cout << "Getting data from file: " << fname << std::endl << std::endl;


        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();

        //std::cout << myDat.size() << std::endl;
        std::chrono::duration<double> elapsed_seconds;
        int k = 0;
        unsigned int inserts = 0;
            for(int j = 0; j < myDat.size(); j++) {
                if(k > 100) {
                    end = std::chrono::system_clock::now();
                    elapsed_seconds = end - start;
                    std::cout<< inserts << ", " << elapsed_seconds.count() << std::endl;
                    k = 0;
                }
                tree.insert(myDat[j]);
                k++;
                inserts++;
            }


        tree.destroy();


        //std::cout << (bool)tree.head << std::endl;

    return 0;
}


//std::vector<std::string> other_files_ri = {"automotives.csv"};
    //std::vector<std::string> other_files_ma = {};
    //std::vector<std::string> available_files_ri = { "alcohols.csv", "banks.csv", "barbers.csv", "coffee.csv", "hikings.csv", "hotels.csv", "landscapings.csv", "lawyers.csv", "polices.csv", "schools.csv", "steak.csv", "theaters.csv", "towings.csv"};
    //std::vector<std::string> available_files_ma = {"MA_alcohols.csv", "MA_automotives.csv", "MA_banks.csv", "MA_barbers.csv", "MA_coffees.csv", "MA_hikings.csv", "MA_hotels.csv",  "MA_landscapings.csv", "MA_lawyers.csv", "MA_polices.csv", "MA_schools.csv", "MA_steaks.csv", "MA_theaters.csv", "MA_towings.csv"};




std::string pwd_for_cpp() {
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    return ((std::string)cwd + "/");
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
    //std::cout << "Number of counted elements: " << elems << std::endl;
    return data_Vector;
};