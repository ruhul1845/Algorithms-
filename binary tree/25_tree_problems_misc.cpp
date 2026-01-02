/*
    Miscellaneous Binary Tree Problems
    ==================================
    
    Collection of various important binary tree problems.
    
    Time Complexity: Varies per problem
    Space Complexity: Varies per problem
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ==================== COUSIN NODES ====================

// Check if two nodes are cousins (same level, different parents)
bool areCousins(TreeNode* root, int x, int y) {
    if (!root) return false;
    
    int depthX = -1, depthY = -1;
    TreeNode* parentX = nullptr;
    TreeNode* parentY = nullptr;
    
    queue<pair<TreeNode*, TreeNode*>> q; // {node, parent}
    q.push({root, nullptr});
    int depth = 0;
    
    while (!q.empty()) {
        int size = q.size();
        
        for (int i = 0; i < size; i++) {
            auto [node, parent] = q.front();
            q.pop();
            
            if (node->val == x) {
                depthX = depth;
                parentX = parent;
            }
            if (node->val == y) {
                depthY = depth;
                parentY = parent;
            }
            
            if (node->left) q.push({node->left, node});
            if (node->right) q.push({node->right, node});
        }
        
        depth++;
    }
    
    return depthX == depthY && parentX != parentY;
}

// ==================== DUPLICATE SUBTREES ====================

// Find all duplicate subtrees
vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
    vector<TreeNode*> result;
    unordered_map<string, int> count;
    
    function<string(TreeNode*)> serialize = [&](TreeNode* node) -> string {
        if (!node) return "#";
        
        string s = to_string(node->val) + "," + 
                   serialize(node->left) + "," + 
                   serialize(node->right);
        
        if (count[s] == 1) {
            result.push_back(node);
        }
        count[s]++;
        
        return s;
    };
    
    serialize(root);
    return result;
}

// ==================== PRINT ANCESTORS ====================

bool printAncestors(TreeNode* root, int target) {
    if (!root) return false;
    
    if (root->val == target) return true;
    
    if (printAncestors(root->left, target) || 
        printAncestors(root->right, target)) {
        cout << root->val << " ";
        return true;
    }
    
    return false;
}

// ==================== COUNT COMPLETE TREE NODES ====================

// O(log^2 n) solution for complete binary tree
int countNodes(TreeNode* root) {
    if (!root) return 0;
    
    int leftHeight = 0, rightHeight = 0;
    TreeNode* left = root;
    TreeNode* right = root;
    
    while (left) {
        leftHeight++;
        left = left->left;
    }
    
    while (right) {
        rightHeight++;
        right = right->right;
    }
    
    // Perfect binary tree
    if (leftHeight == rightHeight) {
        return (1 << leftHeight) - 1;
    }
    
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// ==================== LINKED LIST IN BINARY TREE ====================

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

bool isSubPath(ListNode* head, TreeNode* root) {
    if (!head) return true;
    if (!root) return false;
    
    function<bool(ListNode*, TreeNode*)> match = [&](ListNode* h, TreeNode* t) -> bool {
        if (!h) return true;
        if (!t) return false;
        if (h->val != t->val) return false;
        
        return match(h->next, t->left) || match(h->next, t->right);
    };
    
    return match(head, root) || isSubPath(head, root->left) || isSubPath(head, root->right);
}

// ==================== CONNECT NODES AT SAME LEVEL ====================

struct NodeWithNext {
    int val;
    NodeWithNext* left;
    NodeWithNext* right;
    NodeWithNext* next;
    
    NodeWithNext(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
};

NodeWithNext* connect(NodeWithNext* root) {
    if (!root) return nullptr;
    
    NodeWithNext* leftmost = root;
    
    while (leftmost->left) {
        NodeWithNext* curr = leftmost;
        
        while (curr) {
            curr->left->next = curr->right;
            
            if (curr->next) {
                curr->right->next = curr->next->left;
            }
            
            curr = curr->next;
        }
        
        leftmost = leftmost->left;
    }
    
    return root;
}

// ==================== STEP BY STEP FROM NODE TO NODE ====================

// Minimum steps to reach from one node to another
string getDirections(TreeNode* root, int startValue, int destValue) {
    // Find paths from root to both nodes
    string pathToStart, pathToDest;
    
    function<bool(TreeNode*, int, string&)> findPath = 
        [&](TreeNode* node, int target, string& path) -> bool {
        if (!node) return false;
        if (node->val == target) return true;
        
        path += 'L';
        if (findPath(node->left, target, path)) return true;
        path.pop_back();
        
        path += 'R';
        if (findPath(node->right, target, path)) return true;
        path.pop_back();
        
        return false;
    };
    
    findPath(root, startValue, pathToStart);
    findPath(root, destValue, pathToDest);
    
    // Find LCA position
    int i = 0;
    while (i < pathToStart.size() && i < pathToDest.size() && 
           pathToStart[i] == pathToDest[i]) {
        i++;
    }
    
    // Go up from start to LCA, then down to dest
    string result = string(pathToStart.size() - i, 'U') + pathToDest.substr(i);
    
    return result;
}

// ==================== DELETE NODES AND RETURN FOREST ====================

vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
    vector<TreeNode*> forest;
    unordered_set<int> toDelete(to_delete.begin(), to_delete.end());
    
    function<TreeNode*(TreeNode*, bool)> dfs = [&](TreeNode* node, bool isRoot) -> TreeNode* {
        if (!node) return nullptr;
        
        bool deleted = toDelete.count(node->val);
        
        if (isRoot && !deleted) {
            forest.push_back(node);
        }
        
        node->left = dfs(node->left, deleted);
        node->right = dfs(node->right, deleted);
        
        return deleted ? nullptr : node;
    };
    
    dfs(root, true);
    return forest;
}

// ==================== POPULATING NEXT RIGHT POINTERS ====================

// For any binary tree (not just perfect)
NodeWithNext* connectAnyTree(NodeWithNext* root) {
    if (!root) return nullptr;
    
    queue<NodeWithNext*> q;
    q.push(root);
    
    while (!q.empty()) {
        int size = q.size();
        NodeWithNext* prev = nullptr;
        
        for (int i = 0; i < size; i++) {
            NodeWithNext* curr = q.front();
            q.pop();
            
            if (prev) prev->next = curr;
            prev = curr;
            
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
    
    return root;
}

// ==================== CHECK COMPLETE BINARY TREE ====================

bool isCompleteTree(TreeNode* root) {
    if (!root) return true;
    
    queue<TreeNode*> q;
    q.push(root);
    bool foundNull = false;
    
    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();
        
        if (!curr) {
            foundNull = true;
        } else {
            if (foundNull) return false;
            q.push(curr->left);
            q.push(curr->right);
        }
    }
    
    return true;
}

// ==================== EVEN-ODD TREE ====================

// Check if tree satisfies even-odd property
bool isEvenOddTree(TreeNode* root) {
    if (!root) return true;
    
    queue<TreeNode*> q;
    q.push(root);
    int level = 0;
    
    while (!q.empty()) {
        int size = q.size();
        int prev = level % 2 == 0 ? INT_MIN : INT_MAX;
        
        for (int i = 0; i < size; i++) {
            TreeNode* curr = q.front();
            q.pop();
            
            if (level % 2 == 0) {
                // Even level: odd values, strictly increasing
                if (curr->val % 2 == 0 || curr->val <= prev) return false;
            } else {
                // Odd level: even values, strictly decreasing
                if (curr->val % 2 == 1 || curr->val >= prev) return false;
            }
            
            prev = curr->val;
            
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        
        level++;
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << "=== Miscellaneous Tree Problems ===" << endl;
    
    // Cousin nodes
    /*
              1
            /   \
           2     3
          /       \
         4         5
    */
    vector<int> cousinNodes = {1, 2, 3, 4, -1, -1, 5};
    TreeNode* cousinTree = buildTree(cousinNodes);
    
    cout << "\nAre 4 and 5 cousins: " << (areCousins(cousinTree, 4, 5) ? "Yes" : "No") << endl;
    
    // Print ancestors
    cout << "\nAncestors of 5: ";
    printAncestors(cousinTree, 5);
    cout << endl;
    
    // Complete tree node count
    vector<int> completeNodes = {1, 2, 3, 4, 5, 6};
    TreeNode* complete = buildTree(completeNodes);
    cout << "\nComplete tree node count: " << countNodes(complete) << endl;
    
    // Is complete tree
    cout << "Is complete tree: " << (isCompleteTree(complete) ? "Yes" : "No") << endl;
    
    // Step by step directions
    /*
              5
            /   \
           1     2
          /     / \
         3     6   4
    */
    vector<int> dirNodes = {5, 1, 2, 3, -1, 6, 4};
    TreeNode* dirTree = buildTree(dirNodes);
    
    cout << "\nDirections from 3 to 6: " << getDirections(dirTree, 3, 6) << endl;
    
    // Delete nodes and return forest
    vector<int> forestNodes = {1, 2, 3, 4, 5, 6, 7};
    TreeNode* forestTree = buildTree(forestNodes);
    vector<int> toDelete = {3, 5};
    
    auto forest = delNodes(forestTree, toDelete);
    cout << "\nForest after deleting [3,5]: " << forest.size() << " trees" << endl;
    
    return 0;
}







