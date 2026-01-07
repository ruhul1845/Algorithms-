/*
    Word Break
    Problem: Given a string and dictionary, determine if string can be 
             segmented into dictionary words.
    
    Example: s = "leetcode", dict = ["leet", "code"] → Output: true
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<int> dp;
    string s;
    unordered_set<string> dict;
    
    bool solve(int idx) {
        if (idx == s.length()) return true;
        if (dp[idx] != -1) return dp[idx];
        
        for (int end = idx + 1; end <= s.length(); end++) {
            string word = s.substr(idx, end - idx);
            if (dict.count(word) && solve(end)) {
                return dp[idx] = true;
            }
        }
        
        return dp[idx] = false;
    }
    
public:
    bool wordBreak(string& str, vector<string>& wordDict) {
        s = str;
        for (auto& w : wordDict) dict.insert(w);
        dp.assign(s.length(), -1);
        return solve(0);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    bool wordBreak(string& s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        int n = s.length();
        
        // dp[i] = can we segment s[0..i-1]?
        vector<bool> dp(n + 1, false);
        dp[0] = true;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && dict.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp[n];
    }
    
    // Get one valid segmentation
    vector<string> getSegmentation(string& s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        int n = s.length();
        
        vector<bool> dp(n + 1, false);
        vector<int> parent(n + 1, -1);
        dp[0] = true;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && dict.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    parent[i] = j;
                    break;
                }
            }
        }
        
        vector<string> result;
        if (!dp[n]) return result;
        
        int idx = n;
        while (idx > 0) {
            result.push_back(s.substr(parent[idx], idx - parent[idx]));
            idx = parent[idx];
        }
        
        reverse(result.begin(), result.end());
        return result;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    int n;
    cout << "Enter string: ";
    cin >> s;
    cout << "Enter number of words in dictionary: ";
    cin >> n;
    
    vector<string> dict(n);
    cout << "Enter dictionary words: ";
    for (int i = 0; i < n; i++) cin >> dict[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << (td.wordBreak(s, dict) ? "Yes" : "No") << endl;
    cout << "Bottom-Up: " << (bu.wordBreak(s, dict) ? "Yes" : "No") << endl;
    
    auto seg = bu.getSegmentation(s, dict);
    if (!seg.empty()) {
        cout << "Segmentation: ";
        for (auto& w : seg) cout << w << " ";
        cout << endl;
    }
    
    return 0;
}


















