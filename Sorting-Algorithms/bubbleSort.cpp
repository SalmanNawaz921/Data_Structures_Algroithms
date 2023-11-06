#include <iostream>
#include <vector>

using namespace std;

// Bubble Sort Implementation

void bubble_sorting(vector<int> &arrToSort, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arrToSort[j] > arrToSort[j + 1])
            {
                int temp = arrToSort[j];
                arrToSort[j] = arrToSort[j + 1];
                arrToSort[j + 1] = temp;
                // swap(arrToSort[j], arrToSort[j + 1]);
            }
        }
    }
}
