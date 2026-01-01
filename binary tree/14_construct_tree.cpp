/*
    Construct Binary Tree from Traversals
    ======================================
    
    Building binary tree from different combinations of traversals:
    1. Preorder + Inorder
    2. Postorder + Inorder
    3. Preorder + Postorder (only for full binary tree)
    4. Level Order + Inorder
    
    Time Complexity: O(n) with hash map, O(n²) without
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

// ==================== PREORDER + INORDER ====================

class BuildFromPreIn {
    unordered_map<int, int> inorderMap;
    int preIndex = 0;
    
    TreeNode* build(vector<int>& preorder, int inStart, int inEnd) {
        if (inStart > inEnd) return nullptr;
        
        int rootVal = preorder[preIndex++];
        TreeNode* root = new TreeNode(rootVal);
        
        int inIndex = inorderMap[rootVal];
        
        // Build left subtree first (preorder: root, left, right)
        root->left = build(preorder, inStart, inIndex - 1);
        root->right = build(preorder, inIndex + 1, inEnd);
        
        return root;
    }
    
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        inorderMap.clear();
        preIndex = 0;
        
        for (int i = 0; i < inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }
        
        return build(preorder, 0, inorder.size() - 1);
    }
};

// ==================== POSTORDER + INORDER ====================

class BuildFromPostIn {
    unordered_map<int, int> inorderMap;
    int postIndex;
    
    TreeNode* build(vector<int>& postorder, int inStart, int inEnd) {
        if (inStart > inEnd) return nullptr;
        
        int rootVal = postorder[postIndex--];
        TreeNode* root = new TreeNode(rootVal);
        
        int inIndex = inorderMap[rootVal];
        
        // Build right subtree first (postorder: left, right, root)
        root->right = build(postorder, inIndex + 1, inEnd);
        root->left = build(postorder, inStart, inIndex - 1);
        
        return root;
    }
    
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        inorderMap.clear();
        postIndex = postorder.size() - 1;
        
        for (int i = 0; i < inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }
        
        return build(postorder, 0, inorder.size() - 1);
    }
};

// ==================== PREORDER + POSTORDER (Full Binary Tree) ====================

class BuildFromPrePost {
    unordered_map<int, int> postMap;
    int preIndex = 0;
    
    TreeNode* build(vector<int>& pre, vector<int>& post, int postStart, int postEnd) {
        if (preIndex >= pre.size() || postStart > postEnd) return nullptr;
        
        TreeNode* root = new TreeNode(pre[preIndex++]);
        
        if (postStart == postEnd) return root;
        
        // Find left subtree root in postorder
        int leftRootVal = pre[preIndex];
        int leftRootIdx = postMap[leftRootVal];
        
        root->left = build(pre, post, postStart, leftRootIdx);
        root->right = build(pre, post, leftRootIdx + 1, postEnd - 1);
        
        return root;
    }
    
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& postorder) {
        postMap.clear();
        preIndex = 0;
        
        for (int i = 0; i < postorder.size(); i++) {
            postMap[postorder[i]] = i;
        }
        
        return build(preorder, postorder, 0, postorder.size() - 1);
    }
};

// ==================== LEVEL ORDER + INORDER ====================

class BuildFromLevelIn {
    unordered_map<int, int> inorderMap;
    
    TreeNode* build(vector<int>& level, vector<int>& inorder, int inStart, int inEnd) {
        if (level.empty() || inStart > inEnd) return nullptr;
        
        TreeNode* root = new TreeNode(level[0]);
        int inIndex = inorderMap[level[0]];
        
        // Separate level order for left and right subtrees
        vector<int> leftLevel, rightLevel;
        
        for (int i = 1; i < level.size(); i++) {
            int idx = inorderMap[level[i]];
            if (idx < inIndex) {
                leftLevel.push_back(level[i]);
            } else {
                rightLevel.push_back(level[i]);
            }
        }
        
        root->left = build(leftLevel, inorder, inStart, inIndex - 1);
        root->right = build(rightLevel, inorder, inIndex + 1, inEnd);
        
        return root;
    }
    
public:
    TreeNode* buildTree(vector<int>& level, vector<int>& inorder) {
        inorderMap.clear();
        
        for (int i = 0; i < inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }
        
        return build(level, inorder, 0, inorder.size() - 1);
    }
};

// ==================== BUILD BST FROM PREORDER ====================

TreeNode* bstFromPreorder(vector<int>& preorder) {
    int idx = 0;
    
    function<TreeNode*(int, int)> build = [&](int minVal, int maxVal) -> TreeNode* {
        if (idx >= preorder.size()) return nullptr;
        
        int val = preorder[idx];
        if (val < minVal || val > maxVal) return nullptr;
        
        TreeNode* root = new TreeNode(val);
        idx++;
        
        root->left = build(minVal, val);
        root->right = build(val, maxVal);
        
        return root;
    };
    
    return build(INT_MIN, INT_MAX);
}

// ==================== BUILD BST FROM SORTED ARRAY ====================

TreeNode* sortedArrayToBST(vector<int>& nums, int left, int right) {
    if (left > right) return nullptr;
    
    int mid = left + (right - left) / 2;
    TreeNode* root = new TreeNode(nums[mid]);
    root->left = sortedArrayToBST(nums, left, mid - 1);
    root->right = sortedArrayToBST(nums, mid + 1, right);
    
    return root;
}

// ==================== BUILD COMPLETE BINARY TREE FROM ARRAY ====================

TreeNode* buildCompleteBT(vector<int>& arr, int idx) {
    if (idx >= arr.size()) return nullptr;
    
    TreeNode* root = new TreeNode(arr[idx]);
    root->left = buildCompleteBT(arr, 2 * idx + 1);
    root->right = buildCompleteBT(arr, 2 * idx + 2);
    
    return root;
}

// Helper functions
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

void printPreorder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    printPreorder(root->left);
    printPreorder(root->right);
}

void printPostorder(TreeNode* root) {
    if (!root) return;
    printPostorder(root->left);
    printPostorder(root->right);
    cout << root->val << " ";
}

void printTree(TreeNode* root, string prefix = "", bool isLeft = true) {
    if (!root) return;
    
    cout << prefix;
    cout << (isLeft ? "├──" : "└──");
    cout << root->val << endl;
    
    printTree(root->left, prefix + (isLeft ? "│   " : "    "), true);
    printTree(root->right, prefix + (isLeft ? "│   " : "    "), false);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << "=== Construct Binary Tree ===" << endl;
    
    // From Preorder and Inorder
    /*
              3
            /   \
           9     20
                /  \
               15   7
    */
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};
    
    BuildFromPreIn builder1;
    TreeNode* tree1 = builder1.buildTree(preorder, inorder);
    
    cout << "\n1. From Preorder + Inorder:" << endl;
    cout << "   Preorder: 3 9 20 15 7" << endl;
    cout << "   Inorder:  9 3 15 20 7" << endl;
    cout << "   Result:" << endl;
    printTree(tree1);
    
    // From Inorder and Postorder
    vector<int> postorder = {9, 15, 7, 20, 3};
    
    BuildFromPostIn builder2;
    TreeNode* tree2 = builder2.buildTree(inorder, postorder);
    
    cout << "\n2. From Inorder + Postorder:" << endl;
    cout << "   Inorder:   9 3 15 20 7" << endl;
    cout << "   Postorder: 9 15 7 20 3" << endl;
    cout << "   Result Preorder: ";
    printPreorder(tree2);
    cout << endl;
    
    // From Preorder and Postorder (Full Binary Tree)
    /*
              1
            /   \
           2     3
          / \   / \
         4   5 6   7
    */
    vector<int> pre = {1, 2, 4, 5, 3, 6, 7};
    vector<int> post = {4, 5, 2, 6, 7, 3, 1};
    
    BuildFromPrePost builder3;
    TreeNode* tree3 = builder3.buildTree(pre, post);
    
    cout << "\n3. From Preorder + Postorder (Full BT):" << endl;
    cout << "   Result Inorder: ";
    printInorder(tree3);
    cout << endl;
    
    // BST from Preorder
    vector<int> bstPre = {8, 5, 1, 7, 10, 12};
    TreeNode* bst = bstFromPreorder(bstPre);
    
    cout << "\n4. BST from Preorder [8,5,1,7,10,12]:" << endl;
    printTree(bst);
    
    // BST from sorted array
    vector<int> sorted = {1, 2, 3, 4, 5, 6, 7};
    TreeNode* balancedBST = sortedArrayToBST(sorted, 0, sorted.size() - 1);
    
    cout << "\n5. Balanced BST from sorted [1..7]:" << endl;
    printTree(balancedBST);
    
    return 0;
}





