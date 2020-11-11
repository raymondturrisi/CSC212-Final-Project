#ifndef MEDIAN_H
#define MEDIAN_H

#include <vector>



class MedianOfMedians
{
    private:
        std::vector<int> list;
        int partition (int left, int right, int pivotIdx, int target);
        int pivot(int left, int right);
        int partition5(int left, int right);
    public:
        MedianOfMedians(std::vector<int> list, int target);
        void reset(std::vector<int> list, int target);
        int select(int left, int right, int target);
};


#endif