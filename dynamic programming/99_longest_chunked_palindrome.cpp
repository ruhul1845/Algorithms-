/*
    Longest Chunked Palindrome Decomposition
    Problem: Split string into k chunks where s[1]=s[k], s[2]=s[k-1], etc.
             Maximize k.
    
    Example: "ghiabcdefhelloadamhelloabcdefghi" → Output: 7
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    map<pair<int, int>, int> dp;
    string s;
    
    int solve(int left, int right) {
        if (left > right) return 0;
        if (left == right) return 1;
        
        auto key = make_pair(left, right);
        if (dp.count(key)) return dp[key];
        
        int len = right - left + 1;
        int result = 1; // Treat whole remaining as one chunk
        
        for (int i = 1; i <= len / 2; i++) {
            string prefix = s.substr(left, i);
            string suffix = s.substr(right - i + 1, i);
            
            if (prefix == suffix) {
                result = max(result, 2 + solve(left + i, right - i));
            }
        }
        
        return dp[key] = result;
    }
    
public:
    int longestDecomposition(string text) {
        s = text;
        dp.clear();
        return solve(0, s.length() - 1);
    }
};

// ==================== GREEDY APPROACH ====================
class Greedy {
public:
    int longestDecomposition(string text) {
        int n = text.length();
        int left = 0, right = n - 1;
        int count = 0;
        string prefixChunk = "", suffixChunk = "";
        
        while (left < right) {
            prefixChunk += text[left];
            suffixChunk = text[right] + suffixChunk;
            
            if (prefixChunk == suffixChunk) {
                count += 2;
                prefixChunk = "";
                suffixChunk = "";
            }
            
            left++;
            right--;
        }
        
        // Handle middle part
        if (left == right || !prefixChunk.empty()) {
            count++;
        }
        
        return count;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cout << "Enter string: ";
    cin >> s;
    
    TopDown td;
    Greedy gr;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.longestDecomposition(s) << endl;
    cout << "Greedy: " << gr.longestDecomposition(s) << endl;
    
    return 0;
}









