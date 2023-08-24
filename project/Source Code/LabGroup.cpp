#include <iostream>
#include <string>
#include <iomanip>      // lấy hàm setprecious để xuất chi tiết phần thập phân
#include <fstream>
#include "Sorting.h"     
using namespace std;
char pathIn[] = "input.txt";
char pathOut[] = "output.txt";
string AlgoSyntax[11] = {"selection-sort", "insertion-sort", "bubble-sort", "shaker-sort", "shell-sort", "merge-sort", "heap-sort", "quick-sort", "counting-sort", "radix-sort", "flash-sort"};
string AlgoName[11] = {"Selection Sort", "Insertion Sort", "Bubble Sort", "Shaker Sort", "Shell Sort", "Merge Sort", "Heap Sort", "Quick Sort", "Counting Sort", "Radix Sort", "Flash Sort"};

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// kiểm tra input là file text hay không
bool isFileText(string input){                     
	size_t found = input.find_last_of(".");      
	if(found == string::npos) return false;       
	else {
		string extension = input.substr(found + 1, input.length() - 1);
		if(extension == "txt") return true;     
		else return false;
	}
}

// kiểm tra input là số nguyên hay không
bool isNumber(string input){
	size_t found = input.find_first_not_of("0123456789");
    if(found == string::npos) return true;
    return false;
}

// kiểm tra nhập thuật toán đúng cú pháp
bool InvalidAlgo(string algo){
	for(int i = 0; i < 11; i++){
		if(algo == AlgoSyntax[i]){
			return false;
		}
	}
	cout << "Invalid Algorithm" << endl;
	return true;
}

// kiểm tra nhập đúng output parameter
bool InvalidOutput(string output){
	if(output != "-both" && output != "-time" && output != "-comp"){
		cout << "Invalid output parameter" << endl;
		return true;
	}
	else return false;
}

// gán tên thuật toán
void SetAlgo(string &algo){
	int i = 0;
	while(algo != AlgoSyntax[i]) i++;
	algo = AlgoName[i];
}

// gán tên thứ tự sắp xếp
void SetOrder(string &order){
	if(order == "-rand") order = "Randomized sorted data";
	else if(order == "-sorted") order = "Sorted data";
	else if(order == "-nsorted") order = "Nearly Sorted data";
	else if(order == "-rev") order = "Reversed sorted data";
}   

// Xuất ra file text
void OutputToFile(int arr[], int n, char* path){
	ofstream file;
	file.open(path);
	if(file.fail()){
		cout << "Output file doesn't exist" << endl;
		return;
	}
	file << n << endl;
	for(int i = 0; i < n; i++){
		file << arr[i] << " ";
	}
	file.close();
}

// Sắp xếp mảng
void Sort(string algo, int arr[], int size, double &time, unsigned long long &compare){
	clock_t start, end;
	start = clock();
	if(algo == "selection-sort") SelectionSort(arr, size, compare);
	else if(algo == "insertion-sort") InsertionSort(arr, size, compare);
	else if(algo == "bubble-sort") BubbleSort(arr, size, compare);
	else if(algo == "shaker-sort") ShakerSort(arr, size, compare);
	else if(algo == "shell-sort") ShellSort(arr, size, compare);
	else if(algo == "heap-sort") HeapSort(arr, size, compare);
	else if(algo == "merge-sort") MergeSort(arr, 0, size - 1, compare);
	else if(algo == "quick-sort")  QuickSort(arr, 0, size - 1, compare);
	else if(algo == "counting-sort") CountingSort(arr, size, compare);
	else if(algo == "radix-sort") RadixSort(arr, size, compare);
	else if(algo == "flash-sort") FlashSort(arr, size, compare);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
}

// Xuất Algorithm Mode ra console
void AlgorithmResult(string algo, int size, double time, unsigned long long compare, string output, char* path = NULL, string order = "NULL"){
	cout << "ALGORITHM MODE\n";
	SetAlgo(algo);
	SetOrder(order);
	cout << "Algorithm: " << algo << endl;
	if(path != NULL) cout << "Input file: " << path << endl;
	cout << "Input size: " << size << endl;
	if(order != "NULL") cout << "Input order: " << order << endl;
	cout << "--------------------------------------\n";
	if(output == "-time") cout << "Running time: " << time << "s\n";
	if(output == "-comp") cout << "Comparisions: " << compare << endl;
	if(output == "-both"){
		cout << "Running time: " << setprecision(3) << fixed << time << "s\n";
		cout << "Comparisions: " << compare << endl;
	}
	cout << endl;
}

