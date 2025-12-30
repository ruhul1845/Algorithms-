/*
    Filling Bookcase Shelves
    Problem: Place books on shelves of width shelfWidth.
             Minimize total height. Books must be placed in order.
    
    books[i] = [width, height]
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<int> dp;
    vector<vector<int>> books;
    int shelfWidth;
    
    int solve(int idx) {
        if (idx == books.size()) return 0;
        if (dp[idx] != -1) return dp[idx];
        
        int width = 0, height = 0;
        int minHeight = INT_MAX;
        
        for (int j = idx; j < books.size(); j++) {
            width += books[j][0];
            if (width > shelfWidth) break;
            
            height = max(height, books[j][1]);
            minHeight = min(minHeight, height + solve(j + 1));
        }
        
        return dp[idx] = minHeight;
    }
    
public:
    int minHeightShelves(vector<vector<int>>& b, int sw) {
        books = b;
        shelfWidth = sw;
        dp.assign(books.size(), -1);
        return solve(0);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int n = books.size();
        
        // dp[i] = min height to place books 0..i-1
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        
        for (int i = 1; i <= n; i++) {
            int width = 0, height = 0;
            
            for (int j = i; j >= 1; j--) {
                width += books[j - 1][0];
                if (width > shelfWidth) break;
                
                height = max(height, books[j - 1][1]);
                dp[i] = min(dp[i], dp[j - 1] + height);
            }
        }
        
        return dp[n];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, shelfWidth;
    cout << "Enter number of books and shelf width: ";
    cin >> n >> shelfWidth;
    
    vector<vector<int>> books(n, vector<int>(2));
    cout << "Enter book dimensions (width height):" << endl;
    for (int i = 0; i < n; i++) {
        cin >> books[i][0] >> books[i][1];
    }
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.minHeightShelves(books, shelfWidth) << endl;
    cout << "Bottom-Up: " << bu.minHeightShelves(books, shelfWidth) << endl;
    
    return 0;
}

