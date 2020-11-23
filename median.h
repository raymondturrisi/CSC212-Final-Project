#ifndef MEDIAN_H
#define MEDIAN_H

#include <vector>



class MedianOfMedians
{
    private:
        std::vector<int> list;
        int pivot(int val, int left, int right);
        void sort(int left, int right);
    public:
        MedianOfMedians(std::vector<int> list);//May look into making this a pointer if needed
        void reset(std::vector<int> list);//If we need to change the list out
        int select(int left, int right, int target);//Left = start of array, Right = end of array,
        //Target = index of target (ex. and vector of size 10 would have a target of 4 to find median)

};


#endif
