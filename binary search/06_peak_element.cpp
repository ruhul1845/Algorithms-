#include <bits/stdc++.h>
using namespace std;

/*
 * PEAK ELEMENT PROBLEMS
 * Peak element is an element greater than its neighbors
 * Time Complexity: O(log n)
 */

// Find a peak element in array
int findPeakElement(vector<int>& arr) {
    int n = arr.size();
    
    // Edge cases
    if (n == 1) return 0;
    if (arr[0] > arr[1]) return 0;
    if (arr[n-1] > arr[n-2]) return n - 1;
    
    int left = 1, right = n - 2;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Check if mid is peak
        if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]) {
            return mid;
        }
        
        // Move towards higher side
        if (arr[mid] < arr[mid + 1]) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

// Find all peak elements
vector<int> findAllPeaks(vector<int>& arr) {
    vector<int> peaks;
    int n = arr.size();
    
    if (n == 0) return peaks;
    if (n == 1) return {0};
    
    // Check first element
    if (arr[0] > arr[1]) peaks.push_back(0);
    
    // Check middle elements
    for (int i = 1; i < n - 1; i++) {
        if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {
            peaks.push_back(i);
        }
    }
    
    // Check last element
    if (arr[n-1] > arr[n-2]) peaks.push_back(n - 1);
    
    return peaks;
}

// Find peak in mountain array (bitonic array)
// Mountain array: strictly increases then strictly decreases
int peakIndexInMountainArray(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] < arr[mid + 1]) {
            // Ascending part, peak is to the right
            left = mid + 1;
        } else {
            // Descending part, peak is to the left or at mid
            right = mid;
        }
    }
    
    return left;
}

// Search in mountain array
int findInMountainArray(int target, vector<int>& mountainArr) {
    // Find peak
    int peak = peakIndexInMountainArray(mountainArr);
    
    // Binary search in ascending part
    int left = 0, right = peak;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (mountainArr[mid] == target) return mid;
        else if (mountainArr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    
    // Binary search in descending part
    left = peak + 1;
    right = mountainArr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (mountainArr[mid] == target) return mid;
        else if (mountainArr[mid] > target) left = mid + 1;
        else right = mid - 1;
    }
    
    return -1;
}

// Find minimum in bitonic array
int findMinInBitonic(vector<int>& arr) {
    int peak = peakIndexInMountainArray(arr);
    
    // Minimum is either at start or end
    return min(arr[0], arr[arr.size() - 1]);
}

// Find maximum in bitonic array
int findMaxInBitonic(vector<int>& arr) {
    int peak = peakIndexInMountainArray(arr);
    return arr[peak];
}

// Search in bitonic array for target
int searchBitonic(vector<int>& arr, int target) {
    int peak = peakIndexInMountainArray(arr);
    
    // Check peak
    if (arr[peak] == target) return peak;
    
    // Binary search in ascending part [0...peak-1]
    int left = 0, right = peak - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    
    // Binary search in descending part [peak+1...n-1]
    left = peak + 1;
    right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] > target) left = mid + 1;
        else right = mid - 1;
    }
    
    return -1;
}

// Find if array is bitonic
bool isBitonic(vector<int>& arr) {
    int n = arr.size();
    if (n < 3) return false;
    
    int i = 0;
    
    // Ascending part
    while (i < n - 1 && arr[i] < arr[i + 1]) {
        i++;
    }
    
    // No ascending or no descending
    if (i == 0 || i == n - 1) return false;
    
    // Descending part
    while (i < n - 1 && arr[i] > arr[i + 1]) {
        i++;
    }
    
    return i == n - 1;
}

// Longest bitonic subsequence length
int longestBitonicSubsequence(vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0;
    
    // LIS from left
    vector<int> lis(n, 1);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                lis[i] = max(lis[i], lis[j] + 1);
            }
        }
    }
    
    // LIS from right (LDS)
    vector<int> lds(n, 1);
    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (arr[j] < arr[i]) {
                lds[i] = max(lds[i], lds[j] + 1);
            }
        }
    }
    
    // Find max length
    int maxLen = 0;
    for (int i = 0; i < n; i++) {
        maxLen = max(maxLen, lis[i] + lds[i] - 1);
    }
    
    return maxLen;
}

int main() {
    // Find a peak element
    vector<int> arr1 = {1, 2, 3, 1};
    cout << "Array: ";
    for (int x : arr1) cout << x << " ";
    cout << "\nPeak element at index: " << findPeakElement(arr1) << "\n\n";
    
    // Find all peaks
    vector<int> arr2 = {1, 3, 2, 5, 4, 6, 8, 7};
    cout << "Array: ";
    for (int x : arr2) cout << x << " ";
    cout << "\nAll peak indices: ";
    vector<int> peaks = findAllPeaks(arr2);
    for (int p : peaks) cout << p << " ";
    cout << "\n\n";
    
    // Mountain array
    vector<int> mountain = {0, 2, 5, 10, 8, 3, 1};
    cout << "Mountain Array: ";
    for (int x : mountain) cout << x << " ";
    cout << "\nPeak index: " << peakIndexInMountainArray(mountain) << "\n";
    cout << "Search 8: " << findInMountainArray(8, mountain) << "\n";
    cout << "Is bitonic: " << (isBitonic(mountain) ? "Yes" : "No") << "\n\n";
    
    // Bitonic search
    vector<int> bitonic = {1, 3, 8, 12, 15, 11, 9, 5, 2};
    cout << "Bitonic Array: ";
    for (int x : bitonic) cout << x << " ";
    cout << "\nMax element: " << findMaxInBitonic(bitonic) << "\n";
    cout << "Min element: " << findMinInBitonic(bitonic) << "\n";
    cout << "Search 11: " << searchBitonic(bitonic, 11) << "\n";
    
    return 0;
}












