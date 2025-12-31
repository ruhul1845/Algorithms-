/*
    All Nodes at Distance K
    =======================
    
    Find all nodes at distance K from a target node.
    
    Time Complexity: O(n)
    Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Method 1: Convert tree to graph, then BFS
vector<int> distanceKGraph(TreeNode* root, TreeNode* target, int k) {
    vector<int> result;
    if (!root || !target) return result;
    
    // Build adjacency list (parent-child relationships)
    unordered_map<TreeNode*, TreeNode*> parent;
    
    // BFS to find parents
    queue<TreeNode*> q;
    q.push(root);
    parent[root] = nullptr;
    
    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();
        
        if (curr->left) {
            parent[curr->left] = curr;
            q.push(curr->left);
        }
        if (curr->right) {
            parent[curr->right] = curr;
            q.push(curr->right);
        }
    }
    
    // BFS from target
    unordered_set<TreeNode*> visited;
    queue<TreeNode*> bfs;
    bfs.push(target);
    visited.insert(target);
    
    int dist = 0;
    while (!bfs.empty()) {
        if (dist == k) {
            while (!bfs.empty()) {
                result.push_back(bfs.front()->val);
                bfs.pop();
            }
            return result;
        }
        
        int size = bfs.size();
        for (int i = 0; i < size; i++) {
            TreeNode* curr = bfs.front();
            bfs.pop();
            
            // Check left child
            if (curr->left && !visited.count(curr->left)) {
                visited.insert(curr->left);
                bfs.push(curr->left);
            }
            
            // Check right child
            if (curr->right && !visited.count(curr->right)) {
                visited.insert(curr->right);
                bfs.push(curr->right);
            }
            
            // Check parent
            if (parent[curr] && !visited.count(parent[curr])) {
                visited.insert(parent[curr]);
                bfs.push(parent[curr]);
            }
        }
        
        dist++;
    }
    
    return result;
}

// Method 2: DFS approach
class Solution {
    vector<int> result;
    
    // Find nodes at distance k in subtree
    void findInSubtree(TreeNode* node, int dist, int k) {
        if (!node || dist > k) return;
        
        if (dist == k) {
            result.push_back(node->val);
            return;
        }
        
        findInSubtree(node->left, dist + 1, k);
        findInSubtree(node->right, dist + 1, k);
    }
    
    // Returns distance from node to target, -1 if not found
    int dfs(TreeNode* node, TreeNode* target, int k) {
        if (!node) return -1;
        
        if (node == target) {
            findInSubtree(node, 0, k);
            return 0;
        }
        
        int leftDist = dfs(node->left, target, k);
        if (leftDist != -1) {
            if (leftDist + 1 == k) {
                result.push_back(node->val);
            } else {
                findInSubtree(node->right, leftDist + 2, k);
            }
            return leftDist + 1;
        }
        
        int rightDist = dfs(node->right, target, k);
        if (rightDist != -1) {
            if (rightDist + 1 == k) {
                result.push_back(node->val);
            } else {
                findInSubtree(node->left, rightDist + 2, k);
            }
            return rightDist + 1;
        }
        
        return -1;
    }
    
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        result.clear();
        dfs(root, target, k);
        return result;
    }
};

// Find nodes at distance K from root
vector<int> nodesAtDistanceFromRoot(TreeNode* root, int k) {
    vector<int> result;
    
    function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int dist) {
        if (!node) return;
        
        if (dist == k) {
            result.push_back(node->val);
            return;
        }
        
        dfs(node->left, dist + 1);
        dfs(node->right, dist + 1);
    };
    
    dfs(root, 0);
    return result;
}

// Find nodes at distance K from all leaf nodes
vector<int> nodesAtDistanceFromLeaves(TreeNode* root, int k) {
    set<int> resultSet;
    
    function<void(TreeNode*, vector<TreeNode*>&)> dfs = 
        [&](TreeNode* node, vector<TreeNode*>& path) {
        if (!node) return;
        
        path.push_back(node);
        
        // If leaf node
        if (!node->left && !node->right) {
            if (path.size() > k) {
                resultSet.insert(path[path.size() - 1 - k]->val);
            }
        }
        
        dfs(node->left, path);
        dfs(node->right, path);
        
        path.pop_back();
    };
    
    vector<TreeNode*> path;
    dfs(root, path);
    
    return vector<int>(resultSet.begin(), resultSet.end());
}

// Find closest leaf to given node
pair<int, int> closestLeaf(TreeNode* root, int targetVal) {
    // First, build parent map
    unordered_map<TreeNode*, TreeNode*> parent;
    TreeNode* target = nullptr;
    
    function<void(TreeNode*, TreeNode*)> buildParent = 
        [&](TreeNode* node, TreeNode* par) {
        if (!node) return;
        
        parent[node] = par;
        if (node->val == targetVal) target = node;
        
        buildParent(node->left, node);
        buildParent(node->right, node);
    };
    
    buildParent(root, nullptr);
    
    if (!target) return {-1, -1};
    
    // BFS from target to find closest leaf
    queue<TreeNode*> q;
    unordered_set<TreeNode*> visited;
    q.push(target);
    visited.insert(target);
    
    int dist = 0;
    while (!q.empty()) {
        int size = q.size();
        
        for (int i = 0; i < size; i++) {
            TreeNode* curr = q.front();
            q.pop();
            
            // If leaf
            if (!curr->left && !curr->right) {
                return {curr->val, dist};
            }
            
            if (curr->left && !visited.count(curr->left)) {
                visited.insert(curr->left);
                q.push(curr->left);
            }
            if (curr->right && !visited.count(curr->right)) {
                visited.insert(curr->right);
                q.push(curr->right);
            }
            if (parent[curr] && !visited.count(parent[curr])) {
                visited.insert(parent[curr]);
                q.push(parent[curr]);
            }
        }
        
        dist++;
    }
    
    return {-1, -1};
}

TreeNode* buildTree(vector<int>& nodes) {
    if (nodes.empty() || nodes[0] == -1) return nullptr;
    
    TreeNode* root = new TreeNode(nodes[0]);
    queue<TreeNode*> q;
    q.push(root);
    
    int i = 1;
    while (!q.empty() && i < nodes.size()) {
        TreeNode* curr = q.front();
        q.pop();
        
        if (i < nodes.size() && nodes[i] != -1) {
            curr->left = new TreeNode(nodes[i]);
            q.push(curr->left);
        }
        i++;
        
        if (i < nodes.size() && nodes[i] != -1) {
            curr->right = new TreeNode(nodes[i]);
            q.push(curr->right);
        }
        i++;
    }
    
    return root;
}

TreeNode* findNode(TreeNode* root, int val) {
    if (!root) return nullptr;
    if (root->val == val) return root;
    
    TreeNode* left = findNode(root->left, val);
    if (left) return left;
    return findNode(root->right, val);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    /*
              3
            /   \
           5     1
          / \   / \
         6   2 0   8
            / \
           7   4
    */
    
    vector<int> nodes = {3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4};
    TreeNode* root = buildTree(nodes);
    
    cout << "=== Nodes at Distance K ===" << endl;
    
    TreeNode* target = findNode(root, 5);
    
    cout << "\nNodes at distance 2 from node 5 (Graph method): ";
    for (int x : distanceKGraph(root, target, 2)) cout << x << " ";
    cout << endl;
    
    Solution sol;
    cout << "Nodes at distance 2 from node 5 (DFS method): ";
    for (int x : sol.distanceK(root, target, 2)) cout << x << " ";
    cout << endl;
    
    cout << "\nNodes at distance 2 from root: ";
    for (int x : nodesAtDistanceFromRoot(root, 2)) cout << x << " ";
    cout << endl;
    
    cout << "\nNodes at distance 1 from leaves: ";
    for (int x : nodesAtDistanceFromLeaves(root, 1)) cout << x << " ";
    cout << endl;
    
    cout << "\nNodes at distance 2 from leaves: ";
    for (int x : nodesAtDistanceFromLeaves(root, 2)) cout << x << " ";
    cout << endl;
    
    auto [leaf, dist] = closestLeaf(root, 5);
    cout << "\nClosest leaf to node 5: " << leaf << " at distance " << dist << endl;
    
    auto [leaf2, dist2] = closestLeaf(root, 2);
    cout << "Closest leaf to node 2: " << leaf2 << " at distance " << dist2 << endl;
    
    return 0;
}

