/*
    Mirror and Symmetric Tree Problems
    ===================================
    
    Problems related to mirroring, symmetric check, and inversions.
    
    Time Complexity: O(n)
    Space Complexity: O(h)
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Check if two trees are mirror of each other
bool isMirror(TreeNode* t1, TreeNode* t2) {
    if (!t1 && !t2) return true;
    if (!t1 || !t2) return false;
    
    return (t1->val == t2->val) &&
           isMirror(t1->left, t2->right) &&
           isMirror(t1->right, t2->left);
}

// Check if tree is symmetric (mirror of itself)
bool isSymmetric(TreeNode* root) {
    if (!root) return true;
    return isMirror(root->left, root->right);
}

// Iterative symmetric check
bool isSymmetricIterative(TreeNode* root) {
    if (!root) return true;
    
    queue<TreeNode*> q;
    q.push(root->left);
    q.push(root->right);
    
    while (!q.empty()) {
        TreeNode* t1 = q.front(); q.pop();
        TreeNode* t2 = q.front(); q.pop();
        
        if (!t1 && !t2) continue;
        if (!t1 || !t2) return false;
        if (t1->val != t2->val) return false;
        
        q.push(t1->left);
        q.push(t2->right);
        q.push(t1->right);
        q.push(t2->left);
    }
    
    return true;
}

// Invert/Mirror a binary tree
TreeNode* invertTree(TreeNode* root) {
    if (!root) return nullptr;
    
    swap(root->left, root->right);
    
    invertTree(root->left);
    invertTree(root->right);
    
    return root;
}

// Iterative invert
TreeNode* invertTreeIterative(TreeNode* root) {
    if (!root) return nullptr;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();
        
        swap(curr->left, curr->right);
        
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
    
    return root;
}

// Check if two trees are identical
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;
    if (!p || !q) return false;
    
    return (p->val == q->val) &&
           isSameTree(p->left, q->left) &&
           isSameTree(p->right, q->right);
}

// Check if tree is subtree of another
bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    if (!root) return false;
    if (isSameTree(root, subRoot)) return true;
    
    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}

// Flip equivalent trees
bool flipEquiv(TreeNode* root1, TreeNode* root2) {
    if (!root1 && !root2) return true;
    if (!root1 || !root2) return false;
    if (root1->val != root2->val) return false;
    
    return (flipEquiv(root1->left, root2->left) && 
            flipEquiv(root1->right, root2->right)) ||
           (flipEquiv(root1->left, root2->right) && 
            flipEquiv(root1->right, root2->left));
}

// Create mirror copy of tree
TreeNode* mirrorCopy(TreeNode* root) {
    if (!root) return nullptr;
    
    TreeNode* newNode = new TreeNode(root->val);
    newNode->left = mirrorCopy(root->right);
    newNode->right = mirrorCopy(root->left);
    
    return newNode;
}

// Check if tree is foldable (can be folded around root)
bool isFoldable(TreeNode* root) {
    if (!root) return true;
    
    function<bool(TreeNode*, TreeNode*)> checkFoldable = 
        [&](TreeNode* left, TreeNode* right) -> bool {
        if (!left && !right) return true;
        if (!left || !right) return false;
        
        return checkFoldable(left->left, right->right) &&
               checkFoldable(left->right, right->left);
    };
    
    return checkFoldable(root->left, root->right);
}

// Count symmetric nodes
int countSymmetricNodes(TreeNode* root) {
    int count = 0;
    
    function<bool(TreeNode*, TreeNode*)> isMirrorSubtree = 
        [&](TreeNode* t1, TreeNode* t2) -> bool {
        if (!t1 && !t2) return true;
        if (!t1 || !t2) return false;
        
        return (t1->val == t2->val) &&
               isMirrorSubtree(t1->left, t2->right) &&
               isMirrorSubtree(t1->right, t2->left);
    };
    
    function<void(TreeNode*)> dfs = [&](TreeNode* node) {
        if (!node) return;
        
        if (isMirrorSubtree(node->left, node->right)) {
            count++;
        }
        
        dfs(node->left);
        dfs(node->right);
    };
    
    dfs(root);
    return count;
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
    
    // Symmetric tree
    /*
          1
        /   \
       2     2
      / \   / \
     3   4 4   3
    */
    vector<int> symNodes = {1, 2, 2, 3, 4, 4, 3};
    TreeNode* symRoot = buildTree(symNodes);
    
    // Non-symmetric tree
    /*
          1
        /   \
       2     2
        \     \
         3     3
    */
    vector<int> asymNodes = {1, 2, 2, -1, 3, -1, 3};
    TreeNode* asymRoot = buildTree(asymNodes);
    
    cout << "=== Mirror and Symmetric Tree ===" << endl;
    
    cout << "\nSymmetric tree check:" << endl;
    cout << "  Tree 1 is symmetric: " << (isSymmetric(symRoot) ? "Yes" : "No") << endl;
    cout << "  Tree 2 is symmetric: " << (isSymmetric(asymRoot) ? "Yes" : "No") << endl;
    
    // Invert tree
    /*
          4
        /   \
       2     7
      / \   / \
     1   3 6   9
    */
    vector<int> nodes = {4, 2, 7, 1, 3, 6, 9};
    TreeNode* root = buildTree(nodes);
    
    cout << "\nOriginal tree inorder: ";
    printInorder(root);
    cout << endl;
    
    TreeNode* inverted = invertTree(root);
    cout << "Inverted tree inorder: ";
    printInorder(inverted);
    cout << endl;
    
    // Same tree check
    vector<int> nodes1 = {1, 2, 3};
    vector<int> nodes2 = {1, 2, 3};
    TreeNode* t1 = buildTree(nodes1);
    TreeNode* t2 = buildTree(nodes2);
    
    cout << "\nAre trees [1,2,3] and [1,2,3] same: " 
         << (isSameTree(t1, t2) ? "Yes" : "No") << endl;
    
    // Subtree check
    /*
        Main tree:
              3
            /   \
           4     5
          / \
         1   2
        
        Subtree:
           4
          / \
         1   2
    */
    vector<int> mainNodes = {3, 4, 5, 1, 2};
    vector<int> subNodes = {4, 1, 2};
    TreeNode* mainTree = buildTree(mainNodes);
    TreeNode* subTree = buildTree(subNodes);
    
    cout << "Is [4,1,2] subtree of [3,4,5,1,2]: " 
         << (isSubtree(mainTree, subTree) ? "Yes" : "No") << endl;
    
    // Foldable tree check
    cout << "\nIs symmetric tree foldable: " 
         << (isFoldable(symRoot) ? "Yes" : "No") << endl;
    
    return 0;
}

