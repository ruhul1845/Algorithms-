/*
    Balanced Binary Tree
    ====================
    
    A height-balanced binary tree is defined as a binary tree in which
    the left and right subtrees of every node differ in height by no more than 1.
    
    Time Complexity: O(n)
    Space Complexity: O(h) where h is height of tree
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Method 1: O(n^2) - Naive approach
int height(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

bool isBalancedNaive(TreeNode* root) {
    if (!root) return true;
    
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    
    if (abs(leftHeight - rightHeight) > 1) return false;
    
    return isBalancedNaive(root->left) && isBalancedNaive(root->right);
}

// Method 2: O(n) - Optimized using single traversal
int checkBalance(TreeNode* root) {
    if (!root) return 0;
    
    int leftHeight = checkBalance(root->left);
    if (leftHeight == -1) return -1;
    
    int rightHeight = checkBalance(root->right);
    if (rightHeight == -1) return -1;
    
    if (abs(leftHeight - rightHeight) > 1) return -1;
    
    return 1 + max(leftHeight, rightHeight);
}

bool isBalanced(TreeNode* root) {
    return checkBalance(root) != -1;
}

// Method 3: Using pair to return both height and balance status
pair<bool, int> isBalancedHelper(TreeNode* root) {
    if (!root) return {true, 0};
    
    auto [leftBalanced, leftHeight] = isBalancedHelper(root->left);
    auto [rightBalanced, rightHeight] = isBalancedHelper(root->right);
    
    bool balanced = leftBalanced && rightBalanced && 
                    abs(leftHeight - rightHeight) <= 1;
    int height = 1 + max(leftHeight, rightHeight);
    
    return {balanced, height};
}

// Convert unbalanced tree to balanced BST
vector<int> inorder;

void getInorder(TreeNode* root) {
    if (!root) return;
    getInorder(root->left);
    inorder.push_back(root->val);
    getInorder(root->right);
}

TreeNode* buildBalancedBST(int left, int right) {
    if (left > right) return nullptr;
    
    int mid = left + (right - left) / 2;
    TreeNode* root = new TreeNode(inorder[mid]);
    root->left = buildBalancedBST(left, mid - 1);
    root->right = buildBalancedBST(mid + 1, right);
    
    return root;
}

TreeNode* balanceBST(TreeNode* root) {
    inorder.clear();
    getInorder(root);
    return buildBalancedBST(0, inorder.size() - 1);
}

// Build balanced BST from sorted array
TreeNode* sortedArrayToBST(vector<int>& nums, int left, int right) {
    if (left > right) return nullptr;
    
    int mid = left + (right - left) / 2;
    TreeNode* root = new TreeNode(nums[mid]);
    root->left = sortedArrayToBST(nums, left, mid - 1);
    root->right = sortedArrayToBST(nums, mid + 1, right);
    
    return root;
}

TreeNode* sortedArrayToBST(vector<int>& nums) {
    return sortedArrayToBST(nums, 0, nums.size() - 1);
}

// Build balanced BST from sorted linked list
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* findMiddle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    ListNode* prev = nullptr;
    
    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    
    if (prev) prev->next = nullptr;
    
    return slow;
}

TreeNode* sortedListToBST(ListNode* head) {
    if (!head) return nullptr;
    if (!head->next) return new TreeNode(head->val);
    
    ListNode* mid = findMiddle(head);
    TreeNode* root = new TreeNode(mid->val);
    
    root->left = sortedListToBST(head);
    root->right = sortedListToBST(mid->next);
    
    return root;
}

// Get balance factor of each node
void getBalanceFactors(TreeNode* root, vector<pair<int, int>>& factors) {
    if (!root) return;
    
    int leftH = height(root->left);
    int rightH = height(root->right);
    factors.push_back({root->val, leftH - rightH});
    
    getBalanceFactors(root->left, factors);
    getBalanceFactors(root->right, factors);
}

// Find all unbalanced nodes
vector<int> findUnbalancedNodes(TreeNode* root) {
    vector<int> unbalanced;
    
    function<int(TreeNode*)> checkHeight = [&](TreeNode* node) -> int {
        if (!node) return 0;
        
        int leftH = checkHeight(node->left);
        int rightH = checkHeight(node->right);
        
        if (abs(leftH - rightH) > 1) {
            unbalanced.push_back(node->val);
        }
        
        return 1 + max(leftH, rightH);
    };
    
    checkHeight(root);
    return unbalanced;
}

// Minimum number of nodes to add to make tree balanced
int minNodesToBalance(TreeNode* root) {
    // This is a complex problem - simplified version
    // Just returns height difference as an indicator
    if (!root) return 0;
    
    int leftH = height(root->left);
    int rightH = height(root->right);
    
    return abs(leftH - rightH) + minNodesToBalance(root->left) + 
           minNodesToBalance(root->right);
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
    
    // Balanced tree
    /*
              1
            /   \
           2     3
          / \   / \
         4   5 6   7
    */
    vector<int> balanced = {1, 2, 3, 4, 5, 6, 7};
    TreeNode* root1 = buildTree(balanced);
    
    // Unbalanced tree
    /*
              1
            /
           2
          /
         3
        /
       4
    */
    vector<int> unbalanced = {1, 2, -1, 3, -1, 4};
    TreeNode* root2 = buildTree(unbalanced);
    
    cout << "=== Balanced Binary Tree ===" << endl;
    
    cout << "Tree 1 (balanced):" << endl;
    cout << "  Is balanced (naive): " << (isBalancedNaive(root1) ? "Yes" : "No") << endl;
    cout << "  Is balanced (optimized): " << (isBalanced(root1) ? "Yes" : "No") << endl;
    
    cout << "\nTree 2 (unbalanced):" << endl;
    cout << "  Is balanced (naive): " << (isBalancedNaive(root2) ? "Yes" : "No") << endl;
    cout << "  Is balanced (optimized): " << (isBalanced(root2) ? "Yes" : "No") << endl;
    
    // Balance factors
    vector<pair<int, int>> factors;
    getBalanceFactors(root2, factors);
    cout << "\nBalance factors of Tree 2:" << endl;
    for (auto& [val, factor] : factors) {
        cout << "  Node " << val << ": " << factor << endl;
    }
    
    // Unbalanced nodes
    cout << "\nUnbalanced nodes in Tree 2: ";
    for (int x : findUnbalancedNodes(root2)) cout << x << " ";
    cout << endl;
    
    // Convert unbalanced BST to balanced BST
    // Create a simple unbalanced BST
    TreeNode* bst = new TreeNode(1);
    bst->right = new TreeNode(2);
    bst->right->right = new TreeNode(3);
    bst->right->right->right = new TreeNode(4);
    bst->right->right->right->right = new TreeNode(5);
    
    cout << "\nUnbalanced BST inorder: ";
    printInorder(bst);
    cout << endl;
    
    TreeNode* balancedBST = balanceBST(bst);
    cout << "Balanced BST inorder: ";
    printInorder(balancedBST);
    cout << "\nIs now balanced: " << (isBalanced(balancedBST) ? "Yes" : "No") << endl;
    
    // Build balanced BST from sorted array
    vector<int> sortedArr = {1, 2, 3, 4, 5, 6, 7};
    TreeNode* fromArray = sortedArrayToBST(sortedArr);
    cout << "\nBalanced BST from sorted array [1..7]:" << endl;
    cout << "  Inorder: ";
    printInorder(fromArray);
    cout << "\n  Is balanced: " << (isBalanced(fromArray) ? "Yes" : "No") << endl;
    
    return 0;
}





