#include <bits/stdc++.h>
using namespace std;

/*
 * EXPONENTIAL SEARCH
 * Also called doubling search or galloping search
 * Useful for unbounded or infinite arrays
 * Time Complexity: O(log n)
 * Better than binary search when element is closer to beginning
 */

// Standard binary search helper
int binarySearch(vector<int>& arr, int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

// Exponential search
int exponentialSearch(vector<int>& arr, int target) {
    int n = arr.size();
    
    // If target is at first position
    if (arr[0] == target) return 0;
    
    // Find range for binary search by repeated doubling
    int i = 1;
    while (i < n && arr[i] <= target) {
        i *= 2;
    }
    
    // Perform binary search in found range
    return binarySearch(arr, i / 2, min(i, n - 1), target);
}

// Exponential search for unbounded/infinite array
int exponentialSearchUnbounded(vector<int>& arr, int target) {
    // If target is at first position
    if (arr[0] == target) return 0;
    
    // Find range by repeated doubling
    int i = 1;
    while (arr[i] <= target) {
        i *= 2;
    }
    
    // Perform binary search in found range
    return binarySearch(arr, i / 2, i, target);
}

// Find first occurrence using exponential search
int findFirstOccurrenceExp(vector<int>& arr, int target) {
    int n = arr.size();
    
    if (arr[0] == target) return 0;
    
    // Find range
    int i = 1;
    while (i < n && arr[i] < target) {
        i *= 2;
    }
    
    // Binary search for first occurrence
    int left = i / 2;
    int right = min(i, n - 1);
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// Find position of target in infinite sorted array
int searchInfinite(vector<int>& arr, int target) {
    // Start with first element
    int low = 0, high = 1;
    
    // Double high until we find a value greater than target
    while (arr[high] < target) {
        low = high;
        high = 2 * high;
    }
    
    // Now do binary search
    return binarySearch(arr, low, high, target);
}

// Interpolation search (works well for uniformly distributed data)
int interpolationSearch(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while (left <= right && target >= arr[left] && target <= arr[right]) {
        if (left == right) {
            if (arr[left] == target) return left;
            return -1;
        }
        
        // Probe position using interpolation
        int pos = left + ((double)(right - left) / (arr[right] - arr[left])) * (target - arr[left]);
        
        if (arr[pos] == target) {
            return pos;
        } else if (arr[pos] < target) {
            left = pos + 1;
        } else {
            right = pos - 1;
        }
    }
    
    return -1;
}

// Jump search
int jumpSearch(vector<int>& arr, int target) {
    int n = arr.size();
    int step = sqrt(n);
    int prev = 0;
    
    // Jump to find the block where element may be present
    while (arr[min(step, n) - 1] < target) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) return -1;
    }
    
    // Linear search in the identified block
    while (arr[prev] < target) {
        prev++;
        if (prev == min(step, n)) return -1;
    }
    
    if (arr[prev] == target) return prev;
    
    return -1;
}

// Fibonacci search
int fibonacciSearch(vector<int>& arr, int target) {
    int n = arr.size();
    
    // Initialize fibonacci numbers
    int fib2 = 0;  // (m-2)'th Fibonacci
    int fib1 = 1;  // (m-1)'th Fibonacci
    int fib = fib2 + fib1;  // m'th Fibonacci
    
    // Find smallest Fibonacci >= n
    while (fib < n) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib2 + fib1;
    }
    
    int offset = -1;
    
    while (fib > 1) {
        int i = min(offset + fib2, n - 1);
        
        if (arr[i] < target) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        } else if (arr[i] > target) {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        } else {
            return i;
        }
    }
    
    if (fib1 && offset + 1 < n && arr[offset + 1] == target) {
        return offset + 1;
    }
    
    return -1;
}

// Meta binary search (One sided binary search)
int metaBinarySearch(vector<int>& arr, int target) {
    int n = arr.size();
    int lg = log2(n - 1) + 1;
    int pos = 0;
    
    for (int i = lg - 1; i >= 0; i--) {
        if (arr[pos] == target) return pos;
        
        int new_pos = pos | (1 << i);
        
        if (new_pos < n && arr[new_pos] <= target) {
            pos = new_pos;
        }
    }
    
    return (arr[pos] == target) ? pos : -1;
}

// Ubiquitous binary search (finds any occurrence fast)
int ubiquitousBinarySearch(vector<int>& arr, int target) {
    int n = arr.size();
    int pos = 0;
    
    for (int i = n / 2; i >= 1; i /= 2) {
        while (pos + i < n && arr[pos + i] <= target) {
            pos += i;
        }
    }
    
    return (pos < n && arr[pos] == target) ? pos : -1;
}

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31};
    int target = 19;
    
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nTarget: " << target << "\n\n";
    
    // Exponential search
    int idx = exponentialSearch(arr, target);
    cout << "Exponential Search: " << (idx != -1 ? "Found at index " + to_string(idx) : "Not found") << "\n";
    
    // Interpolation search
    idx = interpolationSearch(arr, target);
    cout << "Interpolation Search: " << (idx != -1 ? "Found at index " + to_string(idx) : "Not found") << "\n";
    
    // Jump search
    idx = jumpSearch(arr, target);
    cout << "Jump Search: " << (idx != -1 ? "Found at index " + to_string(idx) : "Not found") << "\n";
    
    // Fibonacci search
    idx = fibonacciSearch(arr, target);
    cout << "Fibonacci Search: " << (idx != -1 ? "Found at index " + to_string(idx) : "Not found") << "\n";
    
    // Meta binary search
    idx = metaBinarySearch(arr, target);
    cout << "Meta Binary Search: " << (idx != -1 ? "Found at index " + to_string(idx) : "Not found") << "\n";
    
    // Ubiquitous binary search
    idx = ubiquitousBinarySearch(arr, target);
    cout << "Ubiquitous Binary Search: " << (idx != -1 ? "Found at index " + to_string(idx) : "Not found") << "\n\n";
    
    // Test with duplicates for first occurrence
    vector<int> arrDup = {1, 2, 2, 2, 3, 4, 5, 5, 5, 6};
    target = 5;
    cout << "Array with duplicates: ";
    for (int x : arrDup) cout << x << " ";
    cout << "\nFirst occurrence of " << target << ": " << findFirstOccurrenceExp(arrDup, target) << "\n";
    
    // Comparison of search methods
    cout << "\nSearch Algorithm Comparison:\n";
    cout << "1. Binary Search: O(log n), works on sorted arrays\n";
    cout << "2. Exponential Search: O(log n), better when element is near beginning\n";
    cout << "3. Interpolation Search: O(log log n) average, O(n) worst, for uniform distribution\n";
    cout << "4. Jump Search: O(√n), useful when jumping back is costly\n";
    cout << "5. Fibonacci Search: O(log n), useful for non-uniform data access costs\n";
    
    return 0;
}












