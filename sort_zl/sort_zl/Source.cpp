//злиттям
#include <iostream>
//#include<ctime>
using namespace std;

void merge(int* arr, int left, int middle, int right, int size)
{
    int i = left;
    int j = middle + 1;
    int k = left;
 
    int *temp= new int [size];
    for (int i = 0; i < size; i++) {
        temp[i] = 0;
    }        
 
    while (i <= middle && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            i++; k++;
        }
        else {
            temp[k] = arr[j];
            j++; k++;
        }
    }

    while (i <= middle) {
        temp[k] = arr[i];
        i++; k++;
    }
 
    while (j <= right) {
        temp[k] = arr[j];
        j++; k++;
    }
 
    for (int p = left; p <= right; p++) {
        arr[p] = temp[p];
    }
    delete[] temp;
} 

void merge_sort(int* arr, int left, int right, int size)
{

    if (left < right) {
        int middle = (left + right) / 2;
 
        merge_sort(arr, left, middle, size);
        merge_sort(arr, middle + 1, right, size);
 
        merge(arr, left, middle, right, size);
    }
}
/*
void rand_arr(int* arr, int size)
{
    srand(time(NULL));
    for (int i = 0; i < size; i++)
        arr[i] = rand() % 101 - 50;
}
*/
void show(int* arr, int size)
{
    cout << "\nyour array: \n";
    for (int i = 0; i < size; i++)
        cout << arr[i] << "\n";
}

int main() {
    int size;
    cout << "enter size of array: ";
    cin >> size;

    int* arr = new int[size];

   // rand_arr(arr, size);
    show(arr, size);
    cout << "\n*sorting...*\n";
    merge_sort(arr, 0, (size-1), size);
    show(arr, size);

    delete[] arr;
    return 0;
}