// Command 1
void Command_1(string algo, char* path, string output){
	if(InvalidAlgo(algo)) return;
	if(InvalidOutput(output)) return;
	ifstream file;
	file.open(path);
	if(!file.fail()){
		int size; file >> size;
		int *arr = new int[size];
		double time;
		unsigned long long compare = 0;
		int i = 0;
		while(!file.eof()){
			file >> arr[i];
			i++;
		}
		Sort(algo, arr, size, time, compare);
		AlgorithmResult(algo, size, time, compare, output, path);
		OutputToFile(arr, size, pathOut);
        delete[] arr;
		file.close();
	}
	else cout << "File doesn't exist";
}

// Command 2
void Command_2(string algo, char* size, string order, string output){
	if(InvalidAlgo(algo)) return;
	if(InvalidOutput(output)) return;
	int n = atoi(size);
	if(n < 0){
		cout << "Invalid input size" << endl;
		return;
	}
	int *arr = new int[n];
	if(order == "-rand") GenerateData(arr, n, 0);
	else if(order == "-sorted") GenerateData(arr, n, 1);
	else if(order == "-nsorted") GenerateData(arr, n, 3);
	else if(order == "-rev") GenerateData(arr, n, 2);
	else {
		cout << "Invalid Order" << endl;
		return;
	};
	OutputToFile(arr, n, pathIn);
	double time;
	unsigned long long compare = 0;
	Sort(algo, arr, n, time, compare);
	AlgorithmResult(algo, n, time, compare, output, NULL, order);
	OutputToFile(arr, n, pathOut);
    delete[] arr;
}

// Command 3
void Command_3(string algo, char* size, string output){
	if(InvalidAlgo(algo)) return;
	if(InvalidOutput(output)) return;
	string p = algo;
	SetAlgo(p);
	string order;
	int n = atoi(size);
	if(n < 0){
		cout << "Invalid input size" << endl;
		return;
	}
	int *arr = new int[n];
	unsigned long long compare = 0;
	double time;
	char p1[] = "input_1.txt", p2[] = "input_2.txt", p3[] = "input_3.txt", p4[] = "input_4.txt";
	cout << "ALGORITHM MODE\n";
	cout << "Algorithm: " << p << endl << endl;
	for(int i = 0; i < 4; i++){
		GenerateData(arr, n, i);
		switch(i){
			case 0: 
            {
            order = "Randomized sorted data"; 
            OutputToFile(arr, n, p1);
            } break;
			case 1: 
            {
            order = "Sorted data"; 
            OutputToFile(arr, n, p3);
            }; break;
			case 2: 
            {
            order = "Reversed sorted data"; 
            OutputToFile(arr, n, p4);
            }; break;
			case 3: 
            {
            order = "Nearly sorted data"; 
            OutputToFile(arr, n, p2);
            }; break;
		}
		Sort(algo, arr, n, time, compare);
		cout << "Input order: " << order << endl;
		cout << "--------------------------------------\n";
		if(output == "-time") cout << "Running time: " << setprecision(3) << fixed << time << "s" << endl << endl;
     	if(output == "-comp") cout << "Comparisions: " << compare << endl;
    	if(output == "-both"){
     		cout << "Running time: " << setprecision(3) << fixed << time << "s\n";
     		cout << "Comparisions: " << compare << endl << endl;
    	}
		time = 0;
		compare = 0;
	}
    delete[] arr;
}

// Xuất Compare Mode ra console
void ComparisonResult(string algo1, string algo2, int arr1[], int arr2[], int size, double time1, double time2, unsigned long long compare1, unsigned long long compare2, char* path = NULL, string order = "NULL"){
	cout << "COMPARE MODE\n";
	SetAlgo(algo1);
	SetAlgo(algo2);
	SetOrder(order);
	cout << "Algorithm: " << algo1 << " | " << algo2 << endl;
	if(path != NULL) cout << "Input file: " << path << endl;
	cout << "Input size: " << size << endl;
	if(order != "NULL") cout << "Input order: " << order << endl;
	cout << "--------------------------------------\n";
	cout << "Running time: " << setprecision(3) << fixed << time1 << "s" << " | " << setprecision(3) << fixed << time2 << "s" << endl;
    cout << "Comparisions: " << compare1 << " | " << compare2 << endl;
}

