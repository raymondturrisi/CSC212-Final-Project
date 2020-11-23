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

//Find an approximation of median at a target index. Runs in linear time O(n)
//First a loop that runs n/5 times
//Then a recursive call that works on n/5 of the list
//The pivot is done in a single pass O(n)
//There are n/10 medians greater than the pivot and n/10 medians less than
//For each of the medians there are also 2 more elements eliminated, so 3 elements eliminated per median
//Leaves us with 7/10ths of the orginal array to search if target is not found

MedianOfMedians::MedianOfMedians(std::vector<Node>& list)
{
    this->list = list;
}

void MedianOfMedians::reset(std::vector<double>& list)
{
    this->list = list;
}

int MedianOfMedians::select(int left, int right, int target)
{
    //If segment of list is less than 5 then base case is found and median can be found without recursion
    if (right - left <= 5)
    {
        sort(left, right);
        return list[target];
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
        double temp = list[i+floor((subRight-i)/2)];
        list[i+floor((subRight-i)/2)] = list[swapIdx];
        list[swapIdx] = temp;
        swapIdx++;
    }

    //Recursively call select to now find the median of the group of medians (old medians and new medians)
    int newTarget = left + floor((swapIdx-left)/2);
    int median = select(left, swapIdx, newTarget);

    //Pivot re-orders the list around the median of medians and returns out the index location of median of medians
    int location = pivot(median, left, right);
    //If the median is the target you are looking for then return the median
    if (location == target)
    {
        return list[target];
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

int MedianOfMedians::pivot(int val, int left, int right)
{
    int j = left;
    int valIdx = 0; 
    for (int i = left; i <= (right-1); i++)
    {
        //If value is less than or equal to val it is moved
        if (list[i] <= val)
        {
            if (list[i] == val)
            {
                valIdx = i;
            }
            double temp = list[i];
            list[i] = list[j];
            list[j] = temp;
            j++;
        }
    }
    j--;
    //returns out location of properly placed pivot
    double temp = list[j];
    list[j] = list[valIdx];
    list[valIdx] = temp;
    return (j);
}

void MedianOfMedians::sort(int left, int right)
{
    //insertion sort
    int i = left + 1;
    while (i <= right)
    {
        int j = i;
        while (j > left && list[j-1] > list[j] && list.size() != j)
        {
            double temp = list[j];
            list[j] = list[j-1];
            list[j-1] = temp;
            j--;
        }
        i++;
    }
}