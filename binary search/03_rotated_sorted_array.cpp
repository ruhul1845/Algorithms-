#include <bits/stdc++.h>
using namespace std;

/*
 * BINARY SEARCH IN ROTATED SORTED ARRAY
 * Time Complexity: O(log n)
 */

// Search in rotated sorted array (no duplicates)
int searchRotated(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        }
        
        // Check which half is sorted
        if (arr[left] <= arr[mid]) {  // Left half is sorted
            if (arr[left] <= target && target < arr[mid]) {
                right = mid - 1;  // Target in left half
            } else {
                left = mid + 1;   // Target in right half
            }
        } else {  // Right half is sorted
            if (arr[mid] < target && target <= arr[right]) {
                left = mid + 1;   // Target in right half
            } else {
                right = mid - 1;  // Target in left half
            }
        }
    }
    
    return -1;
}

// Search in rotated sorted array (with duplicates)
bool searchRotatedWithDuplicates(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return true;
        }
        
        // Handle duplicates
        if (arr[left] == arr[mid] && arr[mid] == arr[right]) {
            left++;
            right--;
            continue;
        }
        
        // Check which half is sorted
        if (arr[left] <= arr[mid]) {  // Left half is sorted
            if (arr[left] <= target && target < arr[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {  // Right half is sorted
            if (arr[mid] < target && target <= arr[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    
    return false;
}

// Find minimum in rotated sorted array
int findMin(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] > arr[right]) {
            // Minimum is in right half
            left = mid + 1;
        } else {
            // Minimum is in left half (including mid)
            right = mid;
        }
    }
    
    return arr[left];
}

// Find minimum in rotated sorted array (with duplicates)
int findMinWithDuplicates(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] > arr[right]) {
            left = mid + 1;
        } else if (arr[mid] < arr[right]) {
            right = mid;
        } else {
            // Can't determine which side, reduce search space
            right--;
        }
    }
    
    return arr[left];
}

// Find rotation count (or index of minimum element)
int findRotationCount(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    
    while (left < right) {
        // If array is already sorted
        if (arr[left] < arr[right]) {
            return left;
        }
        
        int mid = left + (right - left) / 2;
        int next = (mid + 1) % arr.size();
        int prev = (mid - 1 + arr.size()) % arr.size();
        
        // Check if mid is the minimum
        if (arr[mid] <= arr[next] && arr[mid] <= arr[prev]) {
            return mid;
        }
        
        if (arr[mid] <= arr[right]) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

// Find maximum in rotated sorted array
int findMax(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] > arr[right]) {
            // Maximum might be at mid or in right half
            if (mid < arr.size() - 1 && arr[mid] > arr[mid + 1]) {
                return arr[mid];
            }
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    // The element before minimum is maximum
    return arr[(left - 1 + arr.size()) % arr.size()];
}

int main() {
    vector<int> arr = {7, 8, 9, 1, 2, 3, 4, 5, 6};
    int target = 3;
    
    cout << "Rotated Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n\n";
    
    // Search in rotated array
    int idx = searchRotated(arr, target);
    cout << "Search " << target << ": " << (idx != -1 ? "Found at index " + to_string(idx) : "Not found") << "\n";
    
    // Find minimum
    cout << "Minimum element: " << findMin(arr) << "\n";
    
    // Find maximum
    cout << "Maximum element: " << findMax(arr) << "\n";
    
    // Find rotation count
    cout << "Rotation count: " << findRotationCount(arr) << "\n\n";
    
    // Test with duplicates
    vector<int> arrDup = {2, 2, 2, 3, 4, 2};
    cout << "Rotated Array with duplicates: ";
    for (int x : arrDup) cout << x << " ";
    cout << "\n";
    
    target = 3;
    cout << "Search " << target << ": " << (searchRotatedWithDuplicates(arrDup, target) ? "Found" : "Not found") << "\n";
    cout << "Minimum element: " << findMinWithDuplicates(arrDup) << "\n";
    
    return 0;
}

