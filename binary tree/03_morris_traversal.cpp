/*
    Morris Traversal
    ================
    
    Morris Traversal is a way to traverse a binary tree without using stack or recursion.
    It uses the concept of Threaded Binary Trees.
    
    Key Idea: Use the right pointer of inorder predecessor to point to the current node,
    creating temporary links that are later removed.
    
    Time Complexity: O(n)
    Space Complexity: O(1) - No extra space for stack/recursion
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Morris Inorder Traversal
// Time: O(n), Space: O(1)
vector<int> morrisInorder(TreeNode* root) {
    vector<int> result;
    TreeNode* curr = root;
    
    while (curr) {
        if (!curr->left) {
            // No left subtree, visit current and go right
            result.push_back(curr->val);
            curr = curr->right;
        } else {
            // Find inorder predecessor (rightmost node in left subtree)
            TreeNode* pred = curr->left;
            while (pred->right && pred->right != curr) {
                pred = pred->right;
            }
            
            if (!pred->right) {
                // Create thread: predecessor's right points to current
                pred->right = curr;
                curr = curr->left;
            } else {
                // Thread exists, remove it and visit current
                pred->right = nullptr;
                result.push_back(curr->val);
                curr = curr->right;
            }
        }
    }
    
    return result;
}

// Morris Preorder Traversal
// Time: O(n), Space: O(1)
vector<int> morrisPreorder(TreeNode* root) {
    vector<int> result;
    TreeNode* curr = root;
    
    while (curr) {
        if (!curr->left) {
            // No left subtree, visit current and go right
            result.push_back(curr->val);
            curr = curr->right;
        } else {
            // Find inorder predecessor
            TreeNode* pred = curr->left;
            while (pred->right && pred->right != curr) {
                pred = pred->right;
            }
            
            if (!pred->right) {
                // Create thread and VISIT CURRENT before going left
                result.push_back(curr->val);  // Visit before going left (preorder)
                pred->right = curr;
                curr = curr->left;
            } else {
                // Thread exists, remove it
                pred->right = nullptr;
                curr = curr->right;
            }
        }
    }
    
    return result;
}

// Morris Postorder Traversal
// Time: O(n), Space: O(1) - but result vector is O(n)
vector<int> morrisPostorder(TreeNode* root) {
    vector<int> result;
    
    // Create a dummy node whose left child is root
    TreeNode dummy(0);
    dummy.left = root;
    TreeNode* curr = &dummy;
    
    auto reverseAdd = [&](TreeNode* from, TreeNode* to) {
        vector<int> temp;
        while (from != to) {
            temp.push_back(from->val);
            from = from->right;
        }
        temp.push_back(to->val);
        reverse(temp.begin(), temp.end());
        for (int x : temp) result.push_back(x);
    };
    
    while (curr) {
        if (!curr->left) {
            curr = curr->right;
        } else {
            TreeNode* pred = curr->left;
            while (pred->right && pred->right != curr) {
                pred = pred->right;
            }
            
            if (!pred->right) {
                pred->right = curr;
                curr = curr->left;
            } else {
                // Add nodes from curr->left to pred in reverse order
                reverseAdd(curr->left, pred);
                pred->right = nullptr;
                curr = curr->right;
            }
        }
    }
    
    return result;
}

// Flatten Binary Tree to Linked List using Morris approach
// In-place, O(1) space
void flatten(TreeNode* root) {
    TreeNode* curr = root;
    
    while (curr) {
        if (curr->left) {
            // Find rightmost node in left subtree
            TreeNode* pred = curr->left;
            while (pred->right) {
                pred = pred->right;
            }
            
            // Connect rightmost to curr's right subtree
            pred->right = curr->right;
            
            // Move left subtree to right
            curr->right = curr->left;
            curr->left = nullptr;
        }
        curr = curr->right;
    }
}

// Count nodes using Morris Traversal - O(n) time, O(1) space
int countNodes(TreeNode* root) {
    int count = 0;
    TreeNode* curr = root;
    
    while (curr) {
        if (!curr->left) {
            count++;
            curr = curr->right;
        } else {
            TreeNode* pred = curr->left;
            while (pred->right && pred->right != curr) {
                pred = pred->right;
            }
            
            if (!pred->right) {
                pred->right = curr;
                curr = curr->left;
            } else {
                pred->right = nullptr;
                count++;
                curr = curr->right;
            }
        }
    }
    
    return count;
}

// Find Kth smallest element using Morris - O(n) time, O(1) space
int kthSmallest(TreeNode* root, int k) {
    TreeNode* curr = root;
    int count = 0;
    
    while (curr) {
        if (!curr->left) {
            count++;
            if (count == k) return curr->val;
            curr = curr->right;
        } else {
            TreeNode* pred = curr->left;
            while (pred->right && pred->right != curr) {
                pred = pred->right;
            }
            
            if (!pred->right) {
                pred->right = curr;
                curr = curr->left;
            } else {
                pred->right = nullptr;
                count++;
                if (count == k) return curr->val;
                curr = curr->right;
            }
        }
    }
    
    return -1; // k is larger than tree size
}

// Check if BST using Morris - O(n) time, O(1) space
bool isBST(TreeNode* root) {
    TreeNode* curr = root;
    TreeNode* prev = nullptr;
    
    while (curr) {
        if (!curr->left) {
            if (prev && prev->val >= curr->val) return false;
            prev = curr;
            curr = curr->right;
        } else {
            TreeNode* pred = curr->left;
            while (pred->right && pred->right != curr) {
                pred = pred->right;
            }
            
            if (!pred->right) {
                pred->right = curr;
                curr = curr->left;
            } else {
                pred->right = nullptr;
                if (prev && prev->val >= curr->val) return false;
                prev = curr;
                curr = curr->right;
            }
        }
    }
    
    return true;
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

void printVector(const vector<int>& v, const string& name) {
    cout << name << ": ";
    for (int x : v) cout << x << " ";
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    /*
        Tree structure (BST):
              4
            /   \
           2     6
          / \   / \
         1   3 5   7
    */
    
    vector<int> nodes = {4, 2, 6, 1, 3, 5, 7};
    TreeNode* root = buildTree(nodes);
    
    cout << "=== Morris Traversal (O(1) Space) ===" << endl;
    printVector(morrisInorder(root), "Morris Inorder");
    printVector(morrisPreorder(root), "Morris Preorder");
    printVector(morrisPostorder(root), "Morris Postorder");
    
    cout << "\nTotal nodes: " << countNodes(root) << endl;
    cout << "Is BST: " << (isBST(root) ? "Yes" : "No") << endl;
    cout << "3rd smallest element: " << kthSmallest(root, 3) << endl;
    
    // Flatten tree demonstration
    vector<int> nodes2 = {1, 2, 5, 3, 4, -1, 6};
    TreeNode* root2 = buildTree(nodes2);
    
    cout << "\nBefore Flatten (Preorder): ";
    for (int x : morrisPreorder(root2)) cout << x << " ";
    cout << endl;
    
    flatten(root2);
    
    cout << "After Flatten (Linked List): ";
    TreeNode* curr = root2;
    while (curr) {
        cout << curr->val << " -> ";
        curr = curr->right;
    }
    cout << "NULL" << endl;
    
    return 0;
}







