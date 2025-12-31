/*
    AVL Tree (Self-Balancing BST)
    =============================
    
    AVL Tree is a self-balancing Binary Search Tree where the difference
    between heights of left and right subtrees cannot be more than one.
    
    Balance Factor = Height(Left Subtree) - Height(Right Subtree)
    Valid Balance Factor: -1, 0, +1
    
    Time Complexity: O(log n) for all operations
    Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

struct AVLNode {
    int val;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(int x) : val(x), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;
    
    int height(AVLNode* node) {
        return node ? node->height : 0;
    }
    
    int getBalance(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }
    
    void updateHeight(AVLNode* node) {
        node->height = 1 + max(height(node->left), height(node->right));
    }
    
    // Right rotation
    //      y                x
    //     / \              / \
    //    x   T3    ->     T1  y
    //   / \                  / \
    //  T1  T2               T2  T3
    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        updateHeight(y);
        updateHeight(x);
        
        return x;
    }
    
    // Left rotation
    //    x                   y
    //   / \                 / \
    //  T1  y       ->      x   T3
    //     / \             / \
    //    T2  T3          T1  T2
    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        updateHeight(x);
        updateHeight(y);
        
        return y;
    }
    
    AVLNode* balance(AVLNode* node) {
        updateHeight(node);
        
        int bf = getBalance(node);
        
        // Left Left Case
        if (bf > 1 && getBalance(node->left) >= 0) {
            return rightRotate(node);
        }
        
        // Left Right Case
        if (bf > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        
        // Right Right Case
        if (bf < -1 && getBalance(node->right) <= 0) {
            return leftRotate(node);
        }
        
        // Right Left Case
        if (bf < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }
    
    AVLNode* insertHelper(AVLNode* node, int val) {
        if (!node) return new AVLNode(val);
        
        if (val < node->val) {
            node->left = insertHelper(node->left, val);
        } else if (val > node->val) {
            node->right = insertHelper(node->right, val);
        } else {
            return node; // Duplicate not allowed
        }
        
        return balance(node);
    }
    
    AVLNode* findMin(AVLNode* node) {
        while (node->left) node = node->left;
        return node;
    }
    
    AVLNode* deleteHelper(AVLNode* node, int val) {
        if (!node) return nullptr;
        
        if (val < node->val) {
            node->left = deleteHelper(node->left, val);
        } else if (val > node->val) {
            node->right = deleteHelper(node->right, val);
        } else {
            // Node found
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;
                if (!temp) {
                    delete node;
                    return nullptr;
                }
                *node = *temp;
                delete temp;
            } else {
                AVLNode* successor = findMin(node->right);
                node->val = successor->val;
                node->right = deleteHelper(node->right, successor->val);
            }
        }
        
        return balance(node);
    }
    
    bool searchHelper(AVLNode* node, int val) {
        if (!node) return false;
        if (val == node->val) return true;
        if (val < node->val) return searchHelper(node->left, val);
        return searchHelper(node->right, val);
    }
    
    void inorderHelper(AVLNode* node, vector<int>& result) {
        if (!node) return;
        inorderHelper(node->left, result);
        result.push_back(node->val);
        inorderHelper(node->right, result);
    }
    
    void preorderHelper(AVLNode* node, vector<int>& result) {
        if (!node) return;
        result.push_back(node->val);
        preorderHelper(node->left, result);
        preorderHelper(node->right, result);
    }
    
    void printTreeHelper(AVLNode* node, string prefix, bool isLeft) {
        if (!node) return;
        
        cout << prefix;
        cout << (isLeft ? "├──" : "└──");
        cout << node->val << " (bf=" << getBalance(node) << ")" << endl;
        
        printTreeHelper(node->left, prefix + (isLeft ? "│   " : "    "), true);
        printTreeHelper(node->right, prefix + (isLeft ? "│   " : "    "), false);
    }
    
public:
    AVLTree() : root(nullptr) {}
    
    void insert(int val) {
        root = insertHelper(root, val);
    }
    
    void remove(int val) {
        root = deleteHelper(root, val);
    }
    
    bool search(int val) {
        return searchHelper(root, val);
    }
    
    vector<int> inorder() {
        vector<int> result;
        inorderHelper(root, result);
        return result;
    }
    
    vector<int> preorder() {
        vector<int> result;
        preorderHelper(root, result);
        return result;
    }
    
    int getHeight() {
        return height(root);
    }
    
    void printTree() {
        printTreeHelper(root, "", false);
    }
    
    int findMinVal() {
        if (!root) return INT_MIN;
        AVLNode* curr = root;
        while (curr->left) curr = curr->left;
        return curr->val;
    }
    
    int findMaxVal() {
        if (!root) return INT_MAX;
        AVLNode* curr = root;
        while (curr->right) curr = curr->right;
        return curr->val;
    }
    
    // Count nodes
    int countNodes() {
        function<int(AVLNode*)> count = [&](AVLNode* node) -> int {
            if (!node) return 0;
            return 1 + count(node->left) + count(node->right);
        };
        return count(root);
    }
    
    // Kth smallest
    int kthSmallest(int k) {
        int count = 0;
        int result = -1;
        
        function<void(AVLNode*)> inorder = [&](AVLNode* node) {
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
};

// Convert sorted array to AVL Tree
AVLNode* sortedArrayToAVL(vector<int>& nums, int left, int right) {
    if (left > right) return nullptr;
    
    int mid = left + (right - left) / 2;
    AVLNode* node = new AVLNode(nums[mid]);
    
    node->left = sortedArrayToAVL(nums, left, mid - 1);
    node->right = sortedArrayToAVL(nums, mid + 1, right);
    
    node->height = 1 + max(
        node->left ? node->left->height : 0,
        node->right ? node->right->height : 0
    );
    
    return node;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << "=== AVL Tree ===" << endl;
    
    AVLTree avl;
    
    // Insert elements
    vector<int> elements = {10, 20, 30, 40, 50, 25};
    
    cout << "\nInserting: ";
    for (int x : elements) {
        cout << x << " ";
        avl.insert(x);
    }
    cout << endl;
    
    cout << "\nTree structure:" << endl;
    avl.printTree();
    
    cout << "\nInorder: ";
    for (int x : avl.inorder()) cout << x << " ";
    cout << endl;
    
    cout << "Preorder: ";
    for (int x : avl.preorder()) cout << x << " ";
    cout << endl;
    
    cout << "\nTree height: " << avl.getHeight() << endl;
    cout << "Node count: " << avl.countNodes() << endl;
    cout << "Min value: " << avl.findMinVal() << endl;
    cout << "Max value: " << avl.findMaxVal() << endl;
    cout << "3rd smallest: " << avl.kthSmallest(3) << endl;
    
    // Search
    cout << "\nSearch 25: " << (avl.search(25) ? "Found" : "Not Found") << endl;
    cout << "Search 15: " << (avl.search(15) ? "Found" : "Not Found") << endl;
    
    // Delete
    cout << "\nDeleting 30:" << endl;
    avl.remove(30);
    avl.printTree();
    
    cout << "\nDeleting 20:" << endl;
    avl.remove(20);
    avl.printTree();
    
    // Insert more to show rebalancing
    cout << "\nInserting 35, 28, 27:" << endl;
    avl.insert(35);
    avl.insert(28);
    avl.insert(27);
    avl.printTree();
    
    cout << "\nFinal inorder: ";
    for (int x : avl.inorder()) cout << x << " ";
    cout << endl;
    
    return 0;
}

