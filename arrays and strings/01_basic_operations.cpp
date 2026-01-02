/*
 * Arrays and Strings - Basic Operations
 * Essential array and string manipulation techniques
 * Time Complexity: O(n) for most operations
 */

#include <bits/stdc++.h>
using namespace std;

// 1. Array Reversal
void reverseArray(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    while (left < right) {
        swap(arr[left], arr[right]);
        left++;
        right--;
    }
}

// 2. Find Maximum and Minimum
pair<int, int> findMinMax(vector<int>& arr) {
    int minVal = INT_MAX, maxVal = INT_MIN;
    for (int num : arr) {
        minVal = min(minVal, num);
        maxVal = max(maxVal, num);
    }
    return {minVal, maxVal};
}

// 3. Rotate Array by K positions
void rotateArray(vector<int>& arr, int k) {
    int n = arr.size();
    k = k % n;
    reverse(arr.begin(), arr.end());
    reverse(arr.begin(), arr.begin() + k);
    reverse(arr.begin() + k, arr.end());
}

// 4. Remove Duplicates from Sorted Array
int removeDuplicates(vector<int>& arr) {
    if (arr.empty()) return 0;
    int j = 0;
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] != arr[j]) {
            j++;
            arr[j] = arr[i];
        }
    }
    return j + 1;
}

// 5. String Reversal
void reverseString(string& s) {
    int left = 0, right = s.length() - 1;
    while (left < right) {
        swap(s[left], s[right]);
        left++;
        right--;
    }
}

// 6. Check Palindrome
bool isPalindrome(string s) {
    int left = 0, right = s.length() - 1;
    while (left < right) {
        if (s[left] != s[right]) return false;
        left++;
        right--;
    }
    return true;
}

// 7. Reverse Words in String
string reverseWords(string s) {
    reverse(s.begin(), s.end());
    int n = s.length();
    int i = 0;
    
    for (int j = 0; j <= n; j++) {
        if (j == n || s[j] == ' ') {
            reverse(s.begin() + i, s.begin() + j);
            i = j + 1;
        }
    }
    return s;
}

// 8. Anagram Check
bool isAnagram(string s1, string s2) {
    if (s1.length() != s2.length()) return false;
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    return s1 == s2;
}

// 9. First Non-Repeating Character
char firstNonRepeating(string s) {
    unordered_map<char, int> freq;
    for (char c : s) freq[c]++;
    
    for (char c : s) {
        if (freq[c] == 1) return c;
    }
    return '\0';
}

// 10. Longest Common Prefix
string longestCommonPrefix(vector<string>& strs) {
    if (strs.empty()) return "";
    
    string prefix = strs[0];
    for (int i = 1; i < strs.size(); i++) {
        while (strs[i].find(prefix) != 0) {
            prefix = prefix.substr(0, prefix.length() - 1);
            if (prefix.empty()) return "";
        }
    }
    return prefix;
}

int main() {
    // Test Array Operations
    vector<int> arr = {1, 2, 3, 4, 5};
    cout << "Original Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    reverseArray(arr);
    cout << "Reversed Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    // Test String Operations
    string s = "hello";
    cout << "\nOriginal String: " << s << endl;
    reverseString(s);
    cout << "Reversed String: " << s << endl;
    
    cout << "Is 'racecar' palindrome? " << (isPalindrome("racecar") ? "Yes" : "No") << endl;
    
    return 0;
}

