#include <iostream>
#include <vector>

using namespace std;

// Bubble Sort
void bubbleSort(vector<int> &arr)
{

    for (int i = 0; i < arr.size() - 1; i++)
    {
        for (int j = 0; j < arr.size() - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Selection Sort

void selectionSort(vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        int sIndex = i;
        for (int j = i + 1; j < arr.size(); j++)
        {
            if (arr[j] < arr[sIndex])
                sIndex = j;
        }
        swap(arr[sIndex], arr[i]);
    }
}

// Merge Sort

void conqouer(vector<int> &arr, int start, int mid, int end)
{
    vector<int> merge(end - start + 1);
    int x = 0;
    int index1 = start;
    int index2 = mid + 1;

    while (index1 <= mid && index2 <= end)
    {
        if (arr[index1] <= arr[index2])
            merge[x++] = arr[index1++];
        else
            merge[x++] = arr[index2++];
    }

    while (index1 <= mid)
        merge[x++] = arr[index1++];
    while (index2 <= end)
        merge[x++] = arr[index2++];

    for (int i = 0, j = start; i < merge.size(); i++, j++)
    {
        arr[j] = merge[i];
    }
}
void divide(vector<int> &arr, int start, int end)
{
    if (start >= end)
        return;
    int mid = start + (end - start) / 2;
    divide(arr, start, mid);
    divide(arr, mid + 1, end);
    conqouer(arr, start, mid, end);
}

void mergeSort(vector<int> &arr)
{
    int start = 0;
    int end = arr.size();
    divide(arr, start, end);
}

void printArr(vector<int> &arr)
{
    for (int elem : arr)
        cout << elem << " ";
    cout << endl;
}

main()
{
    vector<int> arr = {10, 80, 50, 90, 70};
    printArr(arr);
    mergeSort(arr);
    printArr(arr);
}