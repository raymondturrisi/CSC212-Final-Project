
#ifndef DATA_STRUCTS
#define DATA_STRUCTS

//#include "Node.hpp"

class DefaultLocation{
    private:

    protected:
    public:
        std::vector<long double> coords;
        std::string type = "";
        std::string name = "";
        std::string yelp_url = "";
        std::string stars = "";
        std::string street_address = "";
        std::string city = "";
        std::string state = "";
        std::string zip_code = "";
        std::string phone_number = "";
        std::string review_count = "";
        void print_info() {
            std::cout << name << ": " << coords[0] << " " << coords[1] << std::endl;
        }
};


#endif