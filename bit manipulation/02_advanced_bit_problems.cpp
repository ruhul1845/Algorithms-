/*
 * Bit Manipulation - Advanced Problems
 * Bit masking, subset generation, Gray code
 */

#include <bits/stdc++.h>
using namespace std;

// 1. Generate all subsets using bit masking
vector<vector<int>> generateSubsets(vector<int>& nums) {
    int n = nums.size();
    int totalSubsets = 1 << n; // 2^n
    vector<vector<int>> result;
    
    for (int mask = 0; mask < totalSubsets; mask++) {
        vector<int> subset;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                subset.push_back(nums[i]);
            }
        }
        result.push_back(subset);
    }
    
    return result;
}

// 2. Maximum XOR of Two Numbers
int findMaximumXOR(vector<int>& nums) {
    int maxXOR = 0;
    int mask = 0;
    
    for (int i = 31; i >= 0; i--) {
        mask |= (1 << i);
        set<int> prefixes;
        
        for (int num : nums) {
            prefixes.insert(num & mask);
        }
        
        int candidate = maxXOR | (1 << i);
        
        for (int prefix : prefixes) {
            if (prefixes.count(candidate ^ prefix)) {
                maxXOR = candidate;
                break;
            }
        }
    }
    
    return maxXOR;
}

// 3. Gray Code
vector<int> grayCode(int n) {
    vector<int> result;
    int size = 1 << n;
    
    for (int i = 0; i < size; i++) {
        result.push_back(i ^ (i >> 1));
    }
    
    return result;
}

// 4. Counting Bits (0 to n)
vector<int> countBits(int n) {
    vector<int> result(n + 1);
    
    for (int i = 1; i <= n; i++) {
        result[i] = result[i >> 1] + (i & 1);
    }
    
    return result;
}

// 5. Bitwise AND of Numbers Range
int rangeBitwiseAnd(int left, int right) {
    int shift = 0;
    
    while (left < right) {
        left >>= 1;
        right >>= 1;
        shift++;
    }
    
    return left << shift;
}

// 6. Maximum Product of Word Lengths
int maxProduct(vector<string>& words) {
    int n = words.size();
    vector<int> masks(n);
    
    // Create bitmask for each word
    for (int i = 0; i < n; i++) {
        for (char c : words[i]) {
            masks[i] |= (1 << (c - 'a'));
        }
    }
    
    int maxProd = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((masks[i] & masks[j]) == 0) {
                int prod = words[i].length() * words[j].length();
                maxProd = max(maxProd, prod);
            }
        }
    }
    
    return maxProd;
}

// 7. UTF-8 Validation
bool validUtf8(vector<int>& data) {
    int numBytes = 0;
    
    for (int byte : data) {
        if (numBytes == 0) {
            if ((byte >> 5) == 0b110) numBytes = 1;
            else if ((byte >> 4) == 0b1110) numBytes = 2;
            else if ((byte >> 3) == 0b11110) numBytes = 3;
            else if ((byte >> 7)) return false;
        } else {
            if ((byte >> 6) != 0b10) return false;
            numBytes--;
        }
    }
    
    return numBytes == 0;
}

// 8. Find Duplicate Number (Floyd's + Bit)
int findDuplicate(vector<int>& nums) {
    // Using bit manipulation
    int n = nums.size() - 1;
    int result = 0;
    
    for (int bit = 0; bit < 32; bit++) {
        int mask = 1 << bit;
        int baseCount = 0, arrayCount = 0;
        
        for (int i = 0; i <= n; i++) {
            if (i & mask) baseCount++;
            if (nums[i] & mask) arrayCount++;
        }
        
        if (arrayCount > baseCount) {
            result |= mask;
        }
    }
    
    return result;
}

// 9. Divide Two Integers (using bits)
int divide(int dividend, int divisor) {
    if (dividend == INT_MIN && divisor == -1) return INT_MAX;
    
    long long dvd = abs((long long)dividend);
    long long dvs = abs((long long)divisor);
    
    int sign = (dividend > 0) ^ (divisor > 0) ? -1 : 1;
    
    long long quotient = 0;
    
    while (dvd >= dvs) {
        long long temp = dvs, multiple = 1;
        
        while (dvd >= (temp << 1)) {
            temp <<= 1;
            multiple <<= 1;
        }
        
        dvd -= temp;
        quotient += multiple;
    }
    
    return sign * quotient;
}

