// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int> &data)
{
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for (int j = 1; j < data.size(); j++)
    {
        int key, i;
        key = data[j];
        i = j - 1;
        while (i >= 0 && data[i] > key)
        {
            data[i + 1] = data[i];
            i = i - 1;
        }
        data[i + 1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int> &data)
{
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int> &data, int low, int high)
{
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    if (low < high)
    {
        int q;
        q = Partition(data, low, high);
        QuickSortSubVector(data, low, q - 1);
        QuickSortSubVector(data, q + 1, high);
    }
    // Hint : recursively call itself
    //        Partition function is needed
}

int SortTool::Partition(vector<int> &data, int low, int high)
{
    // Function : Partition the vector
    // TODO : Please complete the function
    // Hint : Textbook page 171

    srand(time(NULL));
    int r = rand()%(high - low + 1) + low;
    swap(data[r], data[high]);
    
    int x = data[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++)
    {
        if (data[j] <= x)
        {
            i = i + 1;
            swap(data[i], data[j]);
        }
    }
    swap(data[i + 1], data[high]);

    return i + 1;
}

// Merge sort method
void SortTool::MergeSort(vector<int> &data)
{
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int> &data, int low, int high)
{
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    if (low < high)
    {
        int m1, m2;
        m1 = (low + high) / 2;
        m2 = m1 + 1;

        MergeSortSubVector(data, low, m1);
        MergeSortSubVector(data, m2, high);

        Merge(data, low, m1, m2, high);
    }

    // Hint : recursively call itself
    //        Merge function is needed
}

// Merge
void SortTool::Merge(vector<int> &data, int low, int m1, int m2, int high)
{
    // // Function : Merge two sorted subvector
    // // TODO : Please complete the function

    int n1 = m1 - low + 1;
    int n2 = high - m1;

    vector<int> L(n1 + 1);
    vector<int> R(n2 + 1);

    for (int i = 0; i <= n1 - 1; i++)
    {
        L[i] = data[low + i];
    }
    for (int j = 0; j <= n2 - 1; j++)
    {
        R[j] = data[m1 + j + 1];
    }
    L[n1] = 2147483647;
    R[n2] = 2147483647;
    int i = 0;
    int j = 0;
    for (int k = low; k <= high; k++)
    {
        if (L[i] <= R[j])
        {
            data[k] = L[i];
            i++;
        }
        else
        {
            data[k] = R[j];
            j++;
        }
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int> &data)
{
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--)
    {
        swap(data[0], data[i]);
        heapSize--;
        MaxHeapify(data, 0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int> &data, int root)
{
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int left, right, max_id = root;
    left = root * 2 + 1;
    right = root * 2 + 2;

    if (left < heapSize && data[left] > data[max_id])
    {
        max_id = left;
    }

    if (right < heapSize && data[right] > data[max_id])
    {
        max_id = right;
    }

    if (max_id != root)
    {
        swap(data[max_id], data[root]);
        MaxHeapify(data, max_id);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int> &data)
{
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i = data.size() / 2 - 1; i >= 0; i--)
    {
        MaxHeapify(data, i);
    }
}
