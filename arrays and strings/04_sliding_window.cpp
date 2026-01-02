/*
 * Sliding Window Technique
 * Efficient solutions for subarray/substring problems
 * Time Complexity: O(n)
 */

#include <bits/stdc++.h>
using namespace std;

// 1. Maximum Sum Subarray of Size K
int maxSumSubarray(vector<int>& arr, int k) {
    int n = arr.size();
    if (n < k) return -1;
    
    int windowSum = 0;
    for (int i = 0; i < k; i++) {
        windowSum += arr[i];
    }
    
    int maxSum = windowSum;
    for (int i = k; i < n; i++) {
        windowSum += arr[i] - arr[i - k];
        maxSum = max(maxSum, windowSum);
    }
    return maxSum;
}

// 2. Longest Substring Without Repeating Characters
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> charIndex;
    int maxLen = 0, start = 0;
    
    for (int end = 0; end < s.length(); end++) {
        if (charIndex.find(s[end]) != charIndex.end()) {
            start = max(start, charIndex[s[end]] + 1);
        }
        charIndex[s[end]] = end;
        maxLen = max(maxLen, end - start + 1);
    }
    return maxLen;
}

// 3. Minimum Window Substring
string minWindow(string s, string t) {
    if (s.empty() || t.empty()) return "";
    
    unordered_map<char, int> required, window;
    for (char c : t) required[c]++;
    
    int left = 0, right = 0;
    int formed = 0, requiredCount = required.size();
    int minLen = INT_MAX, minLeft = 0;
    
    while (right < s.length()) {
        char c = s[right];
        window[c]++;
        
        if (required.count(c) && window[c] == required[c]) {
            formed++;
        }
        
        while (left <= right && formed == requiredCount) {
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                minLeft = left;
            }
            
            char leftChar = s[left];
            window[leftChar]--;
            if (required.count(leftChar) && window[leftChar] < required[leftChar]) {
                formed--;
            }
            left++;
        }
        right++;
    }
    
    return minLen == INT_MAX ? "" : s.substr(minLeft, minLen);
}

// 4. Longest Substring with At Most K Distinct Characters
int lengthOfLongestSubstringKDistinct(string s, int k) {
    unordered_map<char, int> charCount;
    int left = 0, maxLen = 0;
    
    for (int right = 0; right < s.length(); right++) {
        charCount[s[right]]++;
        
        while (charCount.size() > k) {
            charCount[s[left]]--;
            if (charCount[s[left]] == 0) {
                charCount.erase(s[left]);
            }
            left++;
        }
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}

// 5. Find All Anagrams in String
vector<int> findAnagrams(string s, string p) {
    vector<int> result;
    if (s.length() < p.length()) return result;
    
    vector<int> pCount(26, 0), sCount(26, 0);
    for (char c : p) pCount[c - 'a']++;
    
    for (int i = 0; i < s.length(); i++) {
        sCount[s[i] - 'a']++;
        
        if (i >= p.length()) {
            sCount[s[i - p.length()] - 'a']--;
        }
        
        if (i >= p.length() - 1 && sCount == pCount) {
            result.push_back(i - p.length() + 1);
        }
    }
    return result;
}

// 6. Maximum of All Subarrays of Size K
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> result;
    
    for (int i = 0; i < nums.size(); i++) {
        // Remove elements outside window
        if (!dq.empty() && dq.front() == i - k) {
            dq.pop_front();
        }
        
        // Remove smaller elements from back
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    return result;
}

// 7. Subarray Product Less Than K
int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    if (k <= 1) return 0;
    
    int count = 0, product = 1;
    int left = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        product *= nums[right];
        
        while (product >= k) {
            product /= nums[left];
            left++;
        }
        
        count += right - left + 1;
    }
    return count;
}

// 8. Minimum Size Subarray Sum
int minSubArrayLen(int target, vector<int>& nums) {
    int left = 0, sum = 0;
    int minLen = INT_MAX;
    
    for (int right = 0; right < nums.size(); right++) {
        sum += nums[right];
        
        while (sum >= target) {
            minLen = min(minLen, right - left + 1);
            sum -= nums[left];
            left++;
        }
    }
    return minLen == INT_MAX ? 0 : minLen;
}

int main() {
    // Test Maximum Sum Subarray
    vector<int> arr = {2, 1, 5, 1, 3, 2};
    cout << "Max sum of size 3: " << maxSumSubarray(arr, 3) << endl;
    
    // Test Longest Substring Without Repeating
    string s = "abcabcbb";
    cout << "Longest substring without repeating: " << lengthOfLongestSubstring(s) << endl;
    
    // Test Maximum Sliding Window
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> maxWindow = maxSlidingWindow(nums, 3);
    cout << "Max sliding window: ";
    for (int x : maxWindow) cout << x << " ";
    cout << endl;
    
    return 0;
}