// 10. Total Hamming Distance
int totalHammingDistance(vector<int>& nums) {
    int total = 0;
    int n = nums.size();
    
    for (int bit = 0; bit < 32; bit++) {
        int countOnes = 0;
        
        for (int num : nums) {
            if (num & (1 << bit)) {
                countOnes++;
            }
        }
        
        total += countOnes * (n - countOnes);
    }
    
    return total;
}

// 11. Concatenated Words (with bit DP)
bool canFormWord(string word, unordered_set<string>& dict, int start, vector<int>& memo) {
    if (start == word.length()) return true;
    if (memo[start] != -1) return memo[start];
    
    for (int end = start + 1; end <= word.length(); end++) {
        string sub = word.substr(start, end - start);
        if (dict.count(sub) && canFormWord(word, dict, end, memo)) {
            return memo[start] = 1;
        }
    }
    
    return memo[start] = 0;
}

// 12. Minimum Flips to Make OR Equal
int minFlips(int a, int b, int c) {
    int flips = 0;
    
    for (int i = 0; i < 32; i++) {
        int bitA = (a >> i) & 1;
        int bitB = (b >> i) & 1;
        int bitC = (c >> i) & 1;
        
        if (bitC == 0) {
            flips += bitA + bitB;
        } else {
            if (bitA == 0 && bitB == 0) {
                flips++;
            }
        }
    }
    
    return flips;
}

// 13. XOR Queries of Subarray
vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
    int n = arr.size();
    vector<int> prefix(n + 1, 0);
    
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] ^ arr[i];
    }
    
    vector<int> result;
    for (auto& query : queries) {
        int left = query[0], right = query[1];
        result.push_back(prefix[right + 1] ^ prefix[left]);
    }
    
    return result;
}

// 14. Power of Four
bool isPowerOfFour(int n) {
    // Must be power of 2 and set bit must be at odd position
    return n > 0 && (n & (n - 1)) == 0 && (n & 0x55555555) != 0;
}

// 15. Repeated DNA Sequences
vector<string> findRepeatedDnaSequences(string s) {
    if (s.length() <= 10) return {};
    
    unordered_map<char, int> mapping = {{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};
    unordered_map<int, int> seen;
    vector<string> result;
    
    int hash = 0;
    for (int i = 0; i < 10; i++) {
        hash = (hash << 2) | mapping[s[i]];
    }
    seen[hash] = 1;
    
    int mask = (1 << 20) - 1; // 20 bits for 10 characters
    
    for (int i = 10; i < s.length(); i++) {
        hash = ((hash << 2) & mask) | mapping[s[i]];
        
        if (seen[hash] == 1) {
            result.push_back(s.substr(i - 9, 10));
        }
        seen[hash]++;
    }
    
    return result;
}

int main() {
    // Test Generate Subsets
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> subsets = generateSubsets(nums);
    cout << "Total subsets: " << subsets.size() << endl;
    
    // Test Maximum XOR
    vector<int> nums2 = {3, 10, 5, 25, 2, 8};
    cout << "Maximum XOR: " << findMaximumXOR(nums2) << endl;
    
    // Test Gray Code
    vector<int> gray = grayCode(3);
    cout << "Gray code for n=3: ";
    for (int code : gray) cout << code << " ";
    cout << endl;
    
    // Test Counting Bits
    vector<int> bits = countBits(5);
    cout << "Count bits 0 to 5: ";
    for (int b : bits) cout << b << " ";
    cout << endl;
    
    // Test Power of Four
    cout << "Is 16 power of 4? " << (isPowerOfFour(16) ? "Yes" : "No") << endl;
    cout << "Is 8 power of 4? " << (isPowerOfFour(8) ? "Yes" : "No") << endl;
    
    return 0;
}










