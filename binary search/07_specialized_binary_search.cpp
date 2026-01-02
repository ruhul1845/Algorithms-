#include <bits/stdc++.h>
using namespace std;

/*
 * SPECIALIZED BINARY SEARCH PROBLEMS
 * Advanced applications and variations
 */

// Find the smallest letter greater than target (wrap around)
char nextGreatestLetter(vector<char>& letters, char target) {
    int left = 0, right = letters.size() - 1;
    
    // If target is greater than or equal to last element, wrap around
    if (target >= letters[right]) return letters[0];
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (letters[mid] <= target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return letters[left];
}

// Find K closest elements
vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    int left = 0, right = arr.size() - k;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        // Compare distances from x
        if (x - arr[mid] > arr[mid + k] - x) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return vector<int>(arr.begin() + left, arr.begin() + left + k);
}

// Find minimum in sorted rotated array II (with duplicates)
int findMinWithDuplicates(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] > arr[right]) {
            left = mid + 1;
        } else if (arr[mid] < arr[right]) {
            right = mid;
        } else {
            // arr[mid] == arr[right], can't determine which side
            right--;
        }
    }
    
    return arr[left];
}

// Split array largest sum
bool canSplit(vector<int>& nums, int m, long long maxSum) {
    int subarrays = 1;
    long long currentSum = 0;
    
    for (int num : nums) {
        if (currentSum + num > maxSum) {
            subarrays++;
            currentSum = num;
            
            if (subarrays > m) return false;
        } else {
            currentSum += num;
        }
    }
    
    return true;
}

int splitArray(vector<int>& nums, int m) {
    long long left = *max_element(nums.begin(), nums.end());
    long long right = accumulate(nums.begin(), nums.end(), 0LL);
    long long result = right;
    
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        
        if (canSplit(nums, m, mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return result;
}

// Capacity to ship packages within D days
bool canShip(vector<int>& weights, int days, int capacity) {
    int daysNeeded = 1;
    int currentWeight = 0;
    
    for (int weight : weights) {
        if (currentWeight + weight > capacity) {
            daysNeeded++;
            currentWeight = weight;
            
            if (daysNeeded > days) return false;
        } else {
            currentWeight += weight;
        }
    }
    
    return true;
}

int shipWithinDays(vector<int>& weights, int days) {
    int left = *max_element(weights.begin(), weights.end());
    int right = accumulate(weights.begin(), weights.end(), 0);
    int result = right;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (canShip(weights, days, mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return result;
}

// Koko eating bananas
bool canEatAll(vector<int>& piles, int h, long long k) {
    long long hours = 0;
    
    for (int pile : piles) {
        hours += (pile + k - 1) / k;  // Ceiling division
        if (hours > h) return false;
    }
    
    return true;
}

int minEatingSpeed(vector<int>& piles, int h) {
    int left = 1;
    int right = *max_element(piles.begin(), piles.end());
    int result = right;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (canEatAll(piles, h, mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return result;
}

// Minimum time to complete trips
bool canComplete(vector<int>& time, int totalTrips, long long maxTime) {
    long long trips = 0;
    
    for (int t : time) {
        trips += maxTime / t;
        if (trips >= totalTrips) return true;
    }
    
    return false;
}

long long minimumTime(vector<int>& time, int totalTrips) {
    long long left = 1;
    long long right = (long long)*min_element(time.begin(), time.end()) * totalTrips;
    long long result = right;
    
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        
        if (canComplete(time, totalTrips, mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return result;
}

// Find in infinitely sorted array
int findInInfiniteArray(vector<int>& arr, int target) {
    // First find the range
    int left = 0, right = 1;
    
    while (arr[right] < target) {
        left = right;
        right *= 2;
    }
    
    // Now do binary search in this range
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

// Single element in sorted array (all others appear twice)
int singleNonDuplicate(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        // Ensure mid is even
        if (mid % 2 == 1) mid--;
        
        // Check pair
        if (arr[mid] == arr[mid + 1]) {
            // Pair is correct, single element is on right
            left = mid + 2;
        } else {
            // Pair is broken, single element is on left or at mid
            right = mid;
        }
    }
    
    return arr[left];
}

// Find smallest divisor given threshold
bool isValidDivisor(vector<int>& nums, int divisor, int threshold) {
    int sum = 0;
    
    for (int num : nums) {
        sum += (num + divisor - 1) / divisor;  // Ceiling division
        if (sum > threshold) return false;
    }
    
    return true;
}

int smallestDivisor(vector<int>& nums, int threshold) {
    int left = 1;
    int right = *max_element(nums.begin(), nums.end());
    int result = right;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (isValidDivisor(nums, mid, threshold)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return result;
}

int main() {
    // Next greatest letter
    vector<char> letters = {'c', 'f', 'j'};
    cout << "Letters: ";
    for (char c : letters) cout << c << " ";
    cout << "\nNext greatest letter after 'a': " << nextGreatestLetter(letters, 'a') << "\n\n";
    
    // K closest elements
    vector<int> arr1 = {1, 2, 3, 4, 5};
    vector<int> closest = findClosestElements(arr1, 4, 3);
    cout << "K closest elements to 3: ";
    for (int x : closest) cout << x << " ";
    cout << "\n\n";
    
    // Split array
    vector<int> nums = {7, 2, 5, 10, 8};
    cout << "Split array largest sum (m=2): " << splitArray(nums, 2) << "\n\n";
    
    // Ship packages
    vector<int> weights = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "Ship within days (5 days): " << shipWithinDays(weights, 5) << "\n\n";
    
    // Koko eating bananas
    vector<int> piles = {3, 6, 7, 11};
    cout << "Minimum eating speed (8 hours): " << minEatingSpeed(piles, 8) << "\n\n";
    
    // Single non-duplicate
    vector<int> arr2 = {1, 1, 2, 3, 3, 4, 4, 8, 8};
    cout << "Single non-duplicate: " << singleNonDuplicate(arr2) << "\n";
    
    return 0;
}



