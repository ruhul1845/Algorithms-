/*
    Serialize and Deserialize Binary Tree
    ======================================
    
    Converting a tree to string and back. Essential for:
    - Storing tree in database/file
    - Transmitting over network
    - Deep copy of tree
    
    Time Complexity: O(n)
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

// ==================== METHOD 1: PREORDER ====================

class CodecPreorder {
public:
    // Serialize using preorder with null markers
    string serialize(TreeNode* root) {
        if (!root) return "N";
        
        return to_string(root->val) + "," + 
               serialize(root->left) + "," + 
               serialize(root->right);
    }
    
    // Deserialize
    TreeNode* deserialize(string data) {
        queue<string> tokens;
        stringstream ss(data);
        string token;
        
        while (getline(ss, token, ',')) {
            tokens.push(token);
        }
        
        return buildTree(tokens);
    }
    
private:
    TreeNode* buildTree(queue<string>& tokens) {
        if (tokens.empty()) return nullptr;
        
        string val = tokens.front();
        tokens.pop();
        
        if (val == "N") return nullptr;
        
        TreeNode* node = new TreeNode(stoi(val));
        node->left = buildTree(tokens);
        node->right = buildTree(tokens);
        
        return node;
    }
};

// ==================== METHOD 2: LEVEL ORDER ====================

class CodecLevelOrder {
public:
    string serialize(TreeNode* root) {
        if (!root) return "";
        
        string result;
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();
            
            if (curr) {
                result += to_string(curr->val) + ",";
                q.push(curr->left);
                q.push(curr->right);
            } else {
                result += "N,";
            }
        }
        
        return result;
    }
    
    TreeNode* deserialize(string data) {
        if (data.empty()) return nullptr;
        
        vector<string> tokens;
        stringstream ss(data);
        string token;
        
        while (getline(ss, token, ',')) {
            if (!token.empty()) tokens.push_back(token);
        }
        
        if (tokens.empty() || tokens[0] == "N") return nullptr;
        
        TreeNode* root = new TreeNode(stoi(tokens[0]));
        queue<TreeNode*> q;
        q.push(root);
        
        int i = 1;
        while (!q.empty() && i < tokens.size()) {
            TreeNode* curr = q.front();
            q.pop();
            
            // Left child
            if (tokens[i] != "N") {
                curr->left = new TreeNode(stoi(tokens[i]));
                q.push(curr->left);
            }
            i++;
            
            // Right child
            if (i < tokens.size() && tokens[i] != "N") {
                curr->right = new TreeNode(stoi(tokens[i]));
                q.push(curr->right);
            }
            i++;
        }
        
        return root;
    }
};

// ==================== METHOD 3: BRACKET NOTATION ====================

class CodecBracket {
public:
    // Format: value(left)(right)
    string serialize(TreeNode* root) {
        if (!root) return "()";
        
        string left = serialize(root->left);
        string right = serialize(root->right);
        
        return to_string(root->val) + "(" + left + ")(" + right + ")";
    }
    
    TreeNode* deserialize(string data) {
        int idx = 0;
        return parse(data, idx);
    }
    
private:
    TreeNode* parse(const string& s, int& idx) {
        if (idx >= s.size() || s[idx] == '(') {
            if (idx < s.size() && s[idx] == '(') {
                idx++; // skip '('
                if (s[idx] == ')') {
                    idx++; // skip ')'
                    return nullptr;
                }
            }
            return nullptr;
        }
        
        // Parse value
        int sign = 1;
        if (s[idx] == '-') {
            sign = -1;
            idx++;
        }
        
        int val = 0;
        while (idx < s.size() && isdigit(s[idx])) {
            val = val * 10 + (s[idx] - '0');
            idx++;
        }
        
        TreeNode* node = new TreeNode(sign * val);
        
        // Parse left subtree
        if (idx < s.size() && s[idx] == '(') {
            idx++; // skip '('
            node->left = parse(s, idx);
            idx++; // skip ')'
        }
        
        // Parse right subtree
        if (idx < s.size() && s[idx] == '(') {
            idx++; // skip '('
            node->right = parse(s, idx);
            idx++; // skip ')'
        }
        
        return node;
    }
};

// ==================== BST SERIALIZATION (More Efficient) ====================

class CodecBST {
public:
    // BST can be serialized using preorder only (no null markers needed)
    string serialize(TreeNode* root) {
        string result;
        serializeHelper(root, result);
        return result;
    }
    
    TreeNode* deserialize(string data) {
        if (data.empty()) return nullptr;
        
        queue<int> values;
        stringstream ss(data);
        string token;
        
        while (getline(ss, token, ',')) {
            if (!token.empty()) values.push(stoi(token));
        }
        
        return buildBST(values, INT_MIN, INT_MAX);
    }
    
private:
    void serializeHelper(TreeNode* root, string& result) {
        if (!root) return;
        
        result += to_string(root->val) + ",";
        serializeHelper(root->left, result);
        serializeHelper(root->right, result);
    }
    
    TreeNode* buildBST(queue<int>& values, int minVal, int maxVal) {
        if (values.empty()) return nullptr;
        
        int val = values.front();
        if (val < minVal || val > maxVal) return nullptr;
        
        values.pop();
        TreeNode* node = new TreeNode(val);
        node->left = buildBST(values, minVal, val);
        node->right = buildBST(values, val, maxVal);
        
        return node;
    }
};

// Deep copy of tree
TreeNode* cloneTree(TreeNode* root) {
    if (!root) return nullptr;
    
    TreeNode* newRoot = new TreeNode(root->val);
    newRoot->left = cloneTree(root->left);
    newRoot->right = cloneTree(root->right);
    
    return newRoot;
}

// Print tree
void printTree(TreeNode* root, string prefix = "", bool isLeft = true) {
    if (!root) return;
    
    cout << prefix;
    cout << (isLeft ? "├──" : "└──");
    cout << root->val << endl;
    
    printTree(root->left, prefix + (isLeft ? "│   " : "    "), true);
    printTree(root->right, prefix + (isLeft ? "│   " : "    "), false);
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
              1
            /   \
           2     3
              /   \
             4     5
    */
    
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);
    
    cout << "=== Serialize and Deserialize ===" << endl;
    cout << "\nOriginal Tree:" << endl;
    printTree(root);
    
    // Preorder serialization
    CodecPreorder codec1;
    string preorderSerialized = codec1.serialize(root);
    cout << "\nPreorder Serialized: " << preorderSerialized << endl;
    
    TreeNode* preorderDeserialized = codec1.deserialize(preorderSerialized);
    cout << "Preorder Deserialized (inorder): ";
    printInorder(preorderDeserialized);
    cout << endl;
    
    // Level order serialization
    CodecLevelOrder codec2;
    string levelSerialized = codec2.serialize(root);
    cout << "\nLevel Order Serialized: " << levelSerialized << endl;
    
    TreeNode* levelDeserialized = codec2.deserialize(levelSerialized);
    cout << "Level Order Deserialized (inorder): ";
    printInorder(levelDeserialized);
    cout << endl;
    
    // BST serialization
    /*
        BST:
              4
            /   \
           2     6
          / \   / \
         1   3 5   7
    */
    TreeNode* bst = new TreeNode(4);
    bst->left = new TreeNode(2);
    bst->right = new TreeNode(6);
    bst->left->left = new TreeNode(1);
    bst->left->right = new TreeNode(3);
    bst->right->left = new TreeNode(5);
    bst->right->right = new TreeNode(7);
    
    cout << "\n=== BST Serialization ===" << endl;
    CodecBST codecBST;
    string bstSerialized = codecBST.serialize(bst);
    cout << "BST Serialized: " << bstSerialized << endl;
    
    TreeNode* bstDeserialized = codecBST.deserialize(bstSerialized);
    cout << "BST Deserialized (inorder): ";
    printInorder(bstDeserialized);
    cout << endl;
    
    // Deep copy
    cout << "\n=== Deep Copy ===" << endl;
    TreeNode* clone = cloneTree(root);
    cout << "Original root: " << root << ", val = " << root->val << endl;
    cout << "Cloned root: " << clone << ", val = " << clone->val << endl;
    
    return 0;
}

