
#ifndef DATA_STRUCTS
#define DATA_STRUCTS

//#include "Node.hpp"

class KDTree_Key {
    private:

    protected:

    public:
        std::vector<long double> coords;
};





class DefaultLocation : public KDTree_Key {
    private:

    protected:
    public:
        std::string type = "";
        std::string name = "default";
        std::string yelp_url = "";
        std::string stars = "";
        std::string street_address = "";
        std::string city = "";
        std::string state = "";
        std::string zip_code = "";
        std::string phone_number = "";
        std::string review_count = "";


        DefaultLocation() {

        }; //<<<< do not use, useless, need to know the number of dimensions at conception

        DefaultLocation(unsigned int dimensions) {
            for(int i = 0; i < dimensions; i++) {
                this->coords.push_back(0.00000);
            }
        }

        DefaultLocation(std::vector<double> _coords, std::string _type, std::string _name, std::string _yelp_url,
                    std::string _stars, std::string _street_address, std::string _city,
                    std::string _state, std::string _zip_code, std::string _phone_number, std::string _review_count) {
            for(int i = 0; i < _coords.size(); i++) {
                this->coords.push_back(_coords[i]);
            }
            
            this->type = _type;
            this->name = _name;
            this->yelp_url = _yelp_url;
            this->stars = _stars;
            this->street_address = _street_address;
            this->city = _city;
            this->state = _state;
            this->zip_code = _zip_code;
            this->phone_number = _phone_number;
            this->review_count = _review_count;
        }
        bool operator==(const DefaultLocation &dl) {
            if( (dl.type == this->type) && (dl.name == this->name) && (dl.yelp_url == this->yelp_url) && (dl.stars == this->stars) && (dl.street_address == this->street_address) && (dl.city == this->city) && (dl.state == this->state) && (dl.zip_code == this->zip_code) && (dl.phone_number == this->phone_number) && (dl.review_count == this->review_count) && (dl.coords == this->coords)) {
                    return true;
                } else {
                    return false;
                }
        }
        bool operator!=(const DefaultLocation &dl) {
            if( (dl.type == this->type) && (dl.name == this->name) && (dl.yelp_url == this->yelp_url) && (dl.stars == this->stars) && (dl.street_address == this->street_address) && (dl.city == this->city) && (dl.state == this->state) && (dl.zip_code == this->zip_code) && (dl.phone_number == this->phone_number) && (dl.review_count == this->review_count) && (dl.coords == this->coords)) {
                    return false;
                } else {
                    return true;
                }
        }
        void print_info() {
            std::cout << this->name << ": " << this->coords[0] << " " << this->coords[1] << std::endl;
        }
};


#endif