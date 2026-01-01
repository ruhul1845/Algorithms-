#include <bits/stdc++.h>
using namespace std;

/*
 * FIRST AND LAST OCCURRENCE IN SORTED ARRAY
 * Used when array contains duplicate elements
 * Time Complexity: O(log n)
 */

// Find first occurrence of target
int findFirstOccurrence(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1;  // Continue searching in left half
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// Find last occurrence of target
int findLastOccurrence(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            left = mid + 1;  // Continue searching in right half
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// Count occurrences of target
int countOccurrences(vector<int>& arr, int target) {
    int first = findFirstOccurrence(arr, target);
    if (first == -1) return 0;
    
    int last = findLastOccurrence(arr, target);
    return last - first + 1;
}

// Find first and last position (LeetCode 34)
vector<int> searchRange(vector<int>& arr, int target) {
    int first = findFirstOccurrence(arr, target);
    if (first == -1) return {-1, -1};
    
    int last = findLastOccurrence(arr, target);
    return {first, last};
}

// Find first occurrence greater than target
int findFirstGreater(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    int result = -1;
    
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

// Find last occurrence smaller than target
int findLastSmaller(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] < target) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// Find ceiling of target (smallest element >= target)
int findCeiling(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    int result = -1;
    
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

// Find floor of target (largest element <= target)
int findFloor(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] <= target) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

int main() {
    vector<int> arr = {1, 2, 2, 2, 3, 4, 5, 5, 5, 5, 6, 7, 8, 8};
    int target = 5;
    
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nTarget: " << target << "\n\n";
    
    // First occurrence
    int first = findFirstOccurrence(arr, target);
    cout << "First occurrence: " << first << "\n";
    
    // Last occurrence
    int last = findLastOccurrence(arr, target);
    cout << "Last occurrence: " << last << "\n";
    
    // Count occurrences
    cout << "Count of " << target << ": " << countOccurrences(arr, target) << "\n";
    
    // Search range
    vector<int> range = searchRange(arr, target);
    cout << "Search range: [" << range[0] << ", " << range[1] << "]\n\n";
    
    // Other operations
    target = 4;
    cout << "Target: " << target << "\n";
    int idx = findFirstGreater(arr, target);
    cout << "First greater than " << target << ": " << (idx != -1 ? to_string(arr[idx]) : "None") << "\n";
    
    idx = findLastSmaller(arr, target);
    cout << "Last smaller than " << target << ": " << (idx != -1 ? to_string(arr[idx]) : "None") << "\n";
    
    idx = findCeiling(arr, target);
    cout << "Ceiling of " << target << ": " << (idx != -1 ? to_string(arr[idx]) : "None") << "\n";
    
    idx = findFloor(arr, target);
    cout << "Floor of " << target << ": " << (idx != -1 ? to_string(arr[idx]) : "None") << "\n";
    
    return 0;
}

