#include <iostream>
using namespace std;

void countingSort(int arr[], int n) {
    // 1. Find maximum element
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }

    // 2. Create count array
    int* count = new int[maxVal + 1];
    for (int i = 0; i <= maxVal; i++) {
        count[i] = 0;
    }

    // 3. Count frequency
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    // 4. Cumulative count (prefix sum)
    for (int i = 1; i <= maxVal; i++) {
        count[i] += count[i - 1];
    }

    // 5. Build output array (stable)
    int* output = new int[n];
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // 6. Copy back
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    delete[] count;
    delete[] output;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int* arr = new int[n];

    cout << "Enter " << n << " non-negative integers: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    countingSort(arr, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;
    return 0;
}
