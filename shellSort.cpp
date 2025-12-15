#include <iostream>
using namespace std;

void shellSort(int arr[], int n) {
    // Start with a large gap, then reduce it
    for (int gap = n / 2; gap > 0; gap /= 2) {

        // Perform gapped insertion sort
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;

            // Shift earlier gap-sorted elements up
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            arr[j] = temp;
        }
    }
}

int main() {
    int arr[] = {8, 5, 3, 7, 6, 2, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    shellSort(arr, n);

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    return 0;
}
