#include <iostream>
using namespace std;

int partition(int array[], int startIndex, int endIndex) {
    int pivotValue = array[endIndex];  // choose pivot
    int smallerIndex = startIndex - 1;

    for (int currentIndex = startIndex; currentIndex < endIndex; currentIndex++) {
        if (array[currentIndex] < pivotValue) {
            smallerIndex++;
            swap(array[smallerIndex], array[currentIndex]);
        }
    }

    swap(array[smallerIndex + 1], array[endIndex]);
    return smallerIndex + 1;
}

void quickSort(int array[], int startIndex, int endIndex) {
    if (startIndex < endIndex) {
        int pivotIndex = partition(array, startIndex, endIndex);
        quickSort(array, startIndex, pivotIndex - 1);
        quickSort(array, pivotIndex + 1, endIndex);
    }
}

int main() {
    int array[] = {10, 80, 30, 90, 40, 50, 70};
    int size = sizeof(array) / sizeof(array[0]);

    cout << "Original Array: ";
    for (int i = 0; i < size; i++) cout << array[i] << " ";
    cout << endl;

    quickSort(array, 0, size - 1);

    cout << "Sorted Array:   ";
    for (int i = 0; i < size; i++) cout << array[i] << " ";
    cout << endl;

    return 0;
}
