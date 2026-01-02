/*
 * Basic Sorting Algorithms
 * Bubble Sort, Selection Sort, Insertion Sort
 * Time Complexity: O(n²)
 */

#include <bits/stdc++.h>
using namespace std;

// 1. Bubble Sort - O(n²)
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        
        if (!swapped) break; // Already sorted
    }
}

// 2. Selection Sort - O(n²)
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        
        swap(arr[i], arr[minIdx]);
    }
}

// 3. Insertion Sort - O(n²), good for nearly sorted arrays
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        arr[j + 1] = key;
    }
}

// 4. Recursive Bubble Sort
void recursiveBubbleSort(vector<int>& arr, int n) {
    if (n == 1) return;
    
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            swap(arr[i], arr[i + 1]);
        }
    }
    
    recursiveBubbleSort(arr, n - 1);
}

// 5. Recursive Insertion Sort
void recursiveInsertionSort(vector<int>& arr, int n) {
    if (n <= 1) return;
    
    recursiveInsertionSort(arr, n - 1);
    
    int last = arr[n - 1];
    int j = n - 2;
    
    while (j >= 0 && arr[j] > last) {
        arr[j + 1] = arr[j];
        j--;
    }
    
    arr[j + 1] = last;
}

// 6. Shell Sort - Optimized Insertion Sort
void shellSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            
            arr[j] = temp;
        }
    }
}

// 7. Cocktail Shaker Sort (Bidirectional Bubble Sort)
void cocktailSort(vector<int>& arr) {
    bool swapped = true;
    int start = 0;
    int end = arr.size() - 1;
    
    while (swapped) {
        swapped = false;
        
        // Forward pass
        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        
        if (!swapped) break;
        
        swapped = false;
        end--;
        
        // Backward pass
        for (int i = end - 1; i >= start; i--) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        
        start++;
    }
}

// 8. Comb Sort
void combSort(vector<int>& arr) {
    int n = arr.size();
    int gap = n;
    bool swapped = true;
    
    while (gap != 1 || swapped) {
        gap = (gap * 10) / 13;
        if (gap < 1) gap = 1;
        
        swapped = false;
        
        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

void printArray(vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    // Test Bubble Sort
    vector<int> arr1 = {64, 34, 25, 12, 22, 11, 90};
    cout << "Original array: ";
    printArray(arr1);
    
    bubbleSort(arr1);
    cout << "Bubble Sort: ";
    printArray(arr1);
    
    // Test Selection Sort
    vector<int> arr2 = {64, 25, 12, 22, 11};
    selectionSort(arr2);
    cout << "Selection Sort: ";
    printArray(arr2);
    
    // Test Insertion Sort
    vector<int> arr3 = {12, 11, 13, 5, 6};
    insertionSort(arr3);
    cout << "Insertion Sort: ";
    printArray(arr3);
    
    // Test Shell Sort
    vector<int> arr4 = {12, 34, 54, 2, 3};
    shellSort(arr4);
    cout << "Shell Sort: ";
    printArray(arr4);
    
    return 0;
}

