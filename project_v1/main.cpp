#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

// Custom classes
#include "KDTree.hpp"
#include "dataStructs.hpp"
#include "Node.hpp"
//Returns vector of locations

std::vector<DefaultLocation> getData(std::string fname);


int main(int argc, char *args[]) {
    std::string fname = args[1];
    std::cout << "file name: " << fname << std::endl << std::endl;

    std::vector<DefaultLocation> myDat = getData(fname);

    //KDTree<DefaultLocation> tree();
    KDTree<DefaultLocation> tree(myDat[0]);

    for(int i = 1; i < 500; i++) {
        //std::cout << i << std::endl;
        //myDat[i].print_info();
        tree.insert(myDat[i]);
        //tree.postOrder();
    }

    tree.postOrder();
    tree.dotOut("test.png");
    return 0;
}





















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
        }
        catch(const std::invalid_argument& ia) {

        }
    }
    return data_Vector;
    ifs.close();
};