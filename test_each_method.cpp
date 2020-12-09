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
std::vector<DefaultLocation> getData_CP(std::string fname);
std::vector<DefaultLocation> getData_CP3(std::string fname);


std::string pwd_for_cpp();

int myrandom (int i) { return std::rand()%i;}

int main(int argc, char *args[]) {
    //std::string fname = args[1];
    //int elem = std::stoi(args[1]);
    std::string master_csv = "/CT_MA_RI_cleaned.csv";

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

    std::cout << "Getting data from file: " << fname << std::endl << std::endl;

    std::cout << myDat.size() << std::endl;

    int k = 0;
    unsigned int inserts = 0;

    for(int j = 0; j < myDat.size(); j++) {
        tree.insert(myDat[j]);
    }
    /*
    //compares overload ==
    for(int i = 0; i < myDat.size(); i+=2000) {
        if(myDat[i] == myDat[i]) {
            std::cout << "Passed boolean operation: " << i << std::endl;
        } else {
            std::cout << "Failed boolean operation: " << i << std::endl;
            myDat[i].print_info();
        }
    }

    //compares overload !=
    for(int i = 0; i < myDat.size(); i+=2000) {
        if(myDat[i] != myDat[i]) {
            std::cout << "Failed !boolean operation: " << i << std::endl;
            myDat[i].print_info();
        } else {
            std::cout << "Passed !boolean operation: " << i << std::endl;

        }
    }
    */
    for(int i = 0; i < myDat.size(); i+=500) {
        if(tree.search_for_element(myDat[i])) {
        std::cout << "Found source data in tree!\n";
        } else {
            std::cout << "Missing source data in tree..\n";
            myDat[i].print_info();
        }
    }
    DefaultLocation dl(2);

    for(int i = 0; i < myDat.size(); i+=1000) {
        if(tree.search_for_element(dl)) {
        std::cout << "Does not belong in tree..\n";
        dl.print_info();
        } else {
            std::cout << "Good, false data not in tree!\n";
        }
    }

    DefaultLocation t(2);
    double best_distance;
    for(int i = 0; i < myDat.size(); i+=1000) {
        best_distance = DBL_MAXT;
        t = tree.nearest_neighbor(myDat[i], best_distance);
        myDat[i].print_info();
        t.print_info();
        std::cout << "closest distance of euclidian Long/Lat: " << best_distance << std::endl;
    }

    for(int i = 0; i < myDat.size(); i+=1000) {
        best_distance = DBL_MAXT;
        t = tree.nearest_neighbor_oftype(myDat[i], "automotive", best_distance);
        myDat[i].print_info();
        t.print_info();
        /*
        if(t.type == "default") {
            std::cout << i << std::endl;
            myDat[i].print_info();
            std::cout << tree.search_for_element(myDat[i]) << std::endl;
            std::cout << tree.search_for_element(t) << std::endl;
        }*/
        std::cout << "closest distance of euclidian Long/Lat: " << best_distance << std::endl;
    }


    std::cout << "With local coords\n";
    std::vector<double> local_coords = {41.48071,-71.5258};
    std::cout << local_coords[0] << " " << local_coords[1] << std::endl;
    DefaultLocation r(2);

    best_distance = DBL_MAXT;
    t = tree.nearest_neighbor_oftype(local_coords, "coffee", best_distance);
    t.print_info();
    std::cout << "closest distance of euclidian Long/Lat: " << best_distance << std::endl;

    best_distance = DBL_MAXT;
    t = tree.nearest_neighbor(local_coords, best_distance);
    t.print_info();
    std::cout << "closest distance of euclidian Long/Lat: " << best_distance << std::endl;

    //tree.destroy();


    std::cout << "Onto colors!\n";

    fname = working_directory + "/breakdown_by_type/General_coordinates/2d_colored.csv";
    std::vector<DefaultLocation> cpDat = getData_CP(fname);
    KDTree<DefaultLocation> tree2(2);

    for(int i = 0; i < cpDat.size(); i++) {
        tree2.insert(cpDat[i]);
    }

    for(int i = 0; i < cpDat.size(); i++) {
        best_distance = DBL_MAXT;
        t = tree2.nearest_neighbor(cpDat[i], best_distance);
        //cpDat[i].print_info();
        //t.print_info();
        //std::cout << "closest distance of euclidian distance: " << best_distance << std::endl;
        //cpDat[i].print_info();
        //std::cout << cpDat[i].coords[0] << ", " << cpDat[i].coords[1] << ", " << t.coords[0] << ", " << t.coords[1] << "\n"; //matlab formatted output for arrowed graph
    }



    /*
    for(int i = cpDat.size()-1; i > 0; i-=1) {
        best_distance = DBL_MAXT;
        t = tree2.nearest_neighbor_oftype(cpDat[i], "Orange", best_distance);
        cpDat[i].print_info();
        t.print_info();
        if(t.name == "default") {
            std::cout << i << std::endl;
        }
        std::cout << "closest distance of euclidian distance: " << best_distance << std::endl;
    }
    */
    //tree2.inOrder();
    //tree2.dotOut("coloredCords.svg");
    //tree2.destroy();

    fname = working_directory + "/breakdown_by_type/General_coordinates/3d_colored.txt";
    std::cout << fname << std::endl;
    std::vector<DefaultLocation> cp3Dat = getData_CP3(fname);



    KDTree<DefaultLocation> tree3(3);
    for(int i = 0; i < cp3Dat.size(); i++) {
        tree3.insert(cp3Dat[i]);
    }

    tree3.dotOut("3d_tree.svg");

    sleep(2);
    std::vector<DefaultLocation*> tb_balanced;

    for(int i = 0; i < cp3Dat.size(); i++) {
        tb_balanced.push_back(&cp3Dat[i]);
    }

    KDTree<DefaultLocation> tree3_bal(tb_balanced,3);
    tree3_bal.dotOut("balanced_3d_tree.svg");


    std::cout << "Onto 3D colors!\n";


    /*
    std::vector<DefaultLocation*> dat3d_2;
    for(int i = 0; i < cp3Dat.size(); i++) {
        dat3d_2.push_back(&cp3Dat[i]);
    }
    KDTree<DefaultLocation> tree3_balanced(dat3d_2,3);

    */

    tree3.inOrder();
    DefaultLocation t3(3);
    for(int i = 0; i < cp3Dat.size(); i++) {
        best_distance = DBL_MAXT;
        t3 = tree3.nearest_neighbor(cp3Dat[i], best_distance);
        //cp3Dat[i].print_info();
        //t.print_info();
        //std::cout << "closest distance of euclidian distance: " << best_distance << std::endl;
        //std::cout << cp3Dat[i].coords[0] << ", " << cp3Dat[i].coords[1] << ", " << cp3Dat[i].coords[2] << ", " << t3.coords[0] << ", " << t3.coords[1] << ", " << t3.coords[2] << "\n"; //matlab formatted output for arrowed graph
    }

    std::vector<double> moving_coords = {-100,-100,-100};

    for(int i = -99; i <=100; i++) {
        best_distance = DBL_MAXT;
        t3 = tree3.nearest_neighbor(moving_coords, best_distance);
        std::cout << moving_coords[0] << ", " << moving_coords[1] << ", " << moving_coords[2] << ", " << t3.coords[0] << ", " << t3.coords[1] << ", " << t3.coords[2] << "\n"; //matlab formatted for moving plot finding neighbors
        //moving_coords[0] = i;moving_coords[1] = i;moving_coords[2] = i;
    }


    //tree3.dotOut("coloredCords3D.svg");

    tree3.destroy();



    return 0;
}



















