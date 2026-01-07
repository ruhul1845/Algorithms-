/*
 * Hash Table - Basic Operations and Implementation
 * Hash functions, collision handling, basic operations
 */

#include <bits/stdc++.h>
using namespace std;

// 1. Simple Hash Map using Chaining
class HashMap {
    static const int SIZE = 100;
    vector<list<pair<int, int>>> table;
    
    int hashFunction(int key) {
        return key % SIZE;
    }
    
public:
    HashMap() {
        table.resize(SIZE);
    }
    
    void put(int key, int value) {
        int hash = hashFunction(key);
        
        for (auto& pair : table[hash]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        
        table[hash].push_back({key, value});
    }
    
    int get(int key) {
        int hash = hashFunction(key);
        
        for (auto& pair : table[hash]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        
        return -1;
    }
    
    void remove(int key) {
        int hash = hashFunction(key);
        
        table[hash].remove_if([key](const pair<int, int>& p) {
            return p.first == key;
        });
    }
    
    bool contains(int key) {
        return get(key) != -1;
    }
};

// 2. Hash Set Implementation
class HashSet {
    static const int SIZE = 1000;
    vector<list<int>> buckets;
    
    int hashFunction(int key) {
        return key % SIZE;
    }
    
public:
    HashSet() {
        buckets.resize(SIZE);
    }
    
    void add(int key) {
        int hash = hashFunction(key);
        
        for (int val : buckets[hash]) {
            if (val == key) return;
        }
        
        buckets[hash].push_back(key);
    }
    
    void remove(int key) {
        int hash = hashFunction(key);
        buckets[hash].remove(key);
    }
    
    bool contains(int key) {
        int hash = hashFunction(key);
        
        for (int val : buckets[hash]) {
            if (val == key) return true;
        }
        
        return false;
    }
};

// 3. Two Sum Problem
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> map;
    
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        
        if (map.find(complement) != map.end()) {
            return {map[complement], i};
        }
        
        map[nums[i]] = i;
    }
    
    return {};
}

// 4. Group Anagrams
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> map;
    
    for (string& s : strs) {
        string key = s;
        sort(key.begin(), key.end());
        map[key].push_back(s);
    }
    
    vector<vector<string>> result;
    for (auto& pair : map) {
        result.push_back(pair.second);
    }
    
    return result;
}

// 5. Contains Duplicate
bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> seen;
    
    for (int num : nums) {
        if (seen.count(num)) return true;
        seen.insert(num);
    }
    
    return false;
}

// 6. First Unique Character
int firstUniqChar(string s) {
    unordered_map<char, int> freq;
    
    for (char c : s) {
        freq[c]++;
    }
    
    for (int i = 0; i < s.length(); i++) {
        if (freq[s[i]] == 1) return i;
    }
    
    return -1;
}

// 7. Isomorphic Strings
bool isIsomorphic(string s, string t) {
    if (s.length() != t.length()) return false;
    
    unordered_map<char, char> mapS, mapT;
    
    for (int i = 0; i < s.length(); i++) {
        char c1 = s[i], c2 = t[i];
        
        if (mapS.count(c1) && mapS[c1] != c2) return false;
        if (mapT.count(c2) && mapT[c2] != c1) return false;
        
        mapS[c1] = c2;
        mapT[c2] = c1;
    }
    
    return true;
}

// 8. Word Pattern
bool wordPattern(string pattern, string s) {
    vector<string> words;
    stringstream ss(s);
    string word;
    
    while (ss >> word) {
        words.push_back(word);
    }
    
    if (pattern.length() != words.size()) return false;
    
    unordered_map<char, string> charToWord;
    unordered_map<string, char> wordToChar;
    
    for (int i = 0; i < pattern.length(); i++) {
        char c = pattern[i];
        string w = words[i];
        
        if (charToWord.count(c) && charToWord[c] != w) return false;
        if (wordToChar.count(w) && wordToChar[w] != c) return false;
        
        charToWord[c] = w;
        wordToChar[w] = c;
    }
    
    return true;
}

// 9. Happy Number
bool isHappy(int n) {
    unordered_set<int> seen;
    
    while (n != 1 && !seen.count(n)) {
        seen.insert(n);
        int sum = 0;
        
        while (n > 0) {
            int digit = n % 10;
            sum += digit * digit;
            n /= 10;
        }
        
        n = sum;
    }
    
    return n == 1;
}

// 10. Longest Consecutive Sequence
int longestConsecutive(vector<int>& nums) {
    unordered_set<int> numSet(nums.begin(), nums.end());
    int maxLen = 0;
    
    for (int num : nums) {
        if (!numSet.count(num - 1)) {
            int currentNum = num;
            int currentLen = 1;
            
            while (numSet.count(currentNum + 1)) {
                currentNum++;
                currentLen++;
            }
            
            maxLen = max(maxLen, currentLen);
        }
    }
    
    return maxLen;
}

int main() {
    // Test HashMap
    HashMap map;
    map.put(1, 100);
    map.put(2, 200);
    map.put(3, 300);
    
    cout << "Get key 2: " << map.get(2) << endl;
    cout << "Contains key 3: " << (map.contains(3) ? "Yes" : "No") << endl;
    
    // Test Two Sum
    vector<int> nums = {2, 7, 11, 15};
    vector<int> result = twoSum(nums, 9);
    cout << "Two Sum indices: " << result[0] << ", " << result[1] << endl;
    
    // Test Group Anagrams
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> groups = groupAnagrams(strs);
    cout << "Anagram groups: " << groups.size() << endl;
    
    // Test Longest Consecutive
    vector<int> nums2 = {100, 4, 200, 1, 3, 2};
    cout << "Longest consecutive: " << longestConsecutive(nums2) << endl;
    
    return 0;
}










