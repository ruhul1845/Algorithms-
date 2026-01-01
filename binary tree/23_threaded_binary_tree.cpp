/*
    Threaded Binary Tree
    ====================
    
    A threaded binary tree is a variant where null pointers are replaced
    with pointers to inorder predecessor (left thread) or successor (right thread).
    
    Advantages:
    - Inorder traversal without stack or recursion
    - Faster traversal
    - No wasted null pointers
    
    Time Complexity: O(n) for traversal
    Space Complexity: O(1) for traversal
*/

#include <bits/stdc++.h>
using namespace std;

// Single Threaded (right threads only)
struct ThreadedNode {
    int val;
    ThreadedNode* left;
    ThreadedNode* right;
    bool rightThread;  // true if right points to successor
    
    ThreadedNode(int x) : val(x), left(nullptr), right(nullptr), rightThread(false) {}
};

// Double Threaded
struct DoubleThreadedNode {
    int val;
    DoubleThreadedNode* left;
    DoubleThreadedNode* right;
    bool leftThread;   // true if left points to predecessor
    bool rightThread;  // true if right points to successor
    
    DoubleThreadedNode(int x) : val(x), left(nullptr), right(nullptr), 
                                 leftThread(false), rightThread(false) {}
};

// ==================== SINGLE THREADED TREE ====================

class SingleThreadedTree {
    ThreadedNode* root;
    
    // Find inorder successor
    ThreadedNode* inorderSuccessor(ThreadedNode* node) {
        if (node->rightThread) {
            return node->right;
        }
        
        ThreadedNode* curr = node->right;
        while (curr && !curr->leftThread && curr->left) {
            curr = curr->left;
        }
        return curr;
    }
    
public:
    SingleThreadedTree() : root(nullptr) {}
    
    // Insert node (BST insert with threading)
    void insert(int val) {
        ThreadedNode* newNode = new ThreadedNode(val);
        
        if (!root) {
            root = newNode;
            return;
        }
        
        ThreadedNode* curr = root;
        ThreadedNode* parent = nullptr;
        
        while (curr) {
            parent = curr;
            
            if (val < curr->val) {
                if (curr->left) {
                    curr = curr->left;
                } else {
                    break;
                }
            } else {
                if (!curr->rightThread && curr->right) {
                    curr = curr->right;
                } else {
                    break;
                }
            }
        }
        
        if (val < parent->val) {
            parent->left = newNode;
            newNode->right = parent;
            newNode->rightThread = true;
        } else {
            newNode->right = parent->right;
            newNode->rightThread = parent->rightThread;
            parent->right = newNode;
            parent->rightThread = false;
        }
    }
    
    // Inorder traversal without recursion/stack
    vector<int> inorder() {
        vector<int> result;
        
        if (!root) return result;
        
        // Find leftmost node
        ThreadedNode* curr = root;
        while (curr->left) {
            curr = curr->left;
        }
        
        while (curr) {
            result.push_back(curr->val);
            curr = inorderSuccessor(curr);
        }
        
        return result;
    }
    
    // Search
    bool search(int val) {
        ThreadedNode* curr = root;
        
        while (curr) {
            if (val == curr->val) return true;
            
            if (val < curr->val) {
                curr = curr->left;
            } else {
                if (curr->rightThread) {
                    return false;
                }
                curr = curr->right;
            }
        }
        
        return false;
    }
};

// ==================== DOUBLE THREADED TREE ====================

class DoubleThreadedTree {
    DoubleThreadedNode* root;
    
public:
    DoubleThreadedTree() : root(nullptr) {}
    
    // Convert regular binary tree to double threaded
    void createThreaded(vector<int>& nodes) {
        if (nodes.empty() || nodes[0] == -1) return;
        
        // First build regular tree
        root = new DoubleThreadedNode(nodes[0]);
        queue<DoubleThreadedNode*> q;
        q.push(root);
        
        int i = 1;
        while (!q.empty() && i < nodes.size()) {
            DoubleThreadedNode* curr = q.front();
            q.pop();
            
            if (i < nodes.size() && nodes[i] != -1) {
                curr->left = new DoubleThreadedNode(nodes[i]);
                curr->leftThread = false;
                q.push(curr->left);
            }
            i++;
            
            if (i < nodes.size() && nodes[i] != -1) {
                curr->right = new DoubleThreadedNode(nodes[i]);
                curr->rightThread = false;
                q.push(curr->right);
            }
            i++;
        }
        
        // Create threads using inorder traversal
        createThreads();
    }
    
    void createThreads() {
        DoubleThreadedNode* prev = nullptr;
        
        function<void(DoubleThreadedNode*)> inorder = [&](DoubleThreadedNode* node) {
            if (!node) return;
            
            // Process left subtree
            if (!node->leftThread && node->left) {
                inorder(node->left);
            }
            
            // Set threads
            if (!node->left) {
                node->leftThread = true;
                node->left = prev;
            }
            
            if (prev && !prev->right) {
                prev->rightThread = true;
                prev->right = node;
            }
            
            prev = node;
            
            // Process right subtree
            if (!node->rightThread && node->right) {
                inorder(node->right);
            }
        };
        
        inorder(root);
    }
    
