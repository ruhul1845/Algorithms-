/*
    Red-Black Tree (Self-Balancing BST)
    ====================================
    
    Properties:
    1. Every node is either red or black
    2. Root is always black
    3. All leaves (NIL) are black
    4. If a node is red, both children are black
    5. Every path from node to descendant NIL has same number of black nodes
    
    Time Complexity: O(log n) for all operations
    Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

enum Color { RED, BLACK };

struct RBNode {
    int val;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
    
    RBNode(int x) : val(x), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    RBNode* root;
    RBNode* NIL;  // Sentinel node
    
    void initNIL() {
        NIL = new RBNode(0);
        NIL->color = BLACK;
        NIL->left = NIL->right = NIL->parent = NIL;
    }
    
    void leftRotate(RBNode* x) {
        RBNode* y = x->right;
        x->right = y->left;
        
        if (y->left != NIL) {
            y->left->parent = x;
        }
        
        y->parent = x->parent;
        
        if (x->parent == NIL) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        
        y->left = x;
        x->parent = y;
    }
    
    void rightRotate(RBNode* y) {
        RBNode* x = y->left;
        y->left = x->right;
        
        if (x->right != NIL) {
            x->right->parent = y;
        }
        
        x->parent = y->parent;
        
        if (y->parent == NIL) {
            root = x;
        } else if (y == y->parent->right) {
            y->parent->right = x;
        } else {
            y->parent->left = x;
        }
        
        x->right = y;
        y->parent = x;
    }
    
    void insertFixup(RBNode* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                RBNode* y = z->parent->parent->right; // Uncle
                
                if (y->color == RED) {
                    // Case 1: Uncle is red
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        // Case 2: Uncle black, z is right child
                        z = z->parent;
                        leftRotate(z);
                    }
                    // Case 3: Uncle black, z is left child
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                RBNode* y = z->parent->parent->left; // Uncle
                
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }
    
    void transplant(RBNode* u, RBNode* v) {
        if (u->parent == NIL) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }
    
    RBNode* minimum(RBNode* node) {
        while (node->left != NIL) {
            node = node->left;
        }
        return node;
    }
    
    void deleteFixup(RBNode* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                RBNode* w = x->parent->right;
                
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                RBNode* w = x->parent->left;
                
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }
    
    void inorderHelper(RBNode* node, vector<pair<int, char>>& result) {
        if (node == NIL) return;
        inorderHelper(node->left, result);
        result.push_back({node->val, node->color == RED ? 'R' : 'B'});
        inorderHelper(node->right, result);
    }
    
    void printTreeHelper(RBNode* node, string prefix, bool isLeft) {
        if (node == NIL) return;
        
        cout << prefix;
        cout << (isLeft ? "├──" : "└──");
        cout << node->val << (node->color == RED ? "(R)" : "(B)") << endl;
        
        printTreeHelper(node->left, prefix + (isLeft ? "│   " : "    "), true);
        printTreeHelper(node->right, prefix + (isLeft ? "│   " : "    "), false);
    }
    
    int blackHeight(RBNode* node) {
        if (node == NIL) return 1;
        
        int leftBH = blackHeight(node->left);
        int rightBH = blackHeight(node->right);
        
        if (leftBH != rightBH) return -1;
        
        return leftBH + (node->color == BLACK ? 1 : 0);
    }
    
public:
    RedBlackTree() {
        initNIL();
        root = NIL;
    }
    
    void insert(int val) {
        RBNode* z = new RBNode(val);
        z->left = z->right = NIL;
        
        RBNode* y = NIL;
        RBNode* x = root;
        
        while (x != NIL) {
            y = x;
            if (z->val < x->val) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        
        z->parent = y;
        
        if (y == NIL) {
            root = z;
        } else if (z->val < y->val) {
            y->left = z;
        } else {
            y->right = z;
        }
        
        insertFixup(z);
    }
    
    void remove(int val) {
        RBNode* z = root;
        
        while (z != NIL) {
            if (val == z->val) break;
            if (val < z->val) z = z->left;
            else z = z->right;
        }
        
        if (z == NIL) return;
        
        RBNode* y = z;
        RBNode* x;
        Color originalColor = y->color;
        
        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            originalColor = y->color;
            x = y->right;
            
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        
        delete z;
        
        if (originalColor == BLACK) {
            deleteFixup(x);
        }
    }
    
    bool search(int val) {
        RBNode* curr = root;
        while (curr != NIL) {
            if (val == curr->val) return true;
            if (val < curr->val) curr = curr->left;
            else curr = curr->right;
        }
        return false;
    }
    
    vector<pair<int, char>> inorder() {
        vector<pair<int, char>> result;
        inorderHelper(root, result);
        return result;
    }
    
    void printTree() {
        if (root == NIL) {
            cout << "(empty)" << endl;
            return;
        }
        printTreeHelper(root, "", false);
    }
    
    bool isValid() {
        // Check black height property
        return blackHeight(root) != -1;
    }
    
    int getBlackHeight() {
        return blackHeight(root);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << "=== Red-Black Tree ===" << endl;
    
    RedBlackTree rbt;
    
    // Insert elements
    vector<int> elements = {7, 3, 18, 10, 22, 8, 11, 26, 2, 6};
    
    cout << "\nInserting: ";
    for (int x : elements) {
        cout << x << " ";
        rbt.insert(x);
    }
    cout << endl;
    
    cout << "\nTree structure:" << endl;
    rbt.printTree();
    
    cout << "\nInorder (value, color): ";
    for (auto& [val, color] : rbt.inorder()) {
        cout << val << "(" << color << ") ";
    }
    cout << endl;
    
    cout << "\nIs valid RB Tree: " << (rbt.isValid() ? "Yes" : "No") << endl;
    cout << "Black height: " << rbt.getBlackHeight() << endl;
    
    // Search
    cout << "\nSearch 10: " << (rbt.search(10) ? "Found" : "Not Found") << endl;
    cout << "Search 15: " << (rbt.search(15) ? "Found" : "Not Found") << endl;
    
    // Delete
    cout << "\nDeleting 18:" << endl;
    rbt.remove(18);
    rbt.printTree();
    cout << "Is valid after deletion: " << (rbt.isValid() ? "Yes" : "No") << endl;
    
    cout << "\nDeleting 7:" << endl;
    rbt.remove(7);
    rbt.printTree();
    cout << "Is valid after deletion: " << (rbt.isValid() ? "Yes" : "No") << endl;
    
    cout << "\nFinal inorder: ";
    for (auto& [val, color] : rbt.inorder()) {
        cout << val << "(" << color << ") ";
    }
    cout << endl;
    
    return 0;
}

