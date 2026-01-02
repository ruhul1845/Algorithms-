/*
    Common Contest Problems on Binary Trees
    ========================================
    
    Collection of frequently asked contest/interview problems.
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ==================== MAXIMUM DIFFERENCE BETWEEN ANCESTOR AND NODE ====================

int maxAncestorDiff(TreeNode* root) {
    int result = 0;
    
    function<pair<int,int>(TreeNode*)> dfs = [&](TreeNode* node) -> pair<int,int> {
        if (!node) return {INT_MAX, INT_MIN};
        
        if (!node->left && !node->right) {
            return {node->val, node->val};
        }
        
        auto [leftMin, leftMax] = dfs(node->left);
        auto [rightMin, rightMax] = dfs(node->right);
        
        int minVal = min({node->val, leftMin, rightMin});
        int maxVal = max({node->val, leftMax, rightMax});
        
        result = max({result, abs(node->val - minVal), abs(node->val - maxVal)});
        
        return {minVal, maxVal};
    };
    
    dfs(root);
    return result;
}

// ==================== SUM OF ROOT TO LEAF BINARY NUMBERS ====================

int sumRootToLeaf(TreeNode* root) {
    int sum = 0;
    
    function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int curr) {
        if (!node) return;
        
        curr = (curr << 1) | node->val;
        
        if (!node->left && !node->right) {
            sum += curr;
            return;
        }
        
        dfs(node->left, curr);
        dfs(node->right, curr);
    };
    
    dfs(root, 0);
    return sum;
}

// ==================== FLIP BINARY TREE TO MATCH PREORDER ====================

vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
    vector<int> flipped;
    int idx = 0;
    bool possible = true;
    
    function<void(TreeNode*)> dfs = [&](TreeNode* node) {
        if (!node || !possible) return;
        
        if (node->val != voyage[idx++]) {
            possible = false;
            return;
        }
        
        if (node->left && node->left->val != voyage[idx]) {
            flipped.push_back(node->val);
            dfs(node->right);
            dfs(node->left);
        } else {
            dfs(node->left);
            dfs(node->right);
        }
    };
    
    dfs(root);
    
    return possible ? flipped : vector<int>{-1};
}

// ==================== LONGEST CONSECUTIVE SEQUENCE ====================

int longestConsecutive(TreeNode* root) {
    int maxLen = 0;
    
    function<void(TreeNode*, int, int)> dfs = [&](TreeNode* node, int parent, int len) {
        if (!node) return;
        
        if (node->val == parent + 1) {
            len++;
        } else {
            len = 1;
        }
        
        maxLen = max(maxLen, len);
        
        dfs(node->left, node->val, len);
        dfs(node->right, node->val, len);
    };
    
    dfs(root, INT_MIN, 0);
    return maxLen;
}

// ==================== SMALLEST STRING FROM LEAF ====================

string smallestFromLeaf(TreeNode* root) {
    string result;
    
    function<void(TreeNode*, string)> dfs = [&](TreeNode* node, string path) {
        if (!node) return;
        
        path = char('a' + node->val) + path;
        
        if (!node->left && !node->right) {
            if (result.empty() || path < result) {
                result = path;
            }
            return;
        }
        
        dfs(node->left, path);
        dfs(node->right, path);
    };
    
    dfs(root, "");
    return result;
}

// ==================== COUNT PAIRS IN DISTANCE K ====================

int countPairs(TreeNode* root, int distance) {
    int count = 0;
    
    function<vector<int>(TreeNode*)> dfs = [&](TreeNode* node) -> vector<int> {
        if (!node) return {};
        
        if (!node->left && !node->right) {
            return {1};
        }
        
        auto left = dfs(node->left);
        auto right = dfs(node->right);
        
        // Count pairs
        for (int l : left) {
            for (int r : right) {
                if (l + r <= distance) count++;
            }
        }
        
        // Return distances incremented by 1
        vector<int> result;
        for (int l : left) {
            if (l + 1 < distance) result.push_back(l + 1);
        }
        for (int r : right) {
            if (r + 1 < distance) result.push_back(r + 1);
        }
        
        return result;
    };
    
    dfs(root);
    return count;
}

// ==================== PSEUDO-PALINDROMIC PATHS ====================

int pseudoPalindromicPaths(TreeNode* root) {
    int count = 0;
    
    function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int mask) {
        if (!node) return;
        
        mask ^= (1 << node->val);
        
        if (!node->left && !node->right) {
            // Check if at most one bit is set (at most one odd count)
            if ((mask & (mask - 1)) == 0) count++;
            return;
        }
        
        dfs(node->left, mask);
        dfs(node->right, mask);
    };
    
    dfs(root, 0);
    return count;
}

// ==================== ALL ELEMENTS IN TWO BSTS ====================

vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
    vector<int> result;
    stack<TreeNode*> s1, s2;
    
    auto pushLeft = [](stack<TreeNode*>& st, TreeNode* node) {
        while (node) {
            st.push(node);
            node = node->left;
        }
    };
    
    pushLeft(s1, root1);
    pushLeft(s2, root2);
    
    while (!s1.empty() || !s2.empty()) {
        stack<TreeNode*>& st = s1.empty() ? s2 : 
                               s2.empty() ? s1 :
                               s1.top()->val <= s2.top()->val ? s1 : s2;
        
        TreeNode* node = st.top();
        st.pop();
        result.push_back(node->val);
        pushLeft(st, node->right);
    }
    
    return result;
}

// ==================== VERIFY PREORDER SERIALIZATION ====================

bool isValidSerialization(string preorder) {
    int slots = 1;
    
    stringstream ss(preorder);
    string token;
    
    while (getline(ss, token, ',')) {
        slots--;
        
        if (slots < 0) return false;
        
        if (token != "#") {
            slots += 2;
        }
    }
    
    return slots == 0;
}

// ==================== FIND BOTTOM LEFT VALUE ====================

int findBottomLeftValue(TreeNode* root) {
    int result = root->val;
    int maxDepth = -1;
    
    function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int depth) {
        if (!node) return;
        
        if (depth > maxDepth) {
            maxDepth = depth;
            result = node->val;
        }
        
        dfs(node->left, depth + 1);
        dfs(node->right, depth + 1);
    };
    
    dfs(root, 0);
    return result;
}

// ==================== TRIM BST ====================

TreeNode* trimBST(TreeNode* root, int low, int high) {
    if (!root) return nullptr;
    
    if (root->val < low) {
        return trimBST(root->right, low, high);
    }
    
    if (root->val > high) {
        return trimBST(root->left, low, high);
    }
    
    root->left = trimBST(root->left, low, high);
    root->right = trimBST(root->right, low, high);
    
    return root;
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

void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << "=== Contest Binary Tree Problems ===" << endl;
    
    // Max Ancestor Difference
    vector<int> nodes1 = {8, 3, 10, 1, 6, -1, 14, -1, -1, 4, 7, 13};
    TreeNode* root1 = buildTree(nodes1);
    cout << "\nMax Ancestor Diff: " << maxAncestorDiff(root1) << endl;
    
    // Longest Consecutive Sequence
    vector<int> nodes2 = {1, -1, 3, 2, 4, -1, -1, -1, 5};
    TreeNode* root2 = buildTree(nodes2);
    cout << "Longest Consecutive: " << longestConsecutive(root2) << endl;
    
    // Find Bottom Left Value
    vector<int> nodes3 = {2, 1, 3};
    TreeNode* root3 = buildTree(nodes3);
    cout << "Bottom Left Value: " << findBottomLeftValue(root3) << endl;
    
    // Verify Preorder Serialization
    cout << "Valid serialization '9,3,4,#,#,1,#,#,2,#,6,#,#': " 
         << (isValidSerialization("9,3,4,#,#,1,#,#,2,#,6,#,#") ? "Yes" : "No") << endl;
    
    // Trim BST
    vector<int> bstNodes = {3, 0, 4, -1, 2, -1, -1, 1};
    TreeNode* bst = buildTree(bstNodes);
    
    cout << "\nOriginal BST inorder: ";
    printInorder(bst);
    cout << endl;
    
    TreeNode* trimmed = trimBST(bst, 1, 3);
    cout << "Trimmed BST [1,3] inorder: ";
    printInorder(trimmed);
    cout << endl;
    
    // All Elements in Two BSTs
    vector<int> bst1Nodes = {2, 1, 4};
    vector<int> bst2Nodes = {1, 0, 3};
    TreeNode* bst1 = buildTree(bst1Nodes);
    TreeNode* bst2 = buildTree(bst2Nodes);
    
    cout << "\nAll elements from two BSTs: ";
    for (int x : getAllElements(bst1, bst2)) cout << x << " ";
    cout << endl;
    
    return 0;
}