// Command 4
void Command_4(string algo1, string algo2, char* path){
	if(InvalidAlgo(algo1) || InvalidAlgo(algo2)) return;
	ifstream file;
	file.open(path);
	if(!file.fail()){
		int i = 0;
		int temp;
		int size; file >> size;
    	int *arr1 = new int[size], *arr2 = new int[size];
		double time1, time2;
		unsigned long long compare1 = 0, compare2 = 0;
		while(!file.eof()){
			file >> temp;
			arr1[i] = temp;
			i++;
		}
        memcpy(arr2, arr1, sizeof(int) * size);
		Sort(algo1, arr1, size, time1, compare1);
		Sort(algo2, arr2, size, time2, compare2);
		ComparisonResult(algo1, algo2, arr1, arr2, size, time1, time2, compare1, compare2, path);
        delete[] arr1;
        delete[] arr2;
		file.close();
	} else {
		cout << "File doesn't exist" << endl;
	}
}

// Commmand 5
void Command_5(string algo1, string algo2, char* size, string order){
	if(InvalidAlgo(algo1) || InvalidAlgo(algo2)) return;
	int n = atoi(size);
	if(n < 0){
		cout << "Invalid input size" << endl;
		return;
	}
	int *arr1 = new int[n], *arr2 = new int[n];
	if(order == "-rand") GenerateData(arr1, n, 0);
	else if(order == "-sorted") GenerateData(arr1, n, 1);
	else if(order == "-nsorted") GenerateData(arr1, n, 3);
	else if(order == "-rev") GenerateData(arr1, n, 2);
	else {
		cout << "Invalid Order" << endl;
		return;
	}
	memcpy(arr2, arr1, sizeof(int) * n);
	OutputToFile(arr1, n, pathIn);
	double time1, time2;
	unsigned long long compare1 = 0, compare2 = 0;
	Sort(algo1, arr1, n, time1, compare1);
	Sort(algo2, arr2, n, time2, compare2);
	ComparisonResult(algo1, algo2, arr1, arr2, n, time1, time2, compare1, compare2, NULL, order);
    delete[] arr1;
    delete[] arr2;
}

int main(int argc, char *argv[]){
    string mode = argv[1];
	if(mode == "-a"){
		if(argc == 5) {
			if(isFileText(argv[3])) Command_1(argv[2], argv[3], argv[4]);
			else if(isNumber(argv[3])) Command_3(argv[2], argv[3], argv[4]);
			else cout << "Invalid parameters" << endl;
		} 
		else if(argc == 6) {
			if(isNumber(argv[3])) Command_2(argv[2], argv[3], argv[4], argv[5]);
			else cout << "Invalid parameters" << endl;
		} 
		else cout << "Invalid numbers of parameters" << endl;
	}
	else if(mode == "-c"){
		if(argc == 5){
			if(isFileText(argv[4])) Command_4(argv[2], argv[3], argv[4]);
			else cout << "Invalid parameters" << endl;
		}
		else if(argc == 6){
			if(isNumber(argv[4])) Command_5(argv[2], argv[3], argv[4], argv[5]);
			else cout << "Invalid parameters" << endl;
		}
		else cout << "Invalid numbers of parameters" << endl;
	}
	else cout << "Invalid Mode" << endl;
    return 0;
}

/* 
Source:
https://www.geeksforgeeks.org/insertion-sort/
https://www.geeksforgeeks.org/bubble-sort/
https://codelearn.io/learning/cau-truc-du-lieu-va-giai-thuat/856660
https://www.programiz.com/dsa/merge-sort
https://www.geeksforgeeks.org/quick-sort/
https://nguyenvanhieu.vn/counting-sort/
https://www.geeksforgeeks.org/radix-sort/
https://github.com/HaiDuc0147/sortingAlgorithm/tree/main/reportSort
https://codelearn.io/sharing/flash-sort-thuat-toan-sap-xep-than-thanh
*/