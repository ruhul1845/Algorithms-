/*
    Flatten Binary Tree
    ===================
    
    Convert binary tree to different linked list structures.
    
    Time Complexity: O(n)
    Space Complexity: O(1) for iterative, O(h) for recursive
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Flatten to linked list (preorder) - Recursive
void flattenPreorderRecursive(TreeNode* root) {
    if (!root) return;
    
    flattenPreorderRecursive(root->left);
    flattenPreorderRecursive(root->right);
    
    TreeNode* rightSubtree = root->right;
    root->right = root->left;
    root->left = nullptr;
    
    TreeNode* curr = root;
    while (curr->right) curr = curr->right;
    curr->right = rightSubtree;
}

// Flatten to linked list (preorder) - Morris-like O(1) space
void flattenPreorderMorris(TreeNode* root) {
    TreeNode* curr = root;
    
    while (curr) {
        if (curr->left) {
            // Find rightmost node in left subtree
            TreeNode* pred = curr->left;
            while (pred->right) {
                pred = pred->right;
            }
            
            pred->right = curr->right;
            curr->right = curr->left;
            curr->left = nullptr;
        }
        curr = curr->right;
    }
}

// Flatten to linked list (preorder) - Iterative with stack
void flattenPreorderStack(TreeNode* root) {
    if (!root) return;
    
    stack<TreeNode*> st;
    st.push(root);
    
    while (!st.empty()) {
        TreeNode* curr = st.top();
        st.pop();
        
        if (curr->right) st.push(curr->right);
        if (curr->left) st.push(curr->left);
        
        if (!st.empty()) {
            curr->right = st.top();
        }
        curr->left = nullptr;
    }
}

// Flatten to linked list in inorder
TreeNode* flattenInorderHelper(TreeNode* root, TreeNode* prev) {
    if (!root) return prev;
    
    prev = flattenInorderHelper(root->left, prev);
    
    root->left = nullptr;
    if (prev) prev->right = root;
    prev = root;
    
    return flattenInorderHelper(root->right, prev);
}

TreeNode* flattenInorder(TreeNode* root) {
    if (!root) return nullptr;
    
    // Find leftmost node (will be head)
    TreeNode* head = root;
    while (head->left) head = head->left;
    
    flattenInorderHelper(root, nullptr);
    
    return head;
}

// Convert to Doubly Linked List (DLL) - Circular
TreeNode* prev_dll = nullptr;
TreeNode* head_dll = nullptr;

void treeToDLLHelper(TreeNode* root) {
    if (!root) return;
    
    treeToDLLHelper(root->left);
    
    if (prev_dll) {
        prev_dll->right = root;
        root->left = prev_dll;
    } else {
        head_dll = root;
    }
    prev_dll = root;
    
    treeToDLLHelper(root->right);
}

TreeNode* treeToDLL(TreeNode* root) {
    prev_dll = nullptr;
    head_dll = nullptr;
    
    treeToDLLHelper(root);
    
    // Make circular
    if (head_dll && prev_dll) {
        head_dll->left = prev_dll;
        prev_dll->right = head_dll;
    }
    
    return head_dll;
}

// Convert to Doubly Linked List (non-circular)
pair<TreeNode*, TreeNode*> treeToDLLNonCircular(TreeNode* root) {
    if (!root) return {nullptr, nullptr};
    
    auto [leftHead, leftTail] = treeToDLLNonCircular(root->left);
    auto [rightHead, rightTail] = treeToDLLNonCircular(root->right);
    
    root->left = leftTail;
    root->right = rightHead;
    
    if (leftTail) leftTail->right = root;
    if (rightHead) rightHead->left = root;
    
    TreeNode* head = leftHead ? leftHead : root;
    TreeNode* tail = rightTail ? rightTail : root;
    
    return {head, tail};
}

// Convert BST to sorted DLL
TreeNode* bstToDLL(TreeNode* root) {
    if (!root) return nullptr;
    
    TreeNode* head = nullptr;
    TreeNode* prev = nullptr;
    
    function<void(TreeNode*)> convert = [&](TreeNode* node) {
        if (!node) return;
        
        convert(node->left);
        
        if (!prev) {
            head = node;
        } else {
            prev->right = node;
            node->left = prev;
        }
        prev = node;
        
        convert(node->right);
    };
    
    convert(root);
    return head;
}

// Flatten to separate linked list
ListNode* treeToList(TreeNode* root) {
    if (!root) return nullptr;
    
    ListNode* dummy = new ListNode(0);
    ListNode* curr = dummy;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        
        curr->next = new ListNode(node->val);
        curr = curr->next;
        
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
    
    return dummy->next;
}

// Unflatten - convert flattened tree back (requires original structure info)
// This requires knowing the structure, usually done with serialization

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

void printFlattenedTree(TreeNode* root) {
    while (root) {
        cout << root->val;
        if (root->right) cout << " -> ";
        root = root->right;
    }
    cout << endl;
}

void printDLL(TreeNode* head) {
    TreeNode* curr = head;
    cout << "Forward: ";
    while (curr) {
        cout << curr->val;
        if (curr->right && curr->right != head) cout << " <-> ";
        else break;
        curr = curr->right;
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    /*
              1
            /   \
           2     5
          / \     \
         3   4     6
    */
    
    cout << "=== Flatten Binary Tree ===" << endl;
    
    // Flatten to preorder linked list
    vector<int> nodes1 = {1, 2, 5, 3, 4, -1, 6};
    TreeNode* root1 = buildTree(nodes1);
    
    cout << "\nOriginal tree: 1 -> 2 -> 3, 4 and 1 -> 5 -> 6" << endl;
    
    flattenPreorderMorris(root1);
    cout << "Flattened (preorder): ";
    printFlattenedTree(root1);
    
    // Using recursive method
    vector<int> nodes2 = {1, 2, 5, 3, 4, -1, 6};
    TreeNode* root2 = buildTree(nodes2);
    flattenPreorderRecursive(root2);
    cout << "Flattened (recursive): ";
    printFlattenedTree(root2);
    
    // BST to sorted DLL
    /*
        BST:
              4
            /   \
           2     5
          / \     \
         1   3     6
    */
    vector<int> bstNodes = {4, 2, 5, 1, 3, -1, 6};
    TreeNode* bst = buildTree(bstNodes);
    
    TreeNode* dll = bstToDLL(bst);
    cout << "\nBST to sorted DLL:" << endl;
    printDLL(dll);
    
    // Flatten inorder
    vector<int> nodes3 = {1, 2, 5, 3, 4, -1, 6};
    TreeNode* root3 = buildTree(nodes3);
    TreeNode* inorderFlat = flattenInorder(root3);
    cout << "\nFlattened (inorder): ";
    printFlattenedTree(inorderFlat);
    
    return 0;
}

