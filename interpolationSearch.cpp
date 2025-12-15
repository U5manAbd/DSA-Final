#include <iostream>
using namespace std;

// Interpolation Search
int interpolationSearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;

    while (low <= high && key >= arr[low] && key <= arr[high]) {
        // Estimate position using interpolation formula
        int pos = low + ((double)(key - arr[low]) * (high - low)) / (arr[high] - arr[low]);

        if (arr[pos] == key) 
            return pos; // Key found

        else if (arr[pos] < key) 
            low = pos + 1; // Search right half

        else 
            high = pos - 1; // Search left half
    }
    return -1; // Key not found
}

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70};
    int n = sizeof(arr) / sizeof(arr[0]);

    int key = 50;
    int result = interpolationSearch(arr, n, key);

    if (result != -1)
        cout << "Element " << key << " found at index " << result << endl;
    else
        cout << "Element not found" << endl;

    return 0;
}
