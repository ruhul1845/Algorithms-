/*
    Burn Binary Tree / Time to Burn Tree
    =====================================
    
    Given a binary tree and a target node, find the minimum time to burn
    the entire tree if fire starts from the target node.
    Fire spreads to adjacent nodes (parent and children) in 1 second.
    
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

// Method 1: Using parent map and BFS
int minTimeToBurnTree(TreeNode* root, int targetVal) {
    if (!root) return 0;
    
    // Build parent map and find target
    unordered_map<TreeNode*, TreeNode*> parent;
    TreeNode* target = nullptr;
    
    queue<TreeNode*> q;
    q.push(root);
    parent[root] = nullptr;
    
    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();
        
        if (curr->val == targetVal) target = curr;
        
        if (curr->left) {
            parent[curr->left] = curr;
            q.push(curr->left);
        }
        if (curr->right) {
            parent[curr->right] = curr;
            q.push(curr->right);
        }
    }
    
    if (!target) return -1;
    
    // BFS from target - fire spreads in all directions
    unordered_set<TreeNode*> burnt;
    queue<TreeNode*> fire;
    fire.push(target);
    burnt.insert(target);
    
    int time = 0;
    
    while (!fire.empty()) {
        int size = fire.size();
        bool spread = false;
        
        for (int i = 0; i < size; i++) {
            TreeNode* curr = fire.front();
            fire.pop();
            
            // Spread to left child
            if (curr->left && !burnt.count(curr->left)) {
                burnt.insert(curr->left);
                fire.push(curr->left);
                spread = true;
            }
            
            // Spread to right child
            if (curr->right && !burnt.count(curr->right)) {
                burnt.insert(curr->right);
                fire.push(curr->right);
                spread = true;
            }
            
            // Spread to parent
            if (parent[curr] && !burnt.count(parent[curr])) {
                burnt.insert(parent[curr]);
                fire.push(parent[curr]);
                spread = true;
            }
        }
        
        if (spread) time++;
    }
    
    return time;
}

// Method 2: Single DFS traversal
class BurnTreeDFS {
    int maxTime = 0;
    
    // Returns {height from target, time to burn subtree}
    // If target found: returns positive height from target
    // If target not found: returns negative height
    int dfs(TreeNode* node, int targetVal) {
        if (!node) return 0;
        
        int left = dfs(node->left, targetVal);
        int right = dfs(node->right, targetVal);
        
        // Target found in left subtree
        if (left > 0) {
            maxTime = max(maxTime, left + abs(right));
            return left + 1;
        }
        
        // Target found in right subtree
        if (right > 0) {
            maxTime = max(maxTime, right + abs(left));
            return right + 1;
        }
        
        // Current node is target
        if (node->val == targetVal) {
            maxTime = max(maxTime, abs(left) > abs(right) ? abs(left) : abs(right));
            return 1;
        }
        
        // Target not found, return negative height
        return min(left, right) - 1;
    }
    
public:
    int timeToBurn(TreeNode* root, int target) {
        maxTime = 0;
        dfs(root, target);
        return maxTime;
    }
};

// Get order of burning (which nodes burn at each time step)
vector<vector<int>> getBurningOrder(TreeNode* root, int targetVal) {
    vector<vector<int>> result;
    if (!root) return result;
    
    // Build parent map
    unordered_map<TreeNode*, TreeNode*> parent;
    TreeNode* target = nullptr;
    
    queue<TreeNode*> q;
    q.push(root);
    parent[root] = nullptr;
    
    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();
        
        if (curr->val == targetVal) target = curr;
        
        if (curr->left) {
            parent[curr->left] = curr;
            q.push(curr->left);
        }
        if (curr->right) {
            parent[curr->right] = curr;
            q.push(curr->right);
        }
    }
    
    if (!target) return result;
    
    // BFS from target
    unordered_set<TreeNode*> burnt;
    queue<TreeNode*> fire;
    fire.push(target);
    burnt.insert(target);
    result.push_back({target->val});
    
    while (!fire.empty()) {
        int size = fire.size();
        vector<int> burningNow;
        
        for (int i = 0; i < size; i++) {
            TreeNode* curr = fire.front();
            fire.pop();
            
            if (curr->left && !burnt.count(curr->left)) {
                burnt.insert(curr->left);
                fire.push(curr->left);
                burningNow.push_back(curr->left->val);
            }
            
            if (curr->right && !burnt.count(curr->right)) {
                burnt.insert(curr->right);
                fire.push(curr->right);
                burningNow.push_back(curr->right->val);
            }
            
            if (parent[curr] && !burnt.count(parent[curr])) {
                burnt.insert(parent[curr]);
                fire.push(parent[curr]);
                burningNow.push_back(parent[curr]->val);
            }
        }
        
        if (!burningNow.empty()) {
            result.push_back(burningNow);
        }
    }
    
    return result;
}

// Find the node from which burning takes maximum time
pair<int, int> nodeWithMaxBurnTime(TreeNode* root) {
    int maxTime = 0;
    int maxNode = -1;
    
    // Get all nodes
    vector<TreeNode*> allNodes;
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();
        allNodes.push_back(curr);
        
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
    
    // Find burn time from each node
    for (TreeNode* node : allNodes) {
        int time = minTimeToBurnTree(root, node->val);
        if (time > maxTime) {
            maxTime = time;
            maxNode = node->val;
        }
    }
    
    return {maxNode, maxTime};
}

// Find node to start fire for minimum burn time
pair<int, int> nodeWithMinBurnTime(TreeNode* root) {
    int minTime = INT_MAX;
    int minNode = -1;
    
    // Get all nodes
    vector<TreeNode*> allNodes;
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();
        allNodes.push_back(curr);
        
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
    
    // Find burn time from each node
    for (TreeNode* node : allNodes) {
        int time = minTimeToBurnTree(root, node->val);
        if (time < minTime) {
            minTime = time;
            minNode = node->val;
        }
    }
    
    return {minNode, minTime};
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    /*
              1
            /   \
           2     3
          / \     \
         4   5     6
            / \
           7   8
    */
    
    vector<int> nodes = {1, 2, 3, 4, 5, -1, 6, -1, -1, 7, 8};
    TreeNode* root = buildTree(nodes);
    
    cout << "=== Burn Binary Tree ===" << endl;
    
    cout << "\nTime to burn from node 2: " << minTimeToBurnTree(root, 2) << " seconds" << endl;
    cout << "Time to burn from node 5: " << minTimeToBurnTree(root, 5) << " seconds" << endl;
    cout << "Time to burn from node 7: " << minTimeToBurnTree(root, 7) << " seconds" << endl;
    
    // Using DFS method
    BurnTreeDFS solver;
    cout << "\nTime to burn from node 5 (DFS): " << solver.timeToBurn(root, 5) << " seconds" << endl;
    
    // Burning order
    cout << "\nBurning order starting from node 5:" << endl;
    auto order = getBurningOrder(root, 5);
    for (int t = 0; t < order.size(); t++) {
        cout << "  t=" << t << ": ";
        for (int x : order[t]) cout << x << " ";
        cout << endl;
    }
    
    // Node with max burn time
    auto [maxNode, maxTime] = nodeWithMaxBurnTime(root);
    cout << "\nNode with max burn time: " << maxNode << " (time: " << maxTime << ")" << endl;
    
    // Node with min burn time
    auto [minNode, minTime] = nodeWithMinBurnTime(root);
    cout << "Node with min burn time: " << minNode << " (time: " << minTime << ")" << endl;
    
    return 0;
}





