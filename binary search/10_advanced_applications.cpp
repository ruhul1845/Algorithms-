#include <bits/stdc++.h>
using namespace std;

/*
 * ADVANCED BINARY SEARCH APPLICATIONS
 * Complex problems solved using binary search
 */

// Maximum value at a given index in bounded array
int maxValue(int n, int index, int maxSum) {
    auto getSum = [&](long long value) -> long long {
        long long sum = 0;
        
        // Left side
        if (value > index) {
            sum += (value + value - index) * (index + 1) / 2;
        } else {
            sum += (value + 1) * value / 2 + (index + 1 - value);
        }
        
        // Right side
        int right = n - index - 1;
        if (value > right) {
            sum += (value + value - right) * (right + 1) / 2;
        } else {
            sum += (value + 1) * value / 2 + (right + 1 - value);
        }
        
        return sum - value;  // Remove double counting of arr[index]
    };
    
    long long left = 1, right = maxSum;
    long long result = 1;
    
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        
        if (getSum(mid) <= maxSum) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// Minimize max distance to gas station
double minmaxGasDist(vector<int>& stations, int k) {
    double left = 0;
    double right = stations.back() - stations[0];
    double epsilon = 1e-6;
    
    auto canPlace = [&](double dist) {
        int count = 0;
        for (int i = 1; i < stations.size(); i++) {
            count += (int)((stations[i] - stations[i-1]) / dist);
            if (count > k) return false;
        }
        return true;
    };
    
    while (right - left > epsilon) {
        double mid = left + (right - left) / 2;
        
        if (canPlace(mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    
    return left;
}

// Maximum sum of k non-overlapping subarrays
int maxSumKSubarrays(vector<int>& nums, int k) {
    int n = nums.size();
    vector<vector<int>> dp(k + 1, vector<int>(n + 1, INT_MIN / 2));
    dp[0][0] = 0;
    
    for (int i = 1; i <= k; i++) {
        for (int j = i; j <= n; j++) {
            dp[i][j] = dp[i][j-1];
            int sum = 0;
            for (int p = j; p >= i; p--) {
                sum += nums[p-1];
                dp[i][j] = max(dp[i][j], dp[i-1][p-1] + sum);
            }
        }
    }
    
    return dp[k][n];
}

// Find k-th smallest pair distance
int kthSmallestPairDistance(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    
    int left = 0;
    int right = nums.back() - nums[0];
    
    auto countPairs = [&](int mid) {
        int count = 0;
        int j = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            while (j < nums.size() && nums[j] - nums[i] <= mid) {
                j++;
            }
            count += j - i - 1;
        }
        
        return count;
    };
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (countPairs(mid) < k) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}

// Shortest subarray with sum at least K
int shortestSubarray(vector<int>& nums, int k) {
    int n = nums.size();
    vector<long long> prefix(n + 1, 0);
    
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + nums[i];
    }
    
    int result = n + 1;
    deque<int> dq;
    
    for (int i = 0; i <= n; i++) {
        while (!dq.empty() && prefix[i] - prefix[dq.front()] >= k) {
            result = min(result, i - dq.front());
            dq.pop_front();
        }
        
        while (!dq.empty() && prefix[i] <= prefix[dq.back()]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
    }
    
    return result <= n ? result : -1;
}

// Maximum frequency stack element
class FreqStack {
private:
    unordered_map<int, int> freq;
    unordered_map<int, stack<int>> group;
    int maxFreq;
    
public:
    FreqStack() : maxFreq(0) {}
    
    void push(int val) {
        freq[val]++;
        maxFreq = max(maxFreq, freq[val]);
        group[freq[val]].push(val);
    }
    
    int pop() {
        int val = group[maxFreq].top();
        group[maxFreq].pop();
        freq[val]--;
        
        if (group[maxFreq].empty()) {
            maxFreq--;
        }
        
        return val;
    }
};

// Longest increasing subsequence using binary search
int lengthOfLIS(vector<int>& nums) {
    vector<int> dp;
    
    for (int num : nums) {
        auto it = lower_bound(dp.begin(), dp.end(), num);
        
        if (it == dp.end()) {
            dp.push_back(num);
        } else {
            *it = num;
        }
    }
    
    return dp.size();
}

// Russian doll envelopes (2D LIS)
int maxEnvelopes(vector<vector<int>>& envelopes) {
    sort(envelopes.begin(), envelopes.end(), [](auto& a, auto& b) {
        return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
    });
    
    vector<int> dp;
    
    for (auto& env : envelopes) {
        int h = env[1];
        auto it = lower_bound(dp.begin(), dp.end(), h);
        
        if (it == dp.end()) {
            dp.push_back(h);
        } else {
            *it = h;
        }
    }
    
    return dp.size();
}

// Find kth missing positive number
int findKthPositive(vector<int>& arr, int k) {
    int left = 0, right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int missing = arr[mid] - (mid + 1);
        
        if (missing < k) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return left + k;
}

// Maximum tastiness of candy basket
int maximumTastiness(vector<int>& price, int k) {
    sort(price.begin(), price.end());
    
    auto canSelect = [&](int minDiff) {
        int count = 1;
        int lastPrice = price[0];
        
        for (int i = 1; i < price.size(); i++) {
            if (price[i] - lastPrice >= minDiff) {
                count++;
                lastPrice = price[i];
                if (count >= k) return true;
            }
        }
        
        return false;
    };
    
    int left = 0;
    int right = price.back() - price[0];
    int result = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (canSelect(mid)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// Divide chocolate with minimum sweetness
int maximizeSweetness(vector<int>& sweetness, int k) {
    int left = *min_element(sweetness.begin(), sweetness.end());
    int right = accumulate(sweetness.begin(), sweetness.end(), 0);
    
    auto canDivide = [&](int minSweet) {
        int pieces = 0;
        int currentSweet = 0;
        
        for (int s : sweetness) {
            currentSweet += s;
            if (currentSweet >= minSweet) {
                pieces++;
                currentSweet = 0;
            }
        }
        
        return pieces >= k + 1;
    };
    
    int result = left;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (canDivide(mid)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

int main() {
    // Maximum value at index
    cout << "Maximum value at index (n=4, index=2, maxSum=6): " 
         << maxValue(4, 2, 6) << "\n\n";
    
    // Kth smallest pair distance
    vector<int> nums1 = {1, 3, 1};
    cout << "Kth smallest pair distance (k=1): " 
         << kthSmallestPairDistance(nums1, 1) << "\n\n";
    
    // Longest increasing subsequence
    vector<int> nums2 = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "LIS: ";
    for (int x : nums2) cout << x << " ";
    cout << "\nLength: " << lengthOfLIS(nums2) << "\n\n";
    
    // Find kth missing positive
    vector<int> arr = {2, 3, 4, 7, 11};
    int k = 5;
    cout << "Kth missing positive (k=" << k << "): " 
         << findKthPositive(arr, k) << "\n\n";
    
    // Frequency stack demo
    FreqStack freqStack;
    freqStack.push(5);
    freqStack.push(7);
    freqStack.push(5);
    freqStack.push(7);
    freqStack.push(4);
    freqStack.push(5);
    
    cout << "FreqStack operations:\n";
    cout << "Pop: " << freqStack.pop() << " (expected 5)\n";
    cout << "Pop: " << freqStack.pop() << " (expected 7)\n";
    cout << "Pop: " << freqStack.pop() << " (expected 5)\n";
    cout << "Pop: " << freqStack.pop() << " (expected 4)\n\n";
    
    // Russian doll envelopes
    vector<vector<int>> envelopes = {{5,4},{6,4},{6,7},{2,3}};
    cout << "Maximum nested envelopes: " << maxEnvelopes(envelopes) << "\n";
    
    return 0;
}



