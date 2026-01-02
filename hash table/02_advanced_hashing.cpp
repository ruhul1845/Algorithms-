/*
 * Advanced Hashing Problems
 * Substring problems, frequency counting, pattern matching
 */

#include <bits/stdc++.h>
using namespace std;

// 1. Subarray Sum Equals K
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefixSum;
    prefixSum[0] = 1;
    int sum = 0, count = 0;
    
    for (int num : nums) {
        sum += num;
        if (prefixSum.count(sum - k)) {
            count += prefixSum[sum - k];
        }
        prefixSum[sum]++;
    }
    
    return count;
}

// 2. Longest Substring Without Repeating Characters
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> lastIndex;
    int maxLen = 0, start = 0;
    
    for (int end = 0; end < s.length(); end++) {
        if (lastIndex.count(s[end])) {
            start = max(start, lastIndex[s[end]] + 1);
        }
        
        lastIndex[s[end]] = end;
        maxLen = max(maxLen, end - start + 1);
    }
    
    return maxLen;
}

// 3. Top K Frequent Elements
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for (int num : nums) {
        freq[num]++;
    }
    
    auto comp = [](pair<int, int>& a, pair<int, int>& b) {
        return a.second > b.second;
    };
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> pq(comp);
    
    for (auto& p : freq) {
        pq.push(p);
        if (pq.size() > k) {
            pq.pop();
        }
    }
    
    vector<int> result;
    while (!pq.empty()) {
        result.push_back(pq.top().first);
        pq.pop();
    }
    
    return result;
}

// 4. Find All Anagrams in String
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

// 5. Minimum Window Substring
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

// 6. Four Sum II
int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
    unordered_map<int, int> map;
    
    for (int a : nums1) {
        for (int b : nums2) {
            map[a + b]++;
        }
    }
    
    int count = 0;
    for (int c : nums3) {
        for (int d : nums4) {
            if (map.count(-(c + d))) {
                count += map[-(c + d)];
            }
        }
    }
    
    return count;
}

// 7. Logger Rate Limiter
class Logger {
    unordered_map<string, int> messageTime;
    
public:
    bool shouldPrintMessage(int timestamp, string message) {
        if (!messageTime.count(message) || timestamp - messageTime[message] >= 10) {
            messageTime[message] = timestamp;
            return true;
        }
        return false;
    }
};

// 8. Valid Sudoku
bool isValidSudoku(vector<vector<char>>& board) {
    unordered_set<string> seen;
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] != '.') {
                string num = string(1, board[i][j]);
                
                if (!seen.insert(num + " in row " + to_string(i)).second ||
                    !seen.insert(num + " in col " + to_string(j)).second ||
                    !seen.insert(num + " in box " + to_string(i/3) + "-" + to_string(j/3)).second) {
                    return false;
                }
            }
        }
    }
    
    return true;
}

// 9. Fraction to Recurring Decimal
string fractionToDecimal(int numerator, int denominator) {
    if (numerator == 0) return "0";
    
    string result = "";
    
    if ((numerator < 0) ^ (denominator < 0)) {
        result += "-";
    }
    
    long long num = abs((long long)numerator);
    long long den = abs((long long)denominator);
    
    result += to_string(num / den);
    long long remainder = num % den;
    
    if (remainder == 0) return result;
    
    result += ".";
    unordered_map<long long, int> remainderPos;
    
    while (remainder != 0) {
        if (remainderPos.count(remainder)) {
            result.insert(remainderPos[remainder], "(");
            result += ")";
            break;
        }
        
        remainderPos[remainder] = result.length();
        remainder *= 10;
        result += to_string(remainder / den);
        remainder %= den;
    }
    
    return result;
}

// 10. Random Pick with Blacklist
class RandomPickBlacklist {
    int M;
    unordered_map<int, int> remap;
    
public:
    RandomPickBlacklist(int n, vector<int>& blacklist) {
        M = n - blacklist.size();
        unordered_set<int> blackSet(blacklist.begin(), blacklist.end());
        
        int last = n - 1;
        for (int b : blacklist) {
            if (b < M) {
                while (blackSet.count(last)) {
                    last--;
                }
                remap[b] = last;
                last--;
            }
        }
    }
    
    int pick() {
        int p = rand() % M;
        return remap.count(p) ? remap[p] : p;
    }
};

int main() {
    // Test Subarray Sum
    vector<int> nums1 = {1, 1, 1};
    cout << "Subarrays with sum 2: " << subarraySum(nums1, 2) << endl;
    
    // Test Longest Substring
    cout << "Longest substring without repeat in 'abcabcbb': " 
         << lengthOfLongestSubstring("abcabcbb") << endl;
    
    // Test Top K Frequent
    vector<int> nums2 = {1, 1, 1, 2, 2, 3};
    vector<int> topK = topKFrequent(nums2, 2);
    cout << "Top 2 frequent: ";
    for (int x : topK) cout << x << " ";
    cout << endl;
    
    // Test Minimum Window
    cout << "Min window of 'ADOBECODEBANC' for 'ABC': " 
         << minWindow("ADOBECODEBANC", "ABC") << endl;
    
    return 0;
}

