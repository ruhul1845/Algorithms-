/*
 * Backtracking - Basic Problems
 * Permutations, combinations, subsets
 */

#include <bits/stdc++.h>
using namespace std;

// 1. Subsets (Power Set)
void subsetsHelper(vector<int>& nums, int idx, vector<int>& current, vector<vector<int>>& result) {
    result.push_back(current);
    
    for (int i = idx; i < nums.size(); i++) {
        current.push_back(nums[i]);
        subsetsHelper(nums, i + 1, current, result);
        current.pop_back();
    }
}

vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> current;
    subsetsHelper(nums, 0, current, result);
    return result;
}

// 2. Subsets II (With Duplicates)
void subsetsWithDupHelper(vector<int>& nums, int idx, vector<int>& current, vector<vector<int>>& result) {
    result.push_back(current);
    
    for (int i = idx; i < nums.size(); i++) {
        if (i > idx && nums[i] == nums[i-1]) continue;
        
        current.push_back(nums[i]);
        subsetsWithDupHelper(nums, i + 1, current, result);
        current.pop_back();
    }
}

vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    vector<int> current;
    subsetsWithDupHelper(nums, 0, current, result);
    return result;
}

// 3. Permutations
void permuteHelper(vector<int>& nums, int idx, vector<vector<int>>& result) {
    if (idx == nums.size()) {
        result.push_back(nums);
        return;
    }
    
    for (int i = idx; i < nums.size(); i++) {
        swap(nums[idx], nums[i]);
        permuteHelper(nums, idx + 1, result);
        swap(nums[idx], nums[i]);
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> result;
    permuteHelper(nums, 0, result);
    return result;
}

// 4. Permutations II (With Duplicates)
void permuteUniqueHelper(vector<int>& nums, vector<bool>& used, vector<int>& current, vector<vector<int>>& result) {
    if (current.size() == nums.size()) {
        result.push_back(current);
        return;
    }
    
    for (int i = 0; i < nums.size(); i++) {
        if (used[i]) continue;
        if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;
        
        used[i] = true;
        current.push_back(nums[i]);
        permuteUniqueHelper(nums, used, current, result);
        current.pop_back();
        used[i] = false;
    }
}

vector<vector<int>> permuteUnique(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    vector<int> current;
    vector<bool> used(nums.size(), false);
    permuteUniqueHelper(nums, used, current, result);
    return result;
}

// 5. Combinations
void combineHelper(int n, int k, int start, vector<int>& current, vector<vector<int>>& result) {
    if (current.size() == k) {
        result.push_back(current);
        return;
    }
    
    for (int i = start; i <= n; i++) {
        current.push_back(i);
        combineHelper(n, k, i + 1, current, result);
        current.pop_back();
    }
}

vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> result;
    vector<int> current;
    combineHelper(n, k, 1, current, result);
    return result;
}

// 6. Combination Sum
void combinationSumHelper(vector<int>& candidates, int target, int idx, vector<int>& current, vector<vector<int>>& result) {
    if (target == 0) {
        result.push_back(current);
        return;
    }
    
    if (target < 0) return;
    
    for (int i = idx; i < candidates.size(); i++) {
        current.push_back(candidates[i]);
        combinationSumHelper(candidates, target - candidates[i], i, current, result);
        current.pop_back();
    }
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> result;
    vector<int> current;
    combinationSumHelper(candidates, target, 0, current, result);
    return result;
}

// 7. Combination Sum II (No Reuse)
void combinationSum2Helper(vector<int>& candidates, int target, int idx, vector<int>& current, vector<vector<int>>& result) {
    if (target == 0) {
        result.push_back(current);
        return;
    }
    
    for (int i = idx; i < candidates.size(); i++) {
        if (i > idx && candidates[i] == candidates[i-1]) continue;
        if (candidates[i] > target) break;
        
        current.push_back(candidates[i]);
        combinationSum2Helper(candidates, target - candidates[i], i + 1, current, result);
        current.pop_back();
    }
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> result;
    vector<int> current;
    combinationSum2Helper(candidates, target, 0, current, result);
    return result;
}

// 8. Letter Combinations of Phone Number
void letterCombinationsHelper(string& digits, int idx, vector<string>& map, string& current, vector<string>& result) {
    if (idx == digits.length()) {
        result.push_back(current);
        return;
    }
    
    string letters = map[digits[idx] - '0'];
    for (char c : letters) {
        current.push_back(c);
        letterCombinationsHelper(digits, idx + 1, map, current, result);
        current.pop_back();
    }
}

vector<string> letterCombinations(string digits) {
    if (digits.empty()) return {};
    
    vector<string> map = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> result;
    string current;
    letterCombinationsHelper(digits, 0, map, current, result);
    return result;
}

// 9. Generate Parentheses
void generateParenthesisHelper(int n, int open, int close, string current, vector<string>& result) {
    if (current.length() == 2 * n) {
        result.push_back(current);
        return;
    }
    
    if (open < n) {
        generateParenthesisHelper(n, open + 1, close, current + "(", result);
    }
    
    if (close < open) {
        generateParenthesisHelper(n, open, close + 1, current + ")", result);
    }
}

vector<string> generateParenthesis(int n) {
    vector<string> result;
    generateParenthesisHelper(n, 0, 0, "", result);
    return result;
}

// 10. Palindrome Partitioning
bool isPalindrome(string& s, int left, int right) {
    while (left < right) {
        if (s[left] != s[right]) return false;
        left++;
        right--;
    }
    return true;
}

void partitionHelper(string& s, int start, vector<string>& current, vector<vector<string>>& result) {
    if (start == s.length()) {
        result.push_back(current);
        return;
    }
    
    for (int end = start; end < s.length(); end++) {
        if (isPalindrome(s, start, end)) {
            current.push_back(s.substr(start, end - start + 1));
            partitionHelper(s, end + 1, current, result);
            current.pop_back();
        }
    }
}

vector<vector<string>> partition(string s) {
    vector<vector<string>> result;
    vector<string> current;
    partitionHelper(s, 0, current, result);
    return result;
}

int main() {
    // Test Subsets
    vector<int> nums1 = {1, 2, 3};
    vector<vector<int>> subsetsResult = subsets(nums1);
    cout << "Subsets: " << subsetsResult.size() << " subsets" << endl;
    
    // Test Permutations
    vector<int> nums2 = {1, 2, 3};
    vector<vector<int>> perms = permute(nums2);
    cout << "Permutations: " << perms.size() << " permutations" << endl;
    
    // Test Combinations
    vector<vector<int>> combs = combine(4, 2);
    cout << "Combinations C(4,2): " << combs.size() << " combinations" << endl;
    
    // Test Letter Combinations
    vector<string> letters = letterCombinations("23");
    cout << "Letter combinations of '23': ";
    for (string& s : letters) cout << s << " ";
    cout << endl;
    
    // Test Generate Parentheses
    vector<string> parens = generateParenthesis(3);
    cout << "Valid parentheses (n=3): ";
    for (string& s : parens) cout << s << " ";
    cout << endl;
    
    return 0;
}


