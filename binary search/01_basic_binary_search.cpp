#include <bits/stdc++.h>
using namespace std;

/*
 * BASIC BINARY SEARCH
 * Time Complexity: O(log n)
 * Space Complexity: O(1) for iterative, O(log n) for recursive
 */

// Iterative Binary Search
int binarySearchIterative(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;  // Prevents overflow
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;  // Element not found
}

// Recursive Binary Search
int binarySearchRecursive(vector<int>& arr, int left, int right, int target) {
    if (left > right) {
        return -1;
    }
    
    int mid = left + (right - left) / 2;
    
    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] < target) {
        return binarySearchRecursive(arr, mid + 1, right, target);
    } else {
        return binarySearchRecursive(arr, left, mid - 1, target);
    }
}

// Binary Search using STL
bool binarySearchSTL(vector<int>& arr, int target) {
    return binary_search(arr.begin(), arr.end(), target);
}

// Lower Bound - First position where element >= target
int lowerBound(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    int result = arr.size();
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] >= target) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return result;
}

// Upper Bound - First position where element > target
int upperBound(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    int result = arr.size();
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] > target) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return result;
}

// Binary Search in descending sorted array
int binarySearchDescending(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] > target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

int main() {
    vector<int> arr = {2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78};
    int target = 23;
    
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nTarget: " << target << "\n\n";
    
    // Iterative Binary Search
    int idx = binarySearchIterative(arr, target);
    cout << "Iterative Binary Search: " << (idx != -1 ? "Found at index " + to_string(idx) : "Not found") << "\n";
    
    // Recursive Binary Search
    idx = binarySearchRecursive(arr, 0, arr.size() - 1, target);
    cout << "Recursive Binary Search: " << (idx != -1 ? "Found at index " + to_string(idx) : "Not found") << "\n";
    
    // STL Binary Search
    cout << "STL Binary Search: " << (binarySearchSTL(arr, target) ? "Found" : "Not found") << "\n";
    
    // Lower Bound
    cout << "Lower Bound of " << target << ": " << lowerBound(arr, target) << "\n";
    
    // Upper Bound
    cout << "Upper Bound of " << target << ": " << upperBound(arr, target) << "\n";
    
    // Test with descending array
    vector<int> descArr = {78, 67, 56, 45, 38, 23, 16, 12, 8, 5, 2};
    cout << "\nDescending Array: ";
    for (int x : descArr) cout << x << " ";
    cout << "\n";
    
    idx = binarySearchDescending(descArr, target);
    cout << "Binary Search (Descending): " << (idx != -1 ? "Found at index " + to_string(idx) : "Not found") << "\n";
    
    return 0;
}












