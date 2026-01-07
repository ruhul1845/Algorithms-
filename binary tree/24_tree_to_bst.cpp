/*
    Binary Tree to BST Conversion
    =============================
    
    Convert a binary tree to BST while keeping the structure same.
    
    Time Complexity: O(n log n) due to sorting
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

// ==================== CONVERT BT TO BST (SAME STRUCTURE) ====================

class BTtoBST {
    vector<int> values;
    int idx;
    
    // Collect all values (any traversal)
    void collectValues(TreeNode* root) {
        if (!root) return;
        values.push_back(root->val);
        collectValues(root->left);
        collectValues(root->right);
    }
    
    // Replace values using inorder
    void replaceValues(TreeNode* root) {
        if (!root) return;
        replaceValues(root->left);
        root->val = values[idx++];
        replaceValues(root->right);
    }
    
public:
    void convertToBST(TreeNode* root) {
        values.clear();
        idx = 0;
        
        // Step 1: Collect all values
        collectValues(root);
        
        // Step 2: Sort values
        sort(values.begin(), values.end());
        
        // Step 3: Replace in inorder manner
        replaceValues(root);
    }
};

// ==================== MERGE TWO BSTs ====================

// Method 1: Store inorder, merge, create balanced BST
TreeNode* mergeBSTs(TreeNode* root1, TreeNode* root2) {
    // Get inorder traversals
    vector<int> inorder1, inorder2;
    
    function<void(TreeNode*, vector<int>&)> getInorder = 
        [&](TreeNode* node, vector<int>& arr) {
        if (!node) return;
        getInorder(node->left, arr);
        arr.push_back(node->val);
        getInorder(node->right, arr);
    };
    
    getInorder(root1, inorder1);
    getInorder(root2, inorder2);
    
    // Merge two sorted arrays
    vector<int> merged;
    int i = 0, j = 0;
    while (i < inorder1.size() && j < inorder2.size()) {
        if (inorder1[i] <= inorder2[j]) {
            merged.push_back(inorder1[i++]);
        } else {
            merged.push_back(inorder2[j++]);
        }
    }
    while (i < inorder1.size()) merged.push_back(inorder1[i++]);
    while (j < inorder2.size()) merged.push_back(inorder2[j++]);
    
    // Build balanced BST from sorted array
    function<TreeNode*(int, int)> buildBST = [&](int left, int right) -> TreeNode* {
        if (left > right) return nullptr;
        
        int mid = left + (right - left) / 2;
        TreeNode* node = new TreeNode(merged[mid]);
        node->left = buildBST(left, mid - 1);
        node->right = buildBST(mid + 1, right);
        
        return node;
    };
    
    return buildBST(0, merged.size() - 1);
}

// ==================== BST TO GREATER SUM TREE ====================

// Convert BST so each node contains sum of all nodes >= itself
TreeNode* bstToGST(TreeNode* root) {
    int sum = 0;
    
    // Reverse inorder (right, root, left)
    function<void(TreeNode*)> convert = [&](TreeNode* node) {
        if (!node) return;
        
        convert(node->right);
        sum += node->val;
        node->val = sum;
        convert(node->left);
    };
    
    convert(root);
    return root;
}

// ==================== LARGEST BST IN BINARY TREE ====================

struct BSTInfo {
    bool isBST;
    int size;
    int minVal;
    int maxVal;
};

int largestBSTSize = 0;

BSTInfo largestBSTHelper(TreeNode* root) {
    if (!root) {
        return {true, 0, INT_MAX, INT_MIN};
    }
    
    auto left = largestBSTHelper(root->left);
    auto right = largestBSTHelper(root->right);
    
    if (left.isBST && right.isBST && 
        root->val > left.maxVal && root->val < right.minVal) {
        int size = left.size + right.size + 1;
        largestBSTSize = max(largestBSTSize, size);
        
        return {
            true,
            size,
            min(root->val, left.minVal),
            max(root->val, right.maxVal)
        };
    }
    
    return {false, 0, 0, 0};
}

int largestBSTSubtree(TreeNode* root) {
    largestBSTSize = 0;
    largestBSTHelper(root);
    return largestBSTSize;
}

// ==================== RECOVER BST (Two nodes swapped) ====================

void recoverTree(TreeNode* root) {
    TreeNode* first = nullptr;
    TreeNode* second = nullptr;
    TreeNode* prev = nullptr;
    
    // Inorder traversal to find swapped nodes
    function<void(TreeNode*)> inorder = [&](TreeNode* node) {
        if (!node) return;
        
        inorder(node->left);
        
        if (prev && prev->val > node->val) {
            if (!first) {
                first = prev;
            }
            second = node;
        }
        prev = node;
        
        inorder(node->right);
    };
    
    inorder(root);
    
    // Swap values
    if (first && second) {
        swap(first->val, second->val);
    }
}

// ==================== CHECK IF ARRAY CAN REPRESENT PREORDER OF BST ====================

bool canRepresentBST(vector<int>& preorder) {
    stack<int> st;
    int root = INT_MIN;
    
    for (int val : preorder) {
        // If we find a node greater than root, it's in right subtree
        // So all subsequent nodes must be greater than root
        if (val < root) {
            return false;
        }
        
        // Pop elements smaller than current
        while (!st.empty() && st.top() < val) {
            root = st.top();
            st.pop();
        }
        
        st.push(val);
    }
    
    return true;
}

// ==================== COUNT BST NODES IN RANGE ====================

int countInRange(TreeNode* root, int low, int high) {
    if (!root) return 0;
    
    if (root->val < low) {
        return countInRange(root->right, low, high);
    }
    
    if (root->val > high) {
        return countInRange(root->left, low, high);
    }
    
    return 1 + countInRange(root->left, low, high) + 
           countInRange(root->right, low, high);
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
    
    cout << "=== Binary Tree to BST Conversion ===" << endl;
    
    // Convert BT to BST (same structure)
    /*
        Original:
              10
            /    \
           2      7
          / \
         8   4
         
        After conversion (same structure):
              8
            /    \
           4      10
          / \
         2   7
    */
    vector<int> btNodes = {10, 2, 7, 8, 4};
    TreeNode* bt = buildTree(btNodes);
    
    cout << "\nOriginal BT inorder: ";
    printInorder(bt);
    cout << endl;
    
    BTtoBST converter;
    converter.convertToBST(bt);
    
    cout << "Converted BST inorder: ";
    printInorder(bt);
    cout << endl;
    
    // Merge two BSTs
    /*
        BST1:      BST2:
           3          6
          / \        / \
         1   5      2   8
    */
    vector<int> bst1Nodes = {3, 1, 5};
    vector<int> bst2Nodes = {6, 2, 8};
    TreeNode* bst1 = buildTree(bst1Nodes);
    TreeNode* bst2 = buildTree(bst2Nodes);
    
    TreeNode* merged = mergeBSTs(bst1, bst2);
    cout << "\nMerged BST inorder: ";
    printInorder(merged);
    cout << endl;
    
    // BST to Greater Sum Tree
    vector<int> gstNodes = {4, 1, 6, 0, 2, 5, 7, -1, -1, -1, 3, -1, -1, -1, 8};
    TreeNode* gst = buildTree(gstNodes);
    
    cout << "\nBST inorder before GST: ";
    printInorder(gst);
    cout << endl;
    
    bstToGST(gst);
    cout << "After GST conversion: ";
    printInorder(gst);
    cout << endl;
    
    // Largest BST in Binary Tree
    /*
              10
            /    \
           5      15
          / \       \
         1   8      7 (not BST here)
    */
    vector<int> mixedNodes = {10, 5, 15, 1, 8, -1, 7};
    TreeNode* mixed = buildTree(mixedNodes);
    
    cout << "\nLargest BST subtree size: " << largestBSTSubtree(mixed) << endl;
    
    // Check preorder
    vector<int> pre1 = {40, 30, 35, 80, 100};
    vector<int> pre2 = {40, 30, 35, 20, 80, 100};
    
    cout << "\nCan [40,30,35,80,100] be BST preorder: " 
         << (canRepresentBST(pre1) ? "Yes" : "No") << endl;
    cout << "Can [40,30,35,20,80,100] be BST preorder: " 
         << (canRepresentBST(pre2) ? "Yes" : "No") << endl;
    
    return 0;
}
















