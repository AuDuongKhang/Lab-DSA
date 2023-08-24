#pragma once
#include "GenerateData.h"
#include <cstring>           // lấy hàm memset

// SELECTION SORT

void SelectionSort(int arr[], int n, unsigned long long &compare)
{
    int i, j, min_idx;

    for (i = 0; ++compare && i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; ++compare && j < n; j++)
            if (++compare && arr[j] < arr[min_idx])
                min_idx = j;

        HoanVi(arr[min_idx], arr[i]);
    }
}

// INSERTION SORT

void InsertionSort(int arr[], int n, unsigned long long &compare)
{
    int i, key, j;
    for (i = 1; ++compare && i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        // Move elements of arr[0..i-1], 
        // that are greater than key, to one
        // position ahead of their
        // current position
        while ((++compare && j >= 0) && (++compare && arr[j] > key))
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// BUBBLE SORT

void BubbleSort(int arr[], int n, unsigned long long &compare)
{
    int i, j;
    for (i = 0; ++compare && i < n - 1; i++)
        // Last i elements are already
        // in place
        for (j = 0;  ++compare && j < n - i - 1; j++)
            if (++compare && arr[j] > arr[j + 1])
                HoanVi(arr[j], arr[j + 1]);
}

// SHAKER SORT

void ShakerSort(int arr[], int n, unsigned long long &compare)
{
    bool swapped = true;
    int start = 0;
    int end = n - 1;
    while (swapped)
    {
        swapped = false;
        // loop from left to right same as
        // the bubble sort
        for (int i = start; ++compare && i < end; ++i)
        {
            if (++compare && arr[i] > arr[i + 1]) {
                HoanVi(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
        swapped = false;
        // move the end point back by one, because
        // item at the end is in its rightful spot
        --end;
        // from right to left, doing the
        // same comparison as in the previous stage
        for (int i = end - 1; ++compare && i >= start; --i)
        {
            if (++compare && arr[i] > arr[i + 1]) {
                HoanVi(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        // increase the starting point, because
        // the last stage would have moved the next
        // smallest number to its rightful spot.
        ++start;
    }
}

// SHELL SORT

void ShellSort(int a[], int n, unsigned long long &compare){
    int interval, i, j, temp;
    for(interval = n/2; ++compare && interval > 0; interval /= 2){
        for(i = interval; ++compare && i < n; i++){
            temp = a[i];
            for(j = i; (++compare && j >= interval) && (++compare && a[j - interval] > temp); j -= interval){
                a[j] = a[j - interval];
            }
            a[j] = temp;
        }
    }
}

// HEAP SORT

void heapify(int arr[], int n, int i, unsigned long long& compare)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if ((++compare && l < n) && (++compare && arr[l] > arr[largest]))
        largest = l;

    if ((++compare && r < n) && (++compare && arr[r] > arr[largest]))
        largest = r;
    // If largest is not root
    if (++compare && largest != i) {
        HoanVi(arr[i], arr[largest]);
        // Recursively heapify the affected
        // sub-tree
        heapify(arr, n, largest, compare);
    }
}

void HeapSort(int arr[], int n, unsigned long long& compare)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; ++compare && i >= 0; i--)
        heapify(arr, n, i, compare);
    // One by one extract an element
    // from heap
    for (int i = n - 1; ++compare && i > 0; i--) {
        HoanVi(arr[0], arr[i]);
        // call max heapify on the reduced heap
        heapify(arr, i, 0, compare);
    }
}

// MERGE SORT

void merge(int arr[], int p, int q, int r, unsigned long long &compare) {
  
  // Create L â† A[p..q] and M â† A[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;

  int *L = new int[n1], *M = new int[n2];
  for (int i = 0; ++compare && i < n1; i++)  L[i] = arr[p + i];
  for (int j = 0; ++compare && j < n2; j++)  M[j] = arr[q + 1 + j];

  // Maintain current index of sub-arrays and main array
  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
  while ((++compare && i < n1) && (++compare && j < n2)) {
    if (++compare && L[i] <= M[j]) {
      arr[k] = L[i];
      i++;
    }
    else {
      arr[k] = M[j];
      j++;
    }
    k++;
  }

  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
  while (++compare && i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }
  while (++compare && j < n2) {
    arr[k] = M[j];
    j++;
    k++;
  }
  delete[] L;
  delete[] M;
}

// Divide the array into two subarrays, sort them and merge them
void MergeSort(int a[], int Left, int Right, unsigned long long &compare) {
    int Mid;                        // Index of the middle element
    if (++compare && Left < Right) {             // The array has more than 1 element
        Mid = (Left + Right) / 2;     // Partition to 2 subarrays
        MergeSort(a, Left, Mid, compare);    // Sort 1â„2 left subarray
        MergeSort(a, Mid+1, Right, compare); // Sort 1â„2 right subarray // Merge two subarrays
        merge(a, Left, Mid, Right, compare);
    }
}

// QUICK SORT

int partition(int arr[], int low, int high, unsigned long long &compare)
{
    int pivot = arr[(high + low)/2];
    int i = low;
    int j = high;
    while(++compare && i <= j){
        while(++compare && arr[i] < pivot) i++;
        while(++compare && arr[j] > pivot) j--;
        if(++compare && i <= j){
            HoanVi(arr[i], arr[j]);
            i++; j--;
        }
    }
    return i;
}

void QuickSort(int arr[], int low, int high, unsigned long long &compare)
{
	if (++compare && low < high)
	{
		//  pi is partitioning index, arr[p] is now at right place 
		int pi = partition(arr, low, high, compare);

		// Separately sort elements before partition and after partition
		QuickSort(arr, low, pi - 1, compare);
		QuickSort(arr, pi + 1, high, compare);
	}
}

// COUNTING SORT

void CountingSort(int arr[], int n, unsigned long long &compare)
{
	int *output = new int[n];      // The output will have sorted input array
	int max = arr[0];
	int min = arr[0];
	int i;

	for (i = 1; ++compare && i < n; i++)
	{
		if (++compare && arr[i] > max)
			max = arr[i];            // Maximum value in array
		else if (++compare && arr[i] < min)
			min = arr[i];            // Minimum value in array
	}

	int k = max - min + 1;        // Size of count array

	int *count_array = new int[n];      // Create a count_array to store count of each individual input value
	
	// Initialize count_array elements as ze
	memset(count_array, 0, sizeof(int) * n);

    // Store count of each individual input value
	for (i = 0; ++compare && i < n; i++)
		count_array[arr[i] - min]++;           

	/* Change count_array so that count_array now contains actual
     position of input values in output array */
	for (i = 1; ++compare && i < k; i++)
		count_array[i] += count_array[i - 1];
	
	// Populate output array using count_array and input array
	for (i = 0; ++compare && i < n; i++)
	{
		output[count_array[arr[i] - min] - 1] = arr[i];
		count_array[arr[i] - min]--;
	}

	// Copy the output array to input, so that input now contains sorted values
	memcpy(arr, output, sizeof(int) * n);
    delete[] output;
    delete[] count_array;
}

// RADIX SORT

// A utility function to get maximum value in arr[]
int getMax(int arr[], int n, unsigned long long &compare)
{
	int mx = arr[0];
	for (int i = 1; ++compare && i < n; i++)
		if (++compare && arr[i] > mx)
			mx = arr[i];
	return mx;
}

// A function to do counting sort of arr[] according to the digit represented by exp.
void countSort(int arr[], int n, int exp, unsigned long long &compare)
{
	int *output = new int[n];          // output array
	int i, count[10] = { 0 };          

	// Store count of occurrences in count[]
	for (i = 0; ++compare && i < n; i++)
		count[(arr[i] / exp) % 10]++;

	// Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
	for (i = 1; ++compare && i < 10; i++)
		count[i] += count[i - 1];

	// Build the output array
	for (i = n - 1; ++compare && i >= 0; i--) {
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}
	
	// Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
	memcpy(arr, output, sizeof(int) * n);
    delete[] output;
}

void RadixSort(int arr[], const int n, unsigned long long &compare)
{
	// Find the maximum number to know number of digits
	int m = getMax(arr, n, compare);

	// Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
	for (int exp = 1; ++compare && m / exp > 0; exp *= 10)
		countSort(arr, n, exp, compare);
}

// FLASH SORT 

void FlashSort(int arr[], int n, unsigned long long &compare)
{
	int minVal = arr[0];
	int max = 0;
	int m = int(0.45 * n);              //khoi tao so phan lop
	int* l = new int[m];

	for (int i = 0; ++compare && i < m; i++)
		l[i] = 0;

	for (int i = 1; ++compare && i < n; i++)
	{
		if (arr[i] < minVal)            //check minValue 
			minVal = arr[i];
		if (arr[i] > arr[max])          //check vi tri phan tu lon nhat
			max = i;
	}

	if (arr[max] == minVal)
		return;

	double c1 = (double)(m - 1) / (arr[max] - minVal);

	for (int i = 0; ++compare && i < n; i++)
	{
		int k = int(c1 * (arr[i] - minVal));           //dem so luong phan tu vao phan lop k
		++l[k];
	}
		
	for (int i = 1; ++compare && i < m; i++)         //tim vi tri ket thuc cua tung phan lop
		l[i] += l[i - 1];

	//Hoan vi toan cuc
	HoanVi(arr[max], arr[0]);
	int nmove = 0;
	int j = 0;
	int k = m - 1;
	int t = 0;
	int flash;
	while (++compare && nmove < n - 1)                      //sap xep cac phan tu vao dung phan lop 
	{
		while (++compare && j > l[k] - 1)                
		{
			j++;
			k = int(c1 * (arr[j] - minVal));
		}
		flash = arr[j];
		if (++compare && k < 0) break;
		while (++compare && j != l[k])
		{
			k = int(c1 * (flash - minVal));
			int hold = arr[t = --l[k]];
			arr[t] = flash;
			flash = hold;
			++nmove;
		}
	}
	delete[] l;
	InsertionSort(arr, n, compare);
}
