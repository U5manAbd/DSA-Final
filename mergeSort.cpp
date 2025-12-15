#include <iostream>
using namespace std;

void merge(int array[], int startIndex, int middleIndex, int endIndex) {
    int leftSize = middleIndex - startIndex + 1;
    int rightSize = endIndex - middleIndex;

    int leftArray[leftSize];
    int rightArray[rightSize];

    for (int i = 0; i < leftSize; i++)
        leftArray[i] = array[startIndex + i];

    for (int j = 0; j < rightSize; j++)
        rightArray[j] = array[middleIndex + 1 + j];

    int leftIndex = 0, rightIndex = 0, mergedIndex = startIndex;

    while (leftIndex < leftSize && rightIndex < rightSize) {
        if (leftArray[leftIndex] <= rightArray[rightIndex]) {
            array[mergedIndex++] = leftArray[leftIndex++];
        } else {
            array[mergedIndex++] = rightArray[rightIndex++];
        }
    }

    while (leftIndex < leftSize)
        array[mergedIndex++] = leftArray[leftIndex++];

    while (rightIndex < rightSize)
        array[mergedIndex++] = rightArray[rightIndex++];
}

void mergeSort(int array[], int startIndex, int endIndex) {
    if (startIndex < endIndex) {
        int middleIndex = startIndex + (endIndex - startIndex) / 2;
        mergeSort(array, startIndex, middleIndex);
        mergeSort(array, middleIndex + 1, endIndex);
        merge(array, startIndex, middleIndex, endIndex);
    }
}

int main() {
    int array[] = {38, 27, 43, 3, 9, 82, 10};
    int size = sizeof(array) / sizeof(array[0]);

    cout << "Original Array: ";
    for (int i = 0; i < size; i++) cout << array[i] << " ";
    cout << endl;

    mergeSort(array, 0, size - 1);

    cout << "Sorted Array:   ";
    for (int i = 0; i < size; i++) cout << array[i] << " ";
    cout << endl;

    return 0;
}
