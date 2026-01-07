/*
    Tree DP - Dynamic Programming on Trees
    - Various tree DP problems
*/

#include <bits/stdc++.h>
using namespace std;

class TreeDP {
public:
    int n;
    vector<vector<int>> adj;
    
    TreeDP(int n) : n(n), adj(n) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // ==================== Maximum Independent Set ====================
    pair<int, int> maxIndependentSet() {
        vector<int> include(n), exclude(n);
        dfsIndependent(0, -1, include, exclude);
        return {max(include[0], exclude[0]), 0};
    }
    
    void dfsIndependent(int node, int parent, vector<int>& inc, vector<int>& exc) {
        inc[node] = 1;
        exc[node] = 0;
        
        for (int child : adj[node]) {
            if (child != parent) {
                dfsIndependent(child, node, inc, exc);
                inc[node] += exc[child];
                exc[node] += max(inc[child], exc[child]);
            }
        }
    }
    
    // ==================== Tree Matching ====================
    int maxMatching() {
        vector<int> dp(n, 0); // dp[v] = max matching in subtree
        dfsMatching(0, -1, dp);
        return dp[0];
    }
    
    void dfsMatching(int node, int parent, vector<int>& dp) {
        int sumChildren = 0;
        int maxGain = 0;
        
        for (int child : adj[node]) {
            if (child != parent) {
                dfsMatching(child, node, dp);
                sumChildren += dp[child];
            }
        }
        
        for (int child : adj[node]) {
            if (child != parent) {
                // Try matching edge (node, child)
                int gain = 1 + (sumChildren - dp[child]);
                for (int grandchild : adj[child]) {
                    if (grandchild != node) {
                        gain += dp[grandchild];
                    }
                }
                maxGain = max(maxGain, gain - sumChildren);
            }
        }
        
        dp[node] = sumChildren + maxGain;
    }
    
    // ==================== Sum of Distances ====================
    vector<long long> sumOfDistances() {
        vector<int> subtreeSize(n, 1);
        vector<long long> answer(n, 0);
        
        // First DFS: calculate subtree sizes and answer[0]
        dfsDown(0, -1, subtreeSize, answer);
        
        // Second DFS: re-root to calculate all answers
        dfsUp(0, -1, subtreeSize, answer);
        
        return answer;
    }
    
    void dfsDown(int node, int parent, vector<int>& size, vector<long long>& ans) {
        for (int child : adj[node]) {
            if (child != parent) {
                dfsDown(child, node, size, ans);
                size[node] += size[child];
                ans[node] += ans[child] + size[child];
            }
        }
    }
    
    void dfsUp(int node, int parent, vector<int>& size, vector<long long>& ans) {
        for (int child : adj[node]) {
            if (child != parent) {
                ans[child] = ans[node] - size[child] + (n - size[child]);
                dfsUp(child, node, size, ans);
            }
        }
    }
    
    // ==================== All Longest Paths ====================
    vector<int> allLongestPaths() {
        vector<int> down1(n, 0), down2(n, 0), up(n, 0);
        
        dfsDownPaths(0, -1, down1, down2);
        dfsUpPaths(0, -1, down1, down2, up);
        
        vector<int> result(n);
        for (int i = 0; i < n; i++) {
            result[i] = max(down1[i], up[i]);
        }
        return result;
    }
    
    void dfsDownPaths(int node, int parent, vector<int>& d1, vector<int>& d2) {
        for (int child : adj[node]) {
            if (child != parent) {
                dfsDownPaths(child, node, d1, d2);
                int childPath = d1[child] + 1;
                if (childPath > d1[node]) {
                    d2[node] = d1[node];
                    d1[node] = childPath;
                } else if (childPath > d2[node]) {
                    d2[node] = childPath;
                }
            }
        }
    }
    
    void dfsUpPaths(int node, int parent, vector<int>& d1, vector<int>& d2, vector<int>& up) {
        for (int child : adj[node]) {
            if (child != parent) {
                if (d1[child] + 1 == d1[node]) {
                    up[child] = max(up[node], d2[node]) + 1;
                } else {
                    up[child] = max(up[node], d1[node]) + 1;
                }
                dfsUpPaths(child, node, d1, d2, up);
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Tree DP Demo ===" << endl;
    
    TreeDP tree(7);
    tree.addEdge(0, 1);
    tree.addEdge(0, 2);
    tree.addEdge(1, 3);
    tree.addEdge(1, 4);
    tree.addEdge(2, 5);
    tree.addEdge(2, 6);
    
    cout << "Max Independent Set: " << tree.maxIndependentSet().first << endl;
    cout << "Max Matching: " << tree.maxMatching() << endl;
    
    auto sumDist = tree.sumOfDistances();
    cout << "Sum of distances from each node:" << endl;
    for (int i = 0; i < 7; i++) {
        cout << "Node " << i << ": " << sumDist[i] << endl;
    }
    
    auto longestPaths = tree.allLongestPaths();
    cout << "\nLongest path from each node:" << endl;
    for (int i = 0; i < 7; i++) {
        cout << "Node " << i << ": " << longestPaths[i] << endl;
    }
    
    return 0;
}


















