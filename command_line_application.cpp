#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <map>
#include <typeinfo>
// Custom classes
#include "KDTree.hpp"
#include "dataStructs.hpp"
#include "Node.hpp"

//Returns vector of locations
std::vector<DefaultLocation> getData(std::string fname);
std::string pwd_for_cpp();

std::string map_int_to_location_type(int desired_location_type_choice);
// void output_nearest_neighbor_info(DefaultLocation nearest);
void get_user_choice(std::vector<double> & long_lat_vect, int & desired_location_type_choice);

int main(int argc, char *args[]) {
    //std::string fname = args[1];
    std::string master_csv = "CT_MA_RI_cleaned.csv";

    std::string working_directory = pwd_for_cpp();
    std::string fname;
    fname = working_directory + master_csv;

    //fname = working_directory + "/breakdown_by_type/RI/alcohols.csv";

    std::vector<DefaultLocation> myDat = getData(fname);
    //std::cout << "Getting data from file: " << fname << std::endl << std::endl;

    unsigned int expected_dimensions = 2;
    KDTree<DefaultLocation> tree(expected_dimensions);

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    std::string type;
    std::vector<std::string> types;
    int k = 0;


    // Inserting data into our K-Dimensional Tree class.
    for(int i = 0; i < myDat.size(); i++) {
        type = myDat[i].type;
        while(i != 0 && myDat[i-1].type == myDat[i].type && i <myDat.size()) {
            tree.insert(myDat[i]);
            i++;
        }
        k++;
        //test_vec.push_back(tree);
        types.push_back(type);
        //tree.postOrder();
        //tree.destroy();
        //KDTree<DefaultLocation> tree(expected_dimensions);
    }


    // ** Start Command Line Application **

    std::vector<double> long_lat_coords = {};
    int desired_location_type_choice = 0;

    // Gets a valid user choice and assigns <long_lat_coords> and <desired_location_type> above.
    get_user_choice(long_lat_coords, desired_location_type_choice);

    std::string desired_location_type = map_int_to_location_type(desired_location_type_choice);

    // Sample command line input
    // long, lat, type
    // URI coffee shop command line input: -71.5258 41.48071 5
    // Providence hotels command line input: -71.4128 41.824 7

    DefaultLocation nearest = tree.nearest_neighbor_oftype_best(long_lat_coords, desired_location_type);

    std::cout << "\n\n---------------Result--------------\n";
    std::cout << "Name: " << nearest.name << std::endl << std::endl << "City: " << nearest.city << std::endl << std::endl
              << "State: " << nearest.state << std::endl << std::endl << "Address: " << nearest.street_address << std::endl << std::endl
              << "ZIP: " << nearest.zip_code << std::endl << std::endl << "Phone number: " << nearest.phone_number << std::endl << std::endl
              << "Rating(1-5): " << nearest.stars << std::endl << std::endl << "Yelp URL: " << nearest.yelp_url << std::endl << std::endl
              << "Longitude, latitude: " << "(" << nearest.coords[1] << "," << nearest.coords[0] << ")" << std::endl << std::endl;


    // std::string yelp_url = (tree.nearest_neighbor_oftype(long_lat_coords, desired_location_type)).yelp_url;
    // std::string command = "python3 open_web_browser.py " + yelp_url;
    // std::cout << command << std::endl;
    // system(command.c_str());

    return 0;
}

void get_user_choice(std::vector<double> & long_lat_vect, int & desired_location_type_choice){

  bool valid_choice = false;
  double longitude, latitude;

  while(!valid_choice){

    std::cout << "Location type choices:\n";
    std::cout << "1-Locations with alcohol\n"
              << "2-Automotive (repair)\n"
              << "3-Banks\n"
              << "4-Barber shops\n"
              << "5-Coffee shops\n"
              << "6-Hiking spots\n"
              << "7-Hotels\n"
              << "8-Landscapers\n"
              << "9-Lawyer's offices\n"
              << "10-Courts and other law offices\n"
              << "11-Schools\n"
              << "12-Steakhouses\n"
              << "13-Theaters\n"
              << "14-Towing garages\n";

    std::cout << "\nPlease enter your longitude, latitude and the # from above which corresponds type of location you want to search for.\n";

    std::cin >> longitude >> latitude >> desired_location_type_choice;

    std::vector<int> valid_choices = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    if(longitude && latitude){
      for(int i = 0 ; i < valid_choices.size(); i ++){
          if(desired_location_type_choice == valid_choices[i]){
            valid_choice = true;
          }

      }
    }else{

      std::cout << "Please enter longitude and latitude data...\n";

    }


    if(!valid_choice){
      std::cout << "\n\nInvalid input! Please try again...\n\n";
    }else{
      std::cout << "\n\nLoading...\n\n";
    }

  }

  // Longitude, latitude

  long_lat_vect.push_back(latitude);
  long_lat_vect.push_back(longitude);

};


std::string map_int_to_location_type(int desired_location_type_choice){
  std::string desired_location_type = "";

  switch(desired_location_type_choice) {
    case 1:
      desired_location_type = "alcohol";
      break; //optional
    case 2:
      desired_location_type = "automotive";
      break; //optional
    case 3:
     desired_location_type = "bank";
     break; //optional
    case 4:
      desired_location_type = "barber";
      break; //optional
    case 5:
      desired_location_type = "coffee";
      break; //optional
    case 6:
      desired_location_type = "hiking";
      break;
    case 7:
      desired_location_type = "hotel";
      break;
    case 8:
      desired_location_type = "landscaping";
      break;
    case 9:
      desired_location_type = "lawyer";
      break;
    case 10:
      desired_location_type = "police";
      break;
    case 11:
      desired_location_type = "school";
      break;
    case 12:
      desired_location_type = "steak";
      break;
    case 13:
      desired_location_type = "theater";
      break;
    case 14:
      desired_location_type = "towing";
      break;
    // you can have any number of case statements.
    default : //Optional
      desired_location_type = "coffee";
  }
  return desired_location_type;

};

// void output_nearest_neighbor(DefaultLocation nearest){
//
//
// };

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
    // std::cout << "Number of counted elements: " << elems << std::endl;
    return data_Vector;
};
