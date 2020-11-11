#include "median.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <utility>
#include <queue>
#include <cmath>

MedianOfMedians::MedianOfMedians(std::vector<int> list, int target)
{
    this->list = list;
}

void MedianOfMedians::reset(std::vector<int> list, int target)
{
    this->list = list;
}

int MedianOfMedians::select(int left, int right, int target)
{
    
}
