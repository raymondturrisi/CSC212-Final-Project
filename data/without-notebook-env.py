

# ------------------------------------------------------------------------
# NOTE: No longer reflects the most up to date version of the .ipynb file.
# ------------------------------------------------------------------------


#A Jupyter notebook for gathering and formatting location data using Yelp's API and Python

# Resources:
# - Python 'requests' HTTP library, https://requests.readthedocs.io/en/master/
# - Yelp 'Fusion' API Overview, https://www.yelp.com/developers/documentation/v3/get_started
# - Specific Yelp endpoint used, https://www.yelp.com/developers/documentation/v3/business_search
# - About Jupyter Notebooks, https://jupyter.org/

# Notes (11/30/2020):
# - Compiled .csv data on 50 coffee shops in Rhode Island (coffee-shops.csv)
# - Based loosely on the dataStructs.h > CoffeeShops struct, but I know we
#   are making a common location structure for which I will have to create
#   another file.
# - Can compile data on > 50 locations if we desire more.

import requests
import json

YELP_API_KEY = 'OA7QK3BGg6NX8NSPb2e4nTvvpHuw99lCUgZa5WAVYBYR2nu-zbVejthwyDKMraMV1Dhq85FGGl_jPzcd7rB-mGS97yyHCTLYG_Bw3ccA6T9C6Aj4M57FBgWysiPFX3Yx'

try:
    request_url = f'https://api.yelp.com/v3/businesses/search'
    headers={'Authorization': f'Bearer {YELP_API_KEY}'}

    # Change term variable here to make requests with different search terms.
    url_params = {
        'term': 'coffee',
        'location': 'Rhode Island'
    }
    r = requests.get(request_url, headers=headers, params=url_params)

    #print(headers['Authorization'])

    #print('Response=', r.text)

    # len(r.json()['businesses'])
    r.json()['businesses']
    businesses = r.json()['businesses']

except Exception as e:
    print("Exception=", e)

# struct CoffeeShops
# {
#     int terms = 3;
#     int stars;
#     bool public_bathroom;
#     bool free_Wifi;
#     CoffeeShops(int coordsCount, std::vector<std::string>& extraData);
# };

with open("coffee-shops.csv", "w") as f:
    for b in businesses:
        struct = f"{b['coordinates']['latitude']},{b['coordinates']['latitude']},{b['name']},{b['rating']},0,0\n"
        #print(struct)
        f.write(struct)
