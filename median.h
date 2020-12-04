
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <utility>
#include <queue>
#include <cmath>
#include "Node.h"

class MedianOfMedians
{
    private:
        std::vector<std::shared_ptr<BaseLocation>>* list;
        int pivot(std::shared_ptr<BaseLocation> val, int left, int right);
        void sort(int left, int right);
        int dimension;
        int medianIdx;
    public:
        MedianOfMedians(std::vector<std::shared_ptr<BaseLocation>>& list, int dimension);//May look into making this a pointer if needed
        void reset(std::vector<std::shared_ptr<BaseLocation>>& list, int dimension);//If we need to change the list out
        std::shared_ptr<BaseLocation> select(int left, int right, int target);//Left = start of array, Right = end of array,
        //Target = index of target (ex. and vector of size 10 would have a target of 4 to find median)

};
