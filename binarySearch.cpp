#include <iostream>
using namespace std;

// Binary Search (Iterative)
int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2; // avoid overflow

        if (arr[mid] == key) 
            return mid; // Key found at index mid

        else if (arr[mid] < key) 
            low = mid + 1; // Search right half

        else 
            high = mid - 1; // Search left half
    }
    return -1; // Key not found
}

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70};
    int n = sizeof(arr) / sizeof(arr[0]);

    int key = 40;
    int result = binarySearch(arr, n, key);

    if (result != -1)
        cout << "Element " << key << " found at index " << result << endl;
    else
        cout << "Element not found" << endl;

    return 0;
}
