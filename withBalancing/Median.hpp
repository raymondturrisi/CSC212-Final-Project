#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <utility>
#include <queue>
#include <cmath>
#include "Node.hpp"

template <class t>
class MedianOfMedians
{
    private:
        //Data
        std::vector<t*>* list;
        int dimension;//Dimension being operated on (ex 0 = x, 1 = y, 2 = z, etc.)
        int medianIdx;//Index of median value in un-pivoted array, used only in pivot method

        //Methods
        int pivot(t* val, int left, int right);
        void sort(int left, int right);
    public:
        MedianOfMedians();
        MedianOfMedians(std::vector<t*>& list, int dimension);//May look into making this a pointer if needed
        void reset(std::vector<t*>& list, int dimension);//If we need to change the list out
        t* select(int left, int right, int target);//Left = start of array, Right = end of array,
        //Target = index of target (ex. and vector of size 10 would have a target of 4 to find median)

};


//Find an approximation of median at a target index. Runs in linear time O(n)
//First a loop that runs n/5 times
//Then a recursive call that works on n/5 of the list
//The pivot is done in a single pass O(n)
//There are n/10 medians greater than the pivot and n/10 medians less than
//For each of the medians there are also 2 more elements eliminated, so 3 elements eliminated per median
//Leaves us with 7/10ths of the orginal array to search if target is not found

template <class t>
MedianOfMedians<t>::MedianOfMedians()
{
    this->list = nullptr;
    this->dimension = 0;
    this->medianIdx = 0;
}

template <class t>
MedianOfMedians<t>::MedianOfMedians(std::vector<t*>& list, int dimension)
{
    this->list = &list;
    this->dimension = dimension;
    this->medianIdx = 0;
}

template <class t>
void MedianOfMedians<t>::reset(std::vector<t*>& list, int dimension)
{
    this->list = &list;
    this->dimension = dimension;
    this->medianIdx = 0;
}

template <class t>
t* MedianOfMedians<t>::select(int left, int right, int target)
{
    //If segment of list is less than 5 then base case is found and median can be found without recursion
    if (right - left <= 5)
    {
        sort(left, right);
        medianIdx = target;//Only used in pivot algorithm
        return (*list)[target];
    }

    //Treats list as groups of 5, finds median of each group and swaps median(s) to front of list
    int swapIdx = left;
    for(int i = left; i < (right-1); i+=5)
    {
        int subRight = i + 4;
        if (subRight > right)
        {
            subRight = right;
        }
        sort(i,subRight);
        //Swap
        t* temp = (*list)[i+floor((subRight-i)/2)];
        (*list)[i+floor((subRight-i)/2)] = (*list)[swapIdx];
        (*list)[swapIdx] = temp;

        swapIdx++;
    }

    //Recursively call select to now find the median of the group of medians (old medians and new medians)
    int newTarget = left + floor((swapIdx-left)/2);
    t* median = select(left, swapIdx, newTarget);

    //Pivot re-orders the list around the median of medians and returns out the index location of median of medians
    int location = pivot(median, left, right);
    //If the median is the target you are looking for then return the median
    if (location == target)
    {
        return (*list)[target];
    }
    //else you look for more medians by dividing array into two sections (one less than pivot and one greater than)
    //greater than pivot
    else if (target > newTarget)
    {
        return select(newTarget+1, right, target);
    }
    //less than pivot
    return select(left, newTarget, target);
}

template <class t>
int MedianOfMedians<t>::pivot(t* val, int left, int right)
{
    //COMPLEXITY: n
    //Pivots in one pass

    //Moves the target val to the end of the vector, allows pivot to commence in one pass
    t* temp = (*list)[medianIdx];
    (*list)[medianIdx] = (*list)[right];
    (*list)[right] = temp;


    int j = left-1;
    for (int i = left; i <= (right-1); i++)
    {
        //If value is less than val it is moved to an index starting from the left (that's the j term)
        if ((*list)[i]->coords[dimension] < (*val).coords[dimension])
        {
            j++;
            t* temp = (*list)[i];
            (*list)[i] = (*list)[j];
            (*list)[j] = temp;
        }
    }
    j++;
    //returns out location of properly placed pivot
    temp = (*list)[j];
    (*list)[j] = (*list)[right];
    (*list)[right] = temp;
    return (j);
}

template <class t>
void MedianOfMedians<t>::sort(int left, int right)
{
    //insertion sort
    int i = left + 1;
    while (i <= right)
    {
        int j = i;
        while (j > left && (*list)[j-1]->coords[dimension] > (*list)[j]->coords[dimension] && (*list).size() != j)
        {
            t* temp = (*list)[j];
            (*list)[j] = (*list)[j-1];
            (*list)[j-1] = temp;
            j--;
        }
        i++;
    }
}