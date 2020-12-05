
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
        //TypeDef
        typedef std::vector<BaseLocation::SPtr> BaseVector;//Private version of this typedef as regular version is located in KDTree.h and that file cannot be included due to KDTree.h including median.h

        //Data
        BaseVector* list;
        int dimension;//Dimension being operated on (ex 0 = x, 1 = y, 2 = z, etc.)
        int medianIdx;//Index of median value in un-pivoted array, used only in pivot method

        //Methods
        int pivot(BaseLocation::SPtr val, int left, int right);
        void sort(int left, int right);
    public:
        MedianOfMedians();
        MedianOfMedians(BaseVector& list, int dimension);//May look into making this a pointer if needed
        void reset(BaseVector& list, int dimension);//If we need to change the list out
        BaseLocation::SPtr select(int left, int right, int target);//Left = start of array, Right = end of array,
        //Target = index of target (ex. and vector of size 10 would have a target of 4 to find median)

};
