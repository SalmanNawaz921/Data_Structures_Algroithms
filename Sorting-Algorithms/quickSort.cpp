#include <iostream>
#include <vector>

using namespace std;

// Quick sort implemmation
int partition(vector<int> &arrToSort, int low, int high)
{
    int x = low - 1;
    int pivotElement = arrToSort[high];

    for (int i = low; i < high; i++)
    {
        if (arrToSort[i] < pivotElement)
        {
            int temp = arrToSort[++x];
            arrToSort[x] = arrToSort[i];
            arrToSort[i] = temp;
        }
    }
    x++;
    int temp = arrToSort[x];
    arrToSort[x] = arrToSort[high];
    arrToSort[high] = temp;
    return x;
}
void quick_sorting(vector<int> &arrToSort, int low, int high)
{
    if (low >= high)
        return;
    int pivotIndex = partition(arrToSort, low, high);
    quick_sorting(arrToSort, low, pivotIndex - 1);
    quick_sorting(arrToSort, pivotIndex + 1, high);
}
