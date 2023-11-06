#include <iostream>
#include <vector>

using namespace std;

// Insertion Sort Implementation
void insertion_sorting(vector<int> &arrToSort, int size)
{
    int currentElement = 0;
    for (int i = 1; i < size; i++)
    {
        currentElement = arrToSort[i];
        int j = i - 1;
        for (j = i - 1; j >= 0 && arrToSort[j] > currentElement; j--)
        {
            arrToSort[j + 1] = arrToSort[j];
        }
        arrToSort[j + 1] = currentElement;
    }
}