#include <bits/stdc++.h>
using namespace std;

/*
 * BINARY SEARCH ON ANSWER
 * Used for optimization problems where we search for the best answer
 * in a range of possible values
 */

// Square root using binary search
int mySqrt(int x) {
    if (x == 0 || x == 1) return x;
    
    long long left = 1, right = x;
    long long result = 0;
    
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        long long square = mid * mid;
        
        if (square == x) {
            return mid;
        } else if (square < x) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// Find sqrt with precision
double sqrtPrecision(double x, double precision = 1e-6) {
    if (x == 0 || x == 1) return x;
    
    double left = 0, right = x;
    if (x < 1) right = 1;
    
    while (right - left > precision) {
        double mid = left + (right - left) / 2;
        double square = mid * mid;
        
        if (square == x) {
            return mid;
        } else if (square < x) {
            left = mid;
        } else {
            right = mid;
        }
    }
    
    return (left + right) / 2;
}

// Allocate minimum pages (Book allocation problem)
bool isPossible(vector<int>& pages, int n, int m, int maxPages) {
    int students = 1;
    int currentPages = 0;
    
    for (int i = 0; i < n; i++) {
        if (pages[i] > maxPages) return false;
        
        if (currentPages + pages[i] > maxPages) {
            students++;
            currentPages = pages[i];
            
            if (students > m) return false;
        } else {
            currentPages += pages[i];
        }
    }
    
    return true;
}

int allocateBooks(vector<int>& pages, int m) {
    int n = pages.size();
    if (m > n) return -1;
    
    int left = *max_element(pages.begin(), pages.end());
    int right = accumulate(pages.begin(), pages.end(), 0);
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (isPossible(pages, n, m, mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return result;
}

// Aggressive cows (or minimum distance maximization)
bool canPlaceCows(vector<int>& stalls, int cows, int minDist) {
    int count = 1;
    int lastPos = stalls[0];
    
    for (int i = 1; i < stalls.size(); i++) {
        if (stalls[i] - lastPos >= minDist) {
            count++;
            lastPos = stalls[i];
            
            if (count >= cows) return true;
        }
    }
    
    return false;
}

int aggressiveCows(vector<int>& stalls, int cows) {
    sort(stalls.begin(), stalls.end());
    
    int left = 1;
    int right = stalls.back() - stalls[0];
    int result = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (canPlaceCows(stalls, cows, mid)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// Painter's partition problem
bool canPaint(vector<int>& boards, int painters, long long maxTime) {
    int count = 1;
    long long currentTime = 0;
    
    for (int board : boards) {
        if (board > maxTime) return false;
        
        if (currentTime + board > maxTime) {
            count++;
            currentTime = board;
            
            if (count > painters) return false;
        } else {
            currentTime += board;
        }
    }
    
    return true;
}

long long painterPartition(vector<int>& boards, int painters) {
    long long left = *max_element(boards.begin(), boards.end());
    long long right = accumulate(boards.begin(), boards.end(), 0LL);
    long long result = right;
    
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        
        if (canPaint(boards, painters, mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return result;
}

// Kth smallest element in multiplication table
int findKthNumber(int m, int n, int k) {
    int left = 1, right = m * n;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        int count = 0;
        
        // Count elements <= mid
        for (int i = 1; i <= m; i++) {
            count += min(mid / i, n);
        }
        
        if (count < k) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}

// Median of two sorted arrays
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    if (nums1.size() > nums2.size()) {
        return findMedianSortedArrays(nums2, nums1);
    }
    
    int m = nums1.size(), n = nums2.size();
    int left = 0, right = m;
    
    while (left <= right) {
        int partition1 = left + (right - left) / 2;
        int partition2 = (m + n + 1) / 2 - partition1;
        
        int maxLeft1 = (partition1 == 0) ? INT_MIN : nums1[partition1 - 1];
        int minRight1 = (partition1 == m) ? INT_MAX : nums1[partition1];
        
        int maxLeft2 = (partition2 == 0) ? INT_MIN : nums2[partition2 - 1];
        int minRight2 = (partition2 == n) ? INT_MAX : nums2[partition2];
        
        if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1) {
            if ((m + n) % 2 == 0) {
                return (max(maxLeft1, maxLeft2) + min(minRight1, minRight2)) / 2.0;
            } else {
                return max(maxLeft1, maxLeft2);
            }
        } else if (maxLeft1 > minRight2) {
            right = partition1 - 1;
        } else {
            left = partition1 + 1;
        }
    }
    
    return 0.0;
}

int main() {
    // Square root
    int x = 27;
    cout << "Square root of " << x << ": " << mySqrt(x) << "\n";
    cout << "Square root (precise): " << sqrtPrecision(x) << "\n\n";
    
    // Book allocation
    vector<int> pages = {12, 34, 67, 90};
    int students = 2;
    cout << "Book allocation for " << students << " students: " << allocateBooks(pages, students) << "\n\n";
    
    // Aggressive cows
    vector<int> stalls = {1, 2, 4, 8, 9};
    int cows = 3;
    cout << "Maximum minimum distance (Aggressive Cows): " << aggressiveCows(stalls, cows) << "\n\n";
    
    // Painter's partition
    vector<int> boards = {10, 20, 30, 40};
    int painters = 2;
    cout << "Minimum time (Painter's Partition): " << painterPartition(boards, painters) << "\n\n";
    
    // Median of two sorted arrays
    vector<int> nums1 = {1, 3};
    vector<int> nums2 = {2};
    cout << "Median of two sorted arrays: " << findMedianSortedArrays(nums1, nums2) << "\n";
    
    return 0;
}



