#pragma once
#include <iostream>
#include <time.h>
#include <stdlib.h>             // lấy hàm srand, rand, atoi 
using namespace std;

template <class T>
void HoanVi(T &a, T &b)
{
	T x = a;
	a = b;
	b = x;
}

void GenerateRandomData(int a[], int n)
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % n;
	}
}

void GenerateSortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
}

void GenerateReverseData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = n - 1 - i;
	}
}

void GenerateNearlySortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
	srand((unsigned int) time(NULL));
	for (int i = 0; i < 10; i ++)
	{
		int r1 = rand() % n;
		int r2 = rand() % n;
		HoanVi(a[r1], a[r2]);
	}
}

void GenerateData(int a[], int n, int dataType)
{
	switch (dataType)
	{
	case 0:	// ngẫu nhiên
		GenerateRandomData(a, n);
		break;
	case 1:	// sắp xếp sẵn
		GenerateSortedData(a, n);
		break;
	case 2:	// sắp xếp ngược
		GenerateReverseData(a, n);
		break;
	case 3:	// gần như sắp xếp sẵn
		GenerateNearlySortedData(a, n);
		break;
	default:
		cout << "Error: unknown data type!\n";
	}
}