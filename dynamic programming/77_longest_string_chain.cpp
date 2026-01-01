/*
    Longest String Chain
    Problem: Find longest chain where each word is predecessor of next.
             Word A is predecessor of B if we can add one letter to A to get B.
    
    Example: ["a","b","ba","bca","bda","bdca"] → Output: 4 (a → ba → bda → bdca)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    unordered_map<string, int> dp;
    unordered_set<string> wordSet;
    
    int solve(const string& word) {
        if (dp.count(word)) return dp[word];
        
        int maxLen = 1;
        
        // Try removing each character
        for (int i = 0; i < word.length(); i++) {
            string pred = word.substr(0, i) + word.substr(i + 1);
            if (wordSet.count(pred)) {
                maxLen = max(maxLen, 1 + solve(pred));
            }
        }
        
        return dp[word] = maxLen;
    }
    
public:
    int longestStrChain(vector<string>& words) {
        wordSet = unordered_set<string>(words.begin(), words.end());
        dp.clear();
        
        int maxChain = 0;
        for (const string& word : words) {
            maxChain = max(maxChain, solve(word));
        }
        
        return maxChain;
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int longestStrChain(vector<string>& words) {
        // Sort by length
        sort(words.begin(), words.end(), [](const string& a, const string& b) {
            return a.length() < b.length();
        });
        
        unordered_map<string, int> dp;
        int maxChain = 1;
        
        for (const string& word : words) {
            dp[word] = 1;
            
            // Try removing each character to find predecessor
            for (int i = 0; i < word.length(); i++) {
                string pred = word.substr(0, i) + word.substr(i + 1);
                if (dp.count(pred)) {
                    dp[word] = max(dp[word], dp[pred] + 1);
                }
            }
            
            maxChain = max(maxChain, dp[word]);
        }
        
        return maxChain;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter number of words: ";
    cin >> n;
    
    vector<string> words(n);
    cout << "Enter words: ";
    for (int i = 0; i < n; i++) cin >> words[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.longestStrChain(words) << endl;
    cout << "Bottom-Up: " << bu.longestStrChain(words) << endl;
    
    return 0;
}







