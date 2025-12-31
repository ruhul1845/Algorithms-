/*
    Path Sum Problems in Binary Tree
    =================================
    
    Various problems related to finding paths and sums in binary tree.
    
    Time Complexity: O(n) to O(n^2) depending on problem
    Space Complexity: O(h) where h is height
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Problem 1: Check if root-to-leaf path with given sum exists
bool hasPathSum(TreeNode* root, int targetSum) {
    if (!root) return false;
    
    // Leaf node
    if (!root->left && !root->right) {
        return root->val == targetSum;
    }
    
    return hasPathSum(root->left, targetSum - root->val) ||
           hasPathSum(root->right, targetSum - root->val);
}

// Problem 2: Find all root-to-leaf paths with given sum
void findPaths(TreeNode* root, int targetSum, vector<int>& path,
               vector<vector<int>>& result) {
    if (!root) return;
    
    path.push_back(root->val);
    
    if (!root->left && !root->right && root->val == targetSum) {
        result.push_back(path);
    }
    
    findPaths(root->left, targetSum - root->val, path, result);
    findPaths(root->right, targetSum - root->val, path, result);
    
    path.pop_back();
}

vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    vector<vector<int>> result;
    vector<int> path;
    findPaths(root, targetSum, path, result);
    return result;
}

// Problem 3: Count paths with sum (path can start/end anywhere)
int pathSumCount(TreeNode* root, long targetSum) {
    if (!root) return 0;
    
    // Count paths starting from root
    function<int(TreeNode*, long)> countFromNode = [&](TreeNode* node, long sum) -> int {
        if (!node) return 0;
        
        int count = (node->val == sum) ? 1 : 0;
        count += countFromNode(node->left, sum - node->val);
        count += countFromNode(node->right, sum - node->val);
        
        return count;
    };
    
    // Count from root + count from left subtree + count from right subtree
    return countFromNode(root, targetSum) +
           pathSumCount(root->left, targetSum) +
           pathSumCount(root->right, targetSum);
}

// Problem 3 Optimized: Using prefix sum
int pathSumOptimized(TreeNode* root, int targetSum) {
    unordered_map<long, int> prefixSum;
    prefixSum[0] = 1;
    int count = 0;
    
    function<void(TreeNode*, long)> dfs = [&](TreeNode* node, long currSum) {
        if (!node) return;
        
        currSum += node->val;
        
        if (prefixSum.count(currSum - targetSum)) {
            count += prefixSum[currSum - targetSum];
        }
        
        prefixSum[currSum]++;
        
        dfs(node->left, currSum);
        dfs(node->right, currSum);
        
        prefixSum[currSum]--;
    };
    
    dfs(root, 0);
    return count;
}

// Problem 4: Maximum path sum (any path)
int maxPathSumGlobal;

int maxGain(TreeNode* root) {
    if (!root) return 0;
    
    int leftGain = max(maxGain(root->left), 0);
    int rightGain = max(maxGain(root->right), 0);
    
    // Path through current node
    int pathSum = root->val + leftGain + rightGain;
    maxPathSumGlobal = max(maxPathSumGlobal, pathSum);
    
    // Return max path going through one side
    return root->val + max(leftGain, rightGain);
}

int maxPathSum(TreeNode* root) {
    maxPathSumGlobal = INT_MIN;
    maxGain(root);
    return maxPathSumGlobal;
}

// Problem 5: Sum of all root-to-leaf numbers
int sumNumbers(TreeNode* root, int currSum = 0) {
    if (!root) return 0;
    
    currSum = currSum * 10 + root->val;
    
    if (!root->left && !root->right) return currSum;
    
    return sumNumbers(root->left, currSum) + sumNumbers(root->right, currSum);
}

// Problem 6: Print all root-to-leaf paths
void getAllPaths(TreeNode* root, vector<int>& path, vector<string>& result) {
    if (!root) return;
    
    path.push_back(root->val);
    
    if (!root->left && !root->right) {
        string p = "";
        for (int i = 0; i < path.size(); i++) {
            p += to_string(path[i]);
            if (i < path.size() - 1) p += "->";
        }
        result.push_back(p);
    }
    
    getAllPaths(root->left, path, result);
    getAllPaths(root->right, path, result);
    
    path.pop_back();
}

vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> result;
    vector<int> path;
    getAllPaths(root, path, result);
    return result;
}

// Problem 7: Longest path with same value (Univalue path)
int longestUnivaluePath(TreeNode* root) {
    int maxLen = 0;
    
    function<int(TreeNode*)> dfs = [&](TreeNode* node) -> int {
        if (!node) return 0;
        
        int left = dfs(node->left);
        int right = dfs(node->right);
        
        int leftPath = 0, rightPath = 0;
        
        if (node->left && node->left->val == node->val) {
            leftPath = left + 1;
        }
        if (node->right && node->right->val == node->val) {
            rightPath = right + 1;
        }
        
        maxLen = max(maxLen, leftPath + rightPath);
        
        return max(leftPath, rightPath);
    };
    
    dfs(root);
    return maxLen;
}

// Problem 8: Sum of left leaves
int sumOfLeftLeaves(TreeNode* root, bool isLeft = false) {
    if (!root) return 0;
    
    if (!root->left && !root->right && isLeft) {
        return root->val;
    }
    
    return sumOfLeftLeaves(root->left, true) + sumOfLeftLeaves(root->right, false);
}

// Problem 9: Path from root to given node
bool getPath(TreeNode* root, int target, vector<int>& path) {
    if (!root) return false;
    
    path.push_back(root->val);
    
    if (root->val == target) return true;
    
    if (getPath(root->left, target, path) || getPath(root->right, target, path)) {
        return true;
    }
    
    path.pop_back();
    return false;
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
              5
            /   \
           4     8
          /     / \
         11    13  4
        / \       / \
       7   2     5   1
    */
    
    vector<int> nodes = {5, 4, 8, 11, -1, 13, 4, 7, 2, -1, -1, 5, 1};
    TreeNode* root = buildTree(nodes);
    
    cout << "=== Path Sum Problems ===" << endl;
    
    // Has Path Sum
    cout << "\nHas path sum 22: " << (hasPathSum(root, 22) ? "Yes" : "No") << endl;
    
    // All paths with sum
    cout << "\nPaths with sum 22:" << endl;
    for (auto& path : pathSum(root, 22)) {
        cout << "  ";
        for (int x : path) cout << x << " ";
        cout << endl;
    }
    
    // All root-to-leaf paths
    cout << "\nAll root-to-leaf paths:" << endl;
    for (auto& p : binaryTreePaths(root)) {
        cout << "  " << p << endl;
    }
    
    // Sum of root-to-leaf numbers
    vector<int> numNodes = {1, 2, 3};
    TreeNode* numRoot = buildTree(numNodes);
    cout << "\nSum of root-to-leaf numbers (tree: 1,2,3): " << sumNumbers(numRoot) << endl;
    
    // Maximum path sum
    vector<int> maxNodes = {-10, 9, 20, -1, -1, 15, 7};
    TreeNode* maxRoot = buildTree(maxNodes);
    cout << "\nMaximum path sum: " << maxPathSum(maxRoot) << endl;
    
    // Sum of left leaves
    cout << "Sum of left leaves: " << sumOfLeftLeaves(root) << endl;
    
    // Path to node
    vector<int> pathTo;
    getPath(root, 2, pathTo);
    cout << "\nPath to node 2: ";
    for (int x : pathTo) cout << x << " ";
    cout << endl;
    
    return 0;
}

