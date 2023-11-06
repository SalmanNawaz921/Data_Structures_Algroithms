#include <iostream>
#include <vector>

using namespace std;

// Selection Sort Implementation

void selection_sorting(vector<int> &arrToSort, int size)
{
    int sIndex = 0;

    for (int i = 0; i < size - 1; i++)
    {
        sIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arrToSort[j] < arrToSort[sIndex])
            {
                sIndex = j;
            }
        }
        int temp = arrToSort[i];
        arrToSort[i] = arrToSort[sIndex];
        arrToSort[sIndex] = temp;
    }
}