std::string pwd_for_cpp() {
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    return ((std::string)cwd);
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
    int entryNum = 0;
    unsigned int elems = 0;
    std::vector<DefaultLocation> data_Vector;
    DefaultLocation dl(2);


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


//Returns vector of locations
std::vector<DefaultLocation> getData_CP(std::string fname) {

    //opens file under passed file name
    std::ifstream ifs;
    ifs.open(fname);

    //list of params
    long double longitude, latitude;
    std::string type, name, url, stars, street, city, state, zip, phone, rcount;

    std::string line, entry;
    int entryNum = 0;
    unsigned int elems = 0;
    std::vector<DefaultLocation> data_Vector;
    DefaultLocation dl(2);


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
              	}else {
              	    break;
              	}
          	    entryNum++;
          	}
            //C: 1[Longitude] 2[Latitude] 3[type] 4[Name] 5[website url] 6[stars] 7[Street] 8[City] 9[State] 10[zip code] 11[phone number] 12[review count]

            //std::cout << longitude << " " << latitude << " " << type << " " << name << " " << url << " " << stars << street << " " << city << " " << state << " " << zip << " " << phone << " " << longitude << " " << rcount << std::endl;

          	dl.name = dl.type;
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


std::vector<DefaultLocation> getData_CP3(std::string fname) {

    //opens file under passed file name
    std::ifstream ifs;
    ifs.open(fname);

    //list of params
    long double x, y, z;
    std::string type, name, url, stars, street, city, state, zip, phone, rcount;

    std::string line, entry;
    int entryNum = 0;
    unsigned int elems = 0;
    std::vector<DefaultLocation> data_Vector;
    DefaultLocation dl(2);


    while(std::getline(ifs, line)){
        std::stringstream streamline(line);
        //std::cout << line << std::endl;
        try{
          	while(streamline >> entry){

                //std::cout << entry << std::endl;
          	    if(entryNum == 0) {
              	    x = std::stod(entry);
              	}else if(entryNum == 1) {
              	    y = std::stod(entry);

              	}else if(entryNum == 2) {
              	    z = std::stod(entry);
              	    dl.coords.push_back(x);
                    dl.coords.push_back(y);
                    dl.coords.push_back(z);
              	}else if(entryNum == 3) {
                    dl.type = entry;
              	}else {
              	    break;
              	}
          	    entryNum++;
          	}
            //C: 1[Longitude] 2[Latitude] 3[type] 4[Name] 5[website url] 6[stars] 7[Street] 8[City] 9[State] 10[zip code] 11[phone number] 12[review count]

            //std::cout << longitude << " " << latitude << " " << type << " " << name << " " << url << " " << stars << street << " " << city << " " << state << " " << zip << " " << phone << " " << longitude << " " << rcount << std::endl;

          	dl.name = dl.type;
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


