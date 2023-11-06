#include <iostream>
#include <vector>

using namespace std;

// Merge Sortings Implementation

void merge(vector<int> &arrToMerge, int start, int mid, int end)
{
    vector<int> mergedVector(end - start + 1);
    int x = 0;
    int index1 = start;
    int index2 = mid + 1;
    while (index1 <= mid && index2 <= end)
    {
        if (arrToMerge[index1] <= arrToMerge[index2])
            mergedVector[x++] = arrToMerge[index1++];
        else
            mergedVector[x++] = arrToMerge[index2++];
    }

    while (index1 <= mid)
        mergedVector[x++] = arrToMerge[index1++];

    while (index2 <= end)
        mergedVector[x++] = arrToMerge[index2++];

    for (int i = 0, j = start; i < mergedVector.size(); i++, j++)
    {
        arrToMerge[j] = mergedVector[i];
    }
}

void merge_sorting(vector<int> &arrToSort, int start, int end)
{
    if (start >= end)
        return;
    int mid = start + ((end - start) / 2);
    merge_sorting(arrToSort, start, mid);
    merge_sorting(arrToSort, mid + 1, end);
    merge(arrToSort, start, mid, end);
}