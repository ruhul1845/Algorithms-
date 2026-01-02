#include <bits/stdc++.h>
using namespace std;

/*
 * TERNARY SEARCH
 * Used to find maximum/minimum of unimodal functions
 * Time Complexity: O(log3 n)
 * Space Complexity: O(1)
 */

// Ternary search on sorted array (similar to binary search)
int ternarySearch(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while (left <= right) {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;
        
        if (arr[mid1] == target) return mid1;
        if (arr[mid2] == target) return mid2;
        
        if (target < arr[mid1]) {
            right = mid1 - 1;
        } else if (target > arr[mid2]) {
            left = mid2 + 1;
        } else {
            left = mid1 + 1;
            right = mid2 - 1;
        }
    }
    
    return -1;
}

// Recursive ternary search
int ternarySearchRecursive(vector<int>& arr, int left, int right, int target) {
    if (left > right) return -1;
    
    int mid1 = left + (right - left) / 3;
    int mid2 = right - (right - left) / 3;
    
    if (arr[mid1] == target) return mid1;
    if (arr[mid2] == target) return mid2;
    
    if (target < arr[mid1]) {
        return ternarySearchRecursive(arr, left, mid1 - 1, target);
    } else if (target > arr[mid2]) {
        return ternarySearchRecursive(arr, mid2 + 1, right, target);
    } else {
        return ternarySearchRecursive(arr, mid1 + 1, mid2 - 1, target);
    }
}

// Find maximum in unimodal array (first increases then decreases)
int findMaximum(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    
    while (right - left > 2) {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;
        
        if (arr[mid1] < arr[mid2]) {
            left = mid1;
        } else {
            right = mid2;
        }
    }
    
    // Check remaining elements
    int maxVal = arr[left];
    for (int i = left + 1; i <= right; i++) {
        maxVal = max(maxVal, arr[i]);
    }
    
    return maxVal;
}

// Find minimum of unimodal function (parabola opening upwards)
double findMinimumFunction(double left, double right, 
                          function<double(double)> func, 
                          double epsilon = 1e-6) {
    while (right - left > epsilon) {
        double mid1 = left + (right - left) / 3;
        double mid2 = right - (right - left) / 3;
        
        if (func(mid1) > func(mid2)) {
            left = mid1;
        } else {
            right = mid2;
        }
    }
    
    return (left + right) / 2;
}

// Find maximum of unimodal function
double findMaximumFunction(double left, double right, 
                          function<double(double)> func, 
                          double epsilon = 1e-6) {
    while (right - left > epsilon) {
        double mid1 = left + (right - left) / 3;
        double mid2 = right - (right - left) / 3;
        
        if (func(mid1) < func(mid2)) {
            left = mid1;
        } else {
            right = mid2;
        }
    }
    
    return (left + right) / 2;
}

// Minimize maximum distance to gas station
bool canPlaceStations(vector<int>& stations, int k, double dist) {
    int count = 0;
    
    for (int i = 1; i < stations.size(); i++) {
        count += (int)((stations[i] - stations[i-1]) / dist);
        if (count > k) return false;
    }
    
    return true;
}

double minmaxGasDist(vector<int>& stations, int k) {
    double left = 0;
    double right = stations.back() - stations[0];
    double epsilon = 1e-6;
    
    while (right - left > epsilon) {
        double mid = left + (right - left) / 2;
        
        if (canPlaceStations(stations, k, mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    
    return left;
}

// Find minimum speed to arrive on time
double minSpeedOnTime(vector<int>& dist, double hour) {
    double left = 1, right = 1e7;
    double epsilon = 1e-5;
    
    auto canReach = [&](double speed) {
        double time = 0;
        for (int i = 0; i < dist.size() - 1; i++) {
            time += ceil(dist[i] / speed);
        }
        time += dist.back() / speed;
        return time <= hour;
    };
    
    while (right - left > epsilon) {
        double mid = left + (right - left) / 2;
        
        if (canReach(mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    
    return left;
}

// Magnetic force between two balls
bool canPlaceBalls(vector<int>& position, int m, int minDist) {
    int count = 1;
    int lastPos = position[0];
    
    for (int i = 1; i < position.size(); i++) {
        if (position[i] - lastPos >= minDist) {
            count++;
            lastPos = position[i];
            if (count >= m) return true;
        }
    }
    
    return false;
}

int maxDistance(vector<int>& position, int m) {
    sort(position.begin(), position.end());
    
    int left = 1;
    int right = position.back() - position[0];
    int result = 0;
    
    while (left <= right) {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;
        
        bool can1 = canPlaceBalls(position, m, mid1);
        bool can2 = canPlaceBalls(position, m, mid2);
        
        if (can1 && can2) {
            result = mid2;
            left = mid2 + 1;
        } else if (can1) {
            result = mid1;
            left = mid1 + 1;
            right = mid2 - 1;
        } else {
            right = mid1 - 1;
        }
    }
    
    return result;
}

// Find nth root using ternary search
double nthRoot(double x, int n) {
    if (x == 0 || x == 1) return x;
    
    double left = 0, right = x;
    if (x < 1) right = 1;
    
    double epsilon = 1e-6;
    
    while (right - left > epsilon) {
        double mid = left + (right - left) / 2;
        double value = pow(mid, n);
        
        if (abs(value - x) < epsilon) {
            return mid;
        } else if (value < x) {
            left = mid;
        } else {
            right = mid;
        }
    }
    
    return (left + right) / 2;
}

int main() {
    // Ternary search in array
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int target = 7;
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nTernary search for " << target << ": " << ternarySearch(arr, target) << "\n\n";
    
    // Find maximum in unimodal array
    vector<int> unimodal = {1, 3, 5, 7, 9, 11, 10, 8, 6, 4, 2};
    cout << "Unimodal array: ";
    for (int x : unimodal) cout << x << " ";
    cout << "\nMaximum value: " << findMaximum(unimodal) << "\n\n";
    
    // Find minimum of function f(x) = x^2 - 4x + 7
    auto func1 = [](double x) { return x * x - 4 * x + 7; };
    double minX = findMinimumFunction(0, 10, func1);
    cout << "Minimum of f(x) = x^2 - 4x + 7 at x = " << minX << "\n";
    cout << "f(" << minX << ") = " << func1(minX) << "\n\n";
    
    // Find maximum of function f(x) = -(x-3)^2 + 5
    auto func2 = [](double x) { return -(x - 3) * (x - 3) + 5; };
    double maxX = findMaximumFunction(0, 10, func2);
    cout << "Maximum of f(x) = -(x-3)^2 + 5 at x = " << maxX << "\n";
    cout << "f(" << maxX << ") = " << func2(maxX) << "\n\n";
    
    // Nth root
    double num = 27;
    int n = 3;
    cout << n << "th root of " << num << " = " << nthRoot(num, n) << "\n";
    
    return 0;
}



