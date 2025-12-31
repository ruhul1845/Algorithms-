/*
    Dynamic Programming on Trees
    ============================
    
    Tree DP problems involve computing optimal values by traversing
    the tree and combining results from subtrees.
    
    Time Complexity: O(n) for most problems
    Space Complexity: O(h) for recursion stack
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ==================== HOUSE ROBBER III ====================
// Cannot rob two directly connected houses

pair<int, int> robHelper(TreeNode* root) {
    if (!root) return {0, 0}; // {rob this, not rob this}
    
    auto [leftRob, leftNotRob] = robHelper(root->left);
    auto [rightRob, rightNotRob] = robHelper(root->right);
    
    // If rob this node, cannot rob children
    int rob = root->val + leftNotRob + rightNotRob;
    
    // If not rob this, can choose best of each child
    int notRob = max(leftRob, leftNotRob) + max(rightRob, rightNotRob);
    
    return {rob, notRob};
}

int houseRobber(TreeNode* root) {
    auto [rob, notRob] = robHelper(root);
    return max(rob, notRob);
}

// ==================== MAXIMUM SUM BST IN BINARY TREE ====================
// Find maximum sum of any BST subtree

struct BSTInfo {
    bool isBST;
    int minVal, maxVal;
    int sum;
};

int maxSumBST = 0;

BSTInfo checkBST(TreeNode* root) {
    if (!root) return {true, INT_MAX, INT_MIN, 0};
    
    auto left = checkBST(root->left);
    auto right = checkBST(root->right);
    
    if (left.isBST && right.isBST && 
        root->val > left.maxVal && root->val < right.minVal) {
        int sum = left.sum + right.sum + root->val;
        maxSumBST = max(maxSumBST, sum);
        
        return {true, 
                min(root->val, left.minVal), 
                max(root->val, right.maxVal), 
                sum};
    }
    
    return {false, 0, 0, 0};
}

int maxSumBSTInTree(TreeNode* root) {
    maxSumBST = 0;
    checkBST(root);
    return maxSumBST;
}

// ==================== BINARY TREE CAMERAS ====================
// Minimum cameras to monitor all nodes

int cameras = 0;

// Returns: 0 = needs camera, 1 = has camera, 2 = covered
int minCameraHelper(TreeNode* root) {
    if (!root) return 2; // null nodes are "covered"
    
    int left = minCameraHelper(root->left);
    int right = minCameraHelper(root->right);
    
    // If any child needs camera, place camera here
    if (left == 0 || right == 0) {
        cameras++;
        return 1;
    }
    
    // If any child has camera, this node is covered
    if (left == 1 || right == 1) {
        return 2;
    }
    
    // Both children are covered but no camera nearby
    return 0;
}

int minCameraCover(TreeNode* root) {
    cameras = 0;
    if (minCameraHelper(root) == 0) {
        cameras++; // Root needs camera
    }
    return cameras;
}

// ==================== LONGEST ZIGZAG PATH ====================

int maxZigzag = 0;

// dir: 0 = came from left, 1 = came from right
void zigzagHelper(TreeNode* node, int dir, int len) {
    if (!node) return;
    
    maxZigzag = max(maxZigzag, len);
    
    if (dir == 0) {
        // Came from left, go right to continue zigzag
        zigzagHelper(node->right, 1, len + 1);
        // Start new zigzag going left
        zigzagHelper(node->left, 0, 1);
    } else {
        // Came from right, go left to continue zigzag
        zigzagHelper(node->left, 0, len + 1);
        // Start new zigzag going right
        zigzagHelper(node->right, 1, 1);
    }
}

int longestZigZag(TreeNode* root) {
    if (!root) return 0;
    maxZigzag = 0;
    zigzagHelper(root->left, 0, 1);
    zigzagHelper(root->right, 1, 1);
    return maxZigzag;
}

// ==================== COUNT GOOD NODES ====================
// Node is good if no node with greater value on path from root

int countGoodNodes(TreeNode* root, int maxSoFar = INT_MIN) {
    if (!root) return 0;
    
    int count = (root->val >= maxSoFar) ? 1 : 0;
    maxSoFar = max(maxSoFar, root->val);
    
    return count + countGoodNodes(root->left, maxSoFar) + 
           countGoodNodes(root->right, maxSoFar);
}

// ==================== DISTRIBUTE COINS ====================
// Each node should have exactly 1 coin, find minimum moves

int moves = 0;

int distributeCoinsHelper(TreeNode* root) {
    if (!root) return 0;
    
    int left = distributeCoinsHelper(root->left);
    int right = distributeCoinsHelper(root->right);
    
    moves += abs(left) + abs(right);
    
    return root->val + left + right - 1;
}

int distributeCoins(TreeNode* root) {
    moves = 0;
    distributeCoinsHelper(root);
    return moves;
}

// ==================== SUM OF DISTANCES ====================
// For each node, find sum of distances to all other nodes

vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
    vector<vector<int>> adj(n);
    vector<int> count(n, 1);  // subtree size
    vector<int> result(n, 0);
    
    for (auto& e : edges) {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
    }
    
    // First DFS: Calculate count and result for root
    function<void(int, int)> dfs1 = [&](int node, int parent) {
        for (int child : adj[node]) {
            if (child != parent) {
                dfs1(child, node);
                count[node] += count[child];
                result[node] += result[child] + count[child];
            }
        }
    };
    
    // Second DFS: Calculate result for all nodes
    function<void(int, int)> dfs2 = [&](int node, int parent) {
        for (int child : adj[node]) {
            if (child != parent) {
                // result[child] = result[node] - count[child] + (n - count[child])
                result[child] = result[node] - 2 * count[child] + n;
                dfs2(child, node);
            }
        }
    };
    
    dfs1(0, -1);
    dfs2(0, -1);
    
    return result;
}

// ==================== MAXIMUM PRODUCT OF SPLIT ====================
// Split tree into two by removing an edge, maximize product of sums

long long maxProduct = 0;
long long totalSum = 0;

long long findSum(TreeNode* root) {
    if (!root) return 0;
    return root->val + findSum(root->left) + findSum(root->right);
}

long long calcProduct(TreeNode* root) {
    if (!root) return 0;
    
    long long subtreeSum = root->val + calcProduct(root->left) + calcProduct(root->right);
    maxProduct = max(maxProduct, subtreeSum * (totalSum - subtreeSum));
    
    return subtreeSum;
}

int maxProductSplit(TreeNode* root) {
    maxProduct = 0;
    totalSum = findSum(root);
    calcProduct(root);
    return maxProduct % (int)(1e9 + 7);
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
    
    cout << "=== Tree Dynamic Programming ===" << endl;
    
    // House Robber III
    /*
              3
            /   \
           2     3
            \     \
             3     1
    */
    vector<int> robNodes = {3, 2, 3, -1, 3, -1, 1};
    TreeNode* robRoot = buildTree(robNodes);
    cout << "\nHouse Robber III: " << houseRobber(robRoot) << endl;
    
    // Binary Tree Cameras
    /*
              0
            /   \
           0     0
          / \
         0   0
    */
    vector<int> camNodes = {0, 0, 0, 0, 0};
    TreeNode* camRoot = buildTree(camNodes);
    cout << "Min cameras needed: " << minCameraCover(camRoot) << endl;
    
    // Distribute Coins
    /*
              3
            /   \
           0     0
    */
    vector<int> coinNodes = {3, 0, 0};
    TreeNode* coinRoot = buildTree(coinNodes);
    cout << "Moves to distribute coins: " << distributeCoins(coinRoot) << endl;
    
    // Good Nodes
    /*
              3
            /   \
           1     4
          /     / \
         3     1   5
    */
    vector<int> goodNodes = {3, 1, 4, 3, -1, 1, 5};
    TreeNode* goodRoot = buildTree(goodNodes);
    cout << "Count of good nodes: " << countGoodNodes(goodRoot) << endl;
    
    // Longest ZigZag
    /*
              1
            /   \
           1     1
          / \     \
         1   1     1
              \   / \
               1 1   1
    */
    vector<int> zigNodes = {1, 1, 1, 1, 1, -1, 1, -1, -1, -1, 1, 1, 1};
    TreeNode* zigRoot = buildTree(zigNodes);
    cout << "Longest zigzag path: " << longestZigZag(zigRoot) << endl;
    
    return 0;
}

