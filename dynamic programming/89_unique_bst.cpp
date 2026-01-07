/*
    Unique Binary Search Trees
    Problem: Count structurally unique BSTs with n nodes (values 1 to n).
    
    Example: n = 3 → Output: 5 (Catalan number)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<int> dp;
    
    int solve(int n) {
        if (n <= 1) return 1;
        if (dp[n] != -1) return dp[n];
        
        int count = 0;
        for (int root = 1; root <= n; root++) {
            int leftTrees = solve(root - 1);
            int rightTrees = solve(n - root);
            count += leftTrees * rightTrees;
        }
        
        return dp[n] = count;
    }
    
public:
    int numTrees(int n) {
        dp.assign(n + 1, -1);
        return solve(n);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int numTrees(int n) {
        // Catalan number: C(n) = sum(C(i-1) * C(n-i)) for i = 1 to n
        vector<int> dp(n + 1, 0);
        dp[0] = dp[1] = 1;
        
        for (int nodes = 2; nodes <= n; nodes++) {
            for (int root = 1; root <= nodes; root++) {
                dp[nodes] += dp[root - 1] * dp[nodes - root];
            }
        }
        
        return dp[n];
    }
    
    // Using Catalan number formula: C(n) = (2n)! / ((n+1)! * n!)
    long long numTreesMath(int n) {
        // C(n) = C(2n, n) / (n+1)
        long long result = 1;
        for (int i = 0; i < n; i++) {
            result = result * 2 * (2 * i + 1) / (i + 2);
        }
        return result;
    }
};

// ==================== Generate All Unique BSTs ====================
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class GenerateTrees {
public:
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0) return {};
        return build(1, n);
    }
    
private:
    vector<TreeNode*> build(int start, int end) {
        if (start > end) return {nullptr};
        
        vector<TreeNode*> trees;
        
        for (int root = start; root <= end; root++) {
            auto leftTrees = build(start, root - 1);
            auto rightTrees = build(root + 1, end);
            
            for (auto left : leftTrees) {
                for (auto right : rightTrees) {
                    TreeNode* node = new TreeNode(root);
                    node->left = left;
                    node->right = right;
                    trees.push_back(node);
                }
            }
        }
        
        return trees;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter n: ";
    cin >> n;
    
    TopDown td;
    BottomUp bu;
    GenerateTrees gt;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.numTrees(n) << endl;
    cout << "Bottom-Up: " << bu.numTrees(n) << endl;
    cout << "Math (Catalan): " << bu.numTreesMath(n) << endl;
    cout << "Generated Trees: " << gt.generateTrees(n).size() << endl;
    
    return 0;
}


