    // Inorder traversal (forward)
    vector<int> inorderForward() {
        vector<int> result;
        
        DoubleThreadedNode* curr = root;
        
        // Find leftmost
        while (curr && !curr->leftThread && curr->left) {
            curr = curr->left;
        }
        
        while (curr) {
            result.push_back(curr->val);
            
            if (curr->rightThread) {
                curr = curr->right;
            } else {
                curr = curr->right;
                while (curr && !curr->leftThread && curr->left) {
                    curr = curr->left;
                }
            }
        }
        
        return result;
    }
    
    // Inorder traversal (backward - reverse inorder)
    vector<int> inorderBackward() {
        vector<int> result;
        
        DoubleThreadedNode* curr = root;
        
        // Find rightmost
        while (curr && !curr->rightThread && curr->right) {
            curr = curr->right;
        }
        
        while (curr) {
            result.push_back(curr->val);
            
            if (curr->leftThread) {
                curr = curr->left;
            } else {
                curr = curr->left;
                while (curr && !curr->rightThread && curr->right) {
                    curr = curr->right;
                }
            }
        }
        
        return result;
    }
};

// ==================== CONVERT BINARY TREE TO THREADED ====================

ThreadedNode* convertToThreaded(vector<int>& nodes) {
    if (nodes.empty() || nodes[0] == -1) return nullptr;
    
    // Build regular tree first
    ThreadedNode* root = new ThreadedNode(nodes[0]);
    queue<ThreadedNode*> q;
    q.push(root);
    
    int i = 1;
    while (!q.empty() && i < nodes.size()) {
        ThreadedNode* curr = q.front();
        q.pop();
        
        if (i < nodes.size() && nodes[i] != -1) {
            curr->left = new ThreadedNode(nodes[i]);
            q.push(curr->left);
        }
        i++;
        
        if (i < nodes.size() && nodes[i] != -1) {
            curr->right = new ThreadedNode(nodes[i]);
            q.push(curr->right);
        }
        i++;
    }
    
    // Create right threads
    ThreadedNode* prev = nullptr;
    
    function<void(ThreadedNode*)> createThreads = [&](ThreadedNode* node) {
        if (!node) return;
        
        createThreads(node->left);
        
        if (prev && !prev->right) {
            prev->right = node;
            prev->rightThread = true;
        }
        prev = node;
        
        createThreads(node->right);
    };
    
    createThreads(root);
    
    return root;
}

// Traverse threaded tree
vector<int> traverseThreaded(ThreadedNode* root) {
    vector<int> result;
    
    ThreadedNode* curr = root;
    while (curr && curr->left) {
        curr = curr->left;
    }
    
    while (curr) {
        result.push_back(curr->val);
        
        if (curr->rightThread) {
            curr = curr->right;
        } else {
            curr = curr->right;
            while (curr && curr->left) {
                curr = curr->left;
            }
        }
    }
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << "=== Threaded Binary Tree ===" << endl;
    
    // Single Threaded Tree (BST)
    SingleThreadedTree stt;
    
    vector<int> values = {20, 10, 30, 5, 15, 25, 35};
    
    cout << "\nInserting into Single Threaded BST: ";
    for (int v : values) {
        cout << v << " ";
        stt.insert(v);
    }
    cout << endl;
    
    cout << "Inorder (O(1) space): ";
    for (int x : stt.inorder()) cout << x << " ";
    cout << endl;
    
    cout << "Search 15: " << (stt.search(15) ? "Found" : "Not Found") << endl;
    cout << "Search 12: " << (stt.search(12) ? "Found" : "Not Found") << endl;
    
    // Double Threaded Tree
    cout << "\n=== Double Threaded Tree ===" << endl;
    
    /*
              1
            /   \
           2     3
          / \
         4   5
    */
    vector<int> nodes = {1, 2, 3, 4, 5};
    
    DoubleThreadedTree dtt;
    dtt.createThreaded(nodes);
    
    cout << "Inorder Forward: ";
    for (int x : dtt.inorderForward()) cout << x << " ";
    cout << endl;
    
    cout << "Inorder Backward: ";
    for (int x : dtt.inorderBackward()) cout << x << " ";
    cout << endl;
    
    // Convert regular tree to threaded
    cout << "\n=== Convert to Threaded ===" << endl;
    
    vector<int> treeNodes = {6, 3, 8, 1, 5, 7, 11, -1, 2, 4};
    ThreadedNode* threaded = convertToThreaded(treeNodes);
    
    cout << "Traversal of converted threaded tree: ";
    for (int x : traverseThreaded(threaded)) cout << x << " ";
    cout << endl;
    
    return 0;
}





