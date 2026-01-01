/*
    Zigzag and Spiral Level Order Traversal
    ========================================
    
    Variations of level order traversal with alternating directions.
    
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

// Zigzag Level Order (alternating left-right and right-left)
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    bool leftToRight = true;
    
    while (!q.empty()) {
        int size = q.size();
        vector<int> level(size);
        
        for (int i = 0; i < size; i++) {
            TreeNode* curr = q.front();
            q.pop();
            
            // Place at correct index based on direction
            int idx = leftToRight ? i : size - 1 - i;
            level[idx] = curr->val;
            
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        
        result.push_back(level);
        leftToRight = !leftToRight;
    }
    
    return result;
}

// Zigzag using two stacks
vector<vector<int>> zigzagTwoStacks(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    
    stack<TreeNode*> s1, s2;
    s1.push(root);
    
    while (!s1.empty() || !s2.empty()) {
        vector<int> level;
        
        while (!s1.empty()) {
            TreeNode* curr = s1.top();
            s1.pop();
            level.push_back(curr->val);
            
            // Push left then right for next level (right-to-left)
            if (curr->left) s2.push(curr->left);
            if (curr->right) s2.push(curr->right);
        }
        if (!level.empty()) result.push_back(level);
        
        level.clear();
        while (!s2.empty()) {
            TreeNode* curr = s2.top();
            s2.pop();
            level.push_back(curr->val);
            
            // Push right then left for next level (left-to-right)
            if (curr->right) s1.push(curr->right);
            if (curr->left) s1.push(curr->left);
        }
        if (!level.empty()) result.push_back(level);
    }
    
    return result;
}

// Spiral Order (same as zigzag)
vector<vector<int>> spiralOrder(TreeNode* root) {
    return zigzagLevelOrder(root);
}

// Anti-clockwise spiral
vector<vector<int>> antiClockwiseSpiral(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    bool rightToLeft = true;  // Start with right to left
    
    while (!q.empty()) {
        int size = q.size();
        vector<int> level(size);
        
        for (int i = 0; i < size; i++) {
            TreeNode* curr = q.front();
            q.pop();
            
            int idx = rightToLeft ? size - 1 - i : i;
            level[idx] = curr->val;
            
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        
        result.push_back(level);
        rightToLeft = !rightToLeft;
    }
    
    return result;
}

// Print alternate levels
vector<int> alternateLevels(TreeNode* root, bool startWithOdd = true) {
    vector<int> result;
    if (!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    int level = 1;
    
    while (!q.empty()) {
        int size = q.size();
        
        for (int i = 0; i < size; i++) {
            TreeNode* curr = q.front();
            q.pop();
            
            if ((startWithOdd && level % 2 == 1) || 
                (!startWithOdd && level % 2 == 0)) {
                result.push_back(curr->val);
            }
            
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        
        level++;
    }
    
    return result;
}

// Reverse alternate levels of binary tree
void reverseAlternate(TreeNode* root) {
    if (!root) return;
    
    queue<TreeNode*> q;
    q.push(root);
    int level = 0;
    
    while (!q.empty()) {
        int size = q.size();
        vector<TreeNode*> nodes;
        
        for (int i = 0; i < size; i++) {
            TreeNode* curr = q.front();
            q.pop();
            nodes.push_back(curr);
            
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        
        // Swap values at alternate levels
        if (level % 2 == 1) {
            int n = nodes.size();
            for (int i = 0; i < n / 2; i++) {
                swap(nodes[i]->val, nodes[n - 1 - i]->val);
            }
        }
        
        level++;
    }
}

// Get nodes at every K-th level
vector<vector<int>> everyKthLevel(TreeNode* root, int k) {
    vector<vector<int>> result;
    if (!root || k <= 0) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    int level = 1;
    
    while (!q.empty()) {
        int size = q.size();
        vector<int> levelNodes;
        
        for (int i = 0; i < size; i++) {
            TreeNode* curr = q.front();
            q.pop();
            
            if (level % k == 0) {
                levelNodes.push_back(curr->val);
            }
            
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        
        if (!levelNodes.empty()) result.push_back(levelNodes);
        level++;
    }
    
    return result;
}

// Level order in groups of K
vector<vector<int>> levelOrderGrouped(TreeNode* root, int k) {
    vector<vector<int>> result;
    if (!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    vector<int> currentGroup;
    
    while (!q.empty()) {
        int size = q.size();
        
        for (int i = 0; i < size; i++) {
            TreeNode* curr = q.front();
            q.pop();
            
            currentGroup.push_back(curr->val);
            
            if (currentGroup.size() == k) {
                result.push_back(currentGroup);
                currentGroup.clear();
            }
            
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
    
    if (!currentGroup.empty()) {
        result.push_back(currentGroup);
    }
    
    return result;
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
              3
            /   \
           9     20
          / \   /  \
         1   2 15   7
        / \
       4   5
    */
    
    vector<int> nodes = {3, 9, 20, 1, 2, 15, 7, 4, 5};
    TreeNode* root = buildTree(nodes);
    
    cout << "=== Zigzag and Spiral Traversal ===" << endl;
    
    cout << "\nZigzag Level Order:" << endl;
    for (auto& level : zigzagLevelOrder(root)) {
        cout << "  [ ";
        for (int x : level) cout << x << " ";
        cout << "]" << endl;
    }
    
    cout << "\nZigzag using Two Stacks:" << endl;
    for (auto& level : zigzagTwoStacks(root)) {
        cout << "  [ ";
        for (int x : level) cout << x << " ";
        cout << "]" << endl;
    }
    
    cout << "\nAnti-clockwise Spiral:" << endl;
    for (auto& level : antiClockwiseSpiral(root)) {
        cout << "  [ ";
        for (int x : level) cout << x << " ";
        cout << "]" << endl;
    }
    
    cout << "\nAlternate levels (odd): ";
    for (int x : alternateLevels(root, true)) cout << x << " ";
    cout << endl;
    
    cout << "\nAlternate levels (even): ";
    for (int x : alternateLevels(root, false)) cout << x << " ";
    cout << endl;
    
    cout << "\nEvery 2nd level:" << endl;
    for (auto& level : everyKthLevel(root, 2)) {
        cout << "  [ ";
        for (int x : level) cout << x << " ";
        cout << "]" << endl;
    }
    
    cout << "\nLevel order grouped by 3:" << endl;
    for (auto& group : levelOrderGrouped(root, 3)) {
        cout << "  [ ";
        for (int x : group) cout << x << " ";
        cout << "]" << endl;
    }
    
    return 0;
}





