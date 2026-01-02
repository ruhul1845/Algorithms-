/*
    Binary Search Tree (BST) Operations
    ====================================
    
    BST Property: For each node, all values in left subtree are smaller,
    and all values in right subtree are larger.
    
    Average Time Complexity: O(log n)
    Worst Time Complexity: O(n) for skewed tree
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

// ==================== SEARCH ====================

// Recursive search
TreeNode* searchBST(TreeNode* root, int val) {
    if (!root || root->val == val) return root;
    
    if (val < root->val) return searchBST(root->left, val);
    return searchBST(root->right, val);
}

// Iterative search
TreeNode* searchBSTIterative(TreeNode* root, int val) {
    while (root && root->val != val) {
        root = (val < root->val) ? root->left : root->right;
    }
    return root;
}

// ==================== INSERT ====================

// Recursive insert
TreeNode* insertBST(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    
    if (val < root->val) {
        root->left = insertBST(root->left, val);
    } else {
        root->right = insertBST(root->right, val);
    }
    
    return root;
}

// Iterative insert
TreeNode* insertBSTIterative(TreeNode* root, int val) {
    TreeNode* newNode = new TreeNode(val);
    if (!root) return newNode;
    
    TreeNode* curr = root;
    TreeNode* parent = nullptr;
    
    while (curr) {
        parent = curr;
        if (val < curr->val) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    
    if (val < parent->val) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    
    return root;
}

// ==================== DELETE ====================

// Find minimum value node
TreeNode* findMin(TreeNode* root) {
    while (root->left) root = root->left;
    return root;
}

// Find maximum value node
TreeNode* findMax(TreeNode* root) {
    while (root->right) root = root->right;
    return root;
}

// Recursive delete
TreeNode* deleteBST(TreeNode* root, int val) {
    if (!root) return nullptr;
    
    if (val < root->val) {
        root->left = deleteBST(root->left, val);
    } else if (val > root->val) {
        root->right = deleteBST(root->right, val);
    } else {
        // Node found - delete it
        
        // Case 1: Leaf node
        if (!root->left && !root->right) {
            delete root;
            return nullptr;
        }
        
        // Case 2: One child
        if (!root->left) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        if (!root->right) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        
        // Case 3: Two children
        // Replace with inorder successor (smallest in right subtree)
        TreeNode* successor = findMin(root->right);
        root->val = successor->val;
        root->right = deleteBST(root->right, successor->val);
    }
    
    return root;
}

// ==================== VALIDATION ====================

// Check if tree is valid BST
bool isValidBST(TreeNode* root, long minVal = LONG_MIN, long maxVal = LONG_MAX) {
    if (!root) return true;
    
    if (root->val <= minVal || root->val >= maxVal) return false;
    
    return isValidBST(root->left, minVal, root->val) && 
           isValidBST(root->right, root->val, maxVal);
}

// Using inorder traversal
bool isValidBSTInorder(TreeNode* root) {
    TreeNode* prev = nullptr;
    
    function<bool(TreeNode*)> inorder = [&](TreeNode* node) -> bool {
        if (!node) return true;
        
        if (!inorder(node->left)) return false;
        
        if (prev && prev->val >= node->val) return false;
        prev = node;
        
        return inorder(node->right);
    };
    
    return inorder(root);
}

// ==================== FIND OPERATIONS ====================

// Find Kth smallest element
int kthSmallest(TreeNode* root, int k) {
    int count = 0;
    int result = -1;
    
    function<void(TreeNode*)> inorder = [&](TreeNode* node) {
        if (!node || count >= k) return;
        
        inorder(node->left);
        count++;
        if (count == k) {
            result = node->val;
            return;
        }
        inorder(node->right);
    };
    
    inorder(root);
    return result;
}

// Find Kth largest element
int kthLargest(TreeNode* root, int k) {
    int count = 0;
    int result = -1;
    
    // Reverse inorder: right, root, left
    function<void(TreeNode*)> reverseInorder = [&](TreeNode* node) {
        if (!node || count >= k) return;
        
        reverseInorder(node->right);
        count++;
        if (count == k) {
            result = node->val;
            return;
        }
        reverseInorder(node->left);
    };
    
    reverseInorder(root);
    return result;
}

// Find floor (largest value <= target)
int floor(TreeNode* root, int target) {
    int floor = -1;
    
    while (root) {
        if (root->val == target) return target;
        
        if (root->val < target) {
            floor = root->val;
            root = root->right;
        } else {
            root = root->left;
        }
    }
    
    return floor;
}

// Find ceiling (smallest value >= target)
int ceiling(TreeNode* root, int target) {
    int ceil = -1;
    
    while (root) {
        if (root->val == target) return target;
        
        if (root->val > target) {
            ceil = root->val;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    
    return ceil;
}

// Find inorder successor
TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    TreeNode* successor = nullptr;
    
    while (root) {
        if (p->val >= root->val) {
            root = root->right;
        } else {
            successor = root;
            root = root->left;
        }
    }
    
    return successor;
}

// Find inorder predecessor
TreeNode* inorderPredecessor(TreeNode* root, TreeNode* p) {
    TreeNode* predecessor = nullptr;
    
    while (root) {
        if (p->val <= root->val) {
            root = root->left;
        } else {
            predecessor = root;
            root = root->right;
        }
    }
    
    return predecessor;
}

// ==================== RANGE OPERATIONS ====================

// Count nodes in range [low, high]
int countInRange(TreeNode* root, int low, int high) {
    if (!root) return 0;
    
    if (root->val < low) return countInRange(root->right, low, high);
    if (root->val > high) return countInRange(root->left, low, high);
    
    return 1 + countInRange(root->left, low, high) + 
           countInRange(root->right, low, high);
}

// Sum of nodes in range
int sumInRange(TreeNode* root, int low, int high) {
    if (!root) return 0;
    
    if (root->val < low) return sumInRange(root->right, low, high);
    if (root->val > high) return sumInRange(root->left, low, high);
    
    return root->val + sumInRange(root->left, low, high) + 
           sumInRange(root->right, low, high);
}

// Get all nodes in range
vector<int> getInRange(TreeNode* root, int low, int high) {
    vector<int> result;
    
    function<void(TreeNode*)> inorder = [&](TreeNode* node) {
        if (!node) return;
        
        if (node->val > low) inorder(node->left);
        if (node->val >= low && node->val <= high) {
            result.push_back(node->val);
        }
        if (node->val < high) inorder(node->right);
    };
    
    inorder(root);
    return result;
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
    
    /*
        BST structure:
              8
            /   \
           3     10
          / \      \
         1   6      14
            / \    /
           4   7  13
    */
    
    TreeNode* root = new TreeNode(8);
    root = insertBST(root, 3);
    root = insertBST(root, 10);
    root = insertBST(root, 1);
    root = insertBST(root, 6);
    root = insertBST(root, 14);
    root = insertBST(root, 4);
    root = insertBST(root, 7);
    root = insertBST(root, 13);
    
    cout << "=== Binary Search Tree Operations ===" << endl;
    cout << "BST Inorder: ";
    printInorder(root);
    cout << endl;
    
    // Search
    cout << "\nSearch 6: " << (searchBST(root, 6) ? "Found" : "Not Found") << endl;
    cout << "Search 5: " << (searchBST(root, 5) ? "Found" : "Not Found") << endl;
    
    // Validation
    cout << "\nIs valid BST: " << (isValidBST(root) ? "Yes" : "No") << endl;
    
    // Find operations
    cout << "\nMin value: " << findMin(root)->val << endl;
    cout << "Max value: " << findMax(root)->val << endl;
    cout << "3rd smallest: " << kthSmallest(root, 3) << endl;
    cout << "3rd largest: " << kthLargest(root, 3) << endl;
    
    cout << "\nFloor of 5: " << floor(root, 5) << endl;
    cout << "Ceiling of 5: " << ceiling(root, 5) << endl;
    cout << "Floor of 9: " << floor(root, 9) << endl;
    cout << "Ceiling of 9: " << ceiling(root, 9) << endl;
    
    // Range operations
    cout << "\nNodes in range [4, 10]: ";
    for (int x : getInRange(root, 4, 10)) cout << x << " ";
    cout << endl;
    cout << "Count in range [4, 10]: " << countInRange(root, 4, 10) << endl;
    cout << "Sum in range [4, 10]: " << sumInRange(root, 4, 10) << endl;
    
    // Delete
    cout << "\nDeleting 3:" << endl;
    root = deleteBST(root, 3);
    cout << "BST Inorder: ";
    printInorder(root);
    cout << endl;
    
    cout << "\nDeleting 8 (root):" << endl;
    root = deleteBST(root, 8);
    cout << "BST Inorder: ";
    printInorder(root);
    cout << endl;
    
    return 0;
}







