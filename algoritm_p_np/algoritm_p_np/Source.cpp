//парно-непарне
#include <iostream>

using namespace std;

void oddEvenSort(int* arr, int size) {
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (int i = 1; i < size - 1; i += 2)  // Odd
        {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }

        for (int i = 0; i < size - 1; i += 2)  // Even
        {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }
    }
}

void show(int* arr, int size) {
    for (int i = 0; i < size; i++) 
        cout << arr[i] << "\n";
}

int main() {
    int size, element;
    cout << "Enter the number of elements: ";
    cin >> size;

    int *arr = new int [size];
    
    cout << "Enter unsorted elements: \n";

    for (int i = 0; i < size; i++) {
        cin >> element;
        arr[i]=element;
    }

    oddEvenSort(arr, size);

    cout << "\nSorted array: \n";
    show(arr, size);

    delete[] arr;
    return 0;
}
