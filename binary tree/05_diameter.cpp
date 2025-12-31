/*
    Diameter of Binary Tree
    =======================
    
    The diameter (or width) of a tree is the number of nodes on the longest path
    between any two nodes in the tree. This path may or may not pass through the root.
    
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

// Method 1: O(n) - Single pass using height
class Solution1 {
public:
    int diameter;
    
    int height(TreeNode* root) {
        if (!root) return 0;
        
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        
        // Update diameter - path through this node
        diameter = max(diameter, leftHeight + rightHeight);
        
        return 1 + max(leftHeight, rightHeight);
    }
    
    int diameterOfBinaryTree(TreeNode* root) {
        diameter = 0;
        height(root);
        return diameter;
    }
};

// Method 2: Using pair to return both height and diameter
pair<int, int> diameterHelper(TreeNode* root) {
    if (!root) return {0, 0}; // {height, diameter}
    
    auto [leftHeight, leftDiameter] = diameterHelper(root->left);
    auto [rightHeight, rightDiameter] = diameterHelper(root->right);
    
    int height = 1 + max(leftHeight, rightHeight);
    int diameter = max({leftDiameter, rightDiameter, leftHeight + rightHeight});
    
    return {height, diameter};
}

int diameter(TreeNode* root) {
    return diameterHelper(root).second;
}

// Method 3: Diameter in terms of edges (not nodes)
int diameterEdges(TreeNode* root) {
    int maxDiameter = 0;
    
    function<int(TreeNode*)> height = [&](TreeNode* node) -> int {
        if (!node) return -1;
        
        int leftH = height(node->left);
        int rightH = height(node->right);
        
        maxDiameter = max(maxDiameter, leftH + rightH + 2);
        
        return 1 + max(leftH, rightH);
    };
    
    height(root);
    return maxDiameter;
}

// Get the actual path forming the diameter
vector<int> getDiameterPath(TreeNode* root) {
    vector<int> result;
    int maxLen = 0;
    
    // Helper to get path from node to deepest leaf
    function<vector<int>(TreeNode*)> getPath = [&](TreeNode* node) -> vector<int> {
        if (!node) return {};
        
        vector<int> leftPath = getPath(node->left);
        vector<int> rightPath = getPath(node->right);
        
        // Check if path through this node is the longest
        if (leftPath.size() + rightPath.size() + 1 > maxLen) {
            maxLen = leftPath.size() + rightPath.size() + 1;
            
            // Build the path: reverse(leftPath) + node + rightPath
            result.clear();
            for (int i = leftPath.size() - 1; i >= 0; i--) {
                result.push_back(leftPath[i]);
            }
            result.push_back(node->val);
            for (int x : rightPath) {
                result.push_back(x);
            }
        }
        
        // Return longer path
        if (leftPath.size() > rightPath.size()) {
            leftPath.push_back(node->val);
            return leftPath;
        } else {
            rightPath.push_back(node->val);
            return rightPath;
        }
    };
    
    getPath(root);
    return result;
}

// Diameter of N-ary tree
struct NaryNode {
    int val;
    vector<NaryNode*> children;
    NaryNode(int x) : val(x) {}
};

int diameterNary(NaryNode* root) {
    int maxDiameter = 0;
    
    function<int(NaryNode*)> height = [&](NaryNode* node) -> int {
        if (!node) return 0;
        
        int maxH1 = 0, maxH2 = 0; // Two largest heights
        
        for (auto child : node->children) {
            int h = height(child);
            
            if (h > maxH1) {
                maxH2 = maxH1;
                maxH1 = h;
            } else if (h > maxH2) {
                maxH2 = h;
            }
        }
        
        maxDiameter = max(maxDiameter, maxH1 + maxH2);
        
        return maxH1 + 1;
    };
    
    height(root);
    return maxDiameter;
}

// Weighted diameter - each edge has weight
struct WeightedNode {
    int val;
    vector<pair<WeightedNode*, int>> children; // {child, weight}
    WeightedNode(int x) : val(x) {}
};

long long weightedDiameter(WeightedNode* root) {
    long long maxDiameter = 0;
    
    function<long long(WeightedNode*)> maxPath = [&](WeightedNode* node) -> long long {
        if (!node) return 0;
        
        long long max1 = 0, max2 = 0;
        
        for (auto& [child, weight] : node->children) {
            long long path = maxPath(child) + weight;
            
            if (path > max1) {
                max2 = max1;
                max1 = path;
            } else if (path > max2) {
                max2 = path;
            }
        }
        
        maxDiameter = max(maxDiameter, max1 + max2);
        
        return max1;
    };
    
    maxPath(root);
    return maxDiameter;
}

// Count all paths of diameter length
int countDiameterPaths(TreeNode* root) {
    int maxDiam = 0;
    int count = 0;
    
    function<int(TreeNode*)> height = [&](TreeNode* node) -> int {
        if (!node) return 0;
        
        int leftH = height(node->left);
        int rightH = height(node->right);
        
        int currDiam = leftH + rightH;
        
        if (currDiam > maxDiam) {
            maxDiam = currDiam;
            count = 1;
        } else if (currDiam == maxDiam) {
            count++;
        }
        
        return 1 + max(leftH, rightH);
    };
    
    height(root);
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    /*
        Tree structure:
              1
            /   \
           2     3
          / \     
         4   5    
        /     \
       6       7
              /
             8
    */
    
    vector<int> nodes = {1, 2, 3, 4, 5, -1, -1, 6, -1, -1, 7, -1, -1, -1, -1, -1, -1, -1, 8};
    TreeNode* root = buildTree(nodes);
    
    // Simpler tree for clear demonstration
    /*
              1
            /   \
           2     3
          / \     
         4   5    
    */
    vector<int> nodes2 = {1, 2, 3, 4, 5};
    TreeNode* root2 = buildTree(nodes2);
    
    cout << "=== Diameter of Binary Tree ===" << endl;
    
    Solution1 sol1;
    cout << "Diameter (Method 1): " << sol1.diameterOfBinaryTree(root2) << endl;
    cout << "Diameter (Method 2): " << diameter(root2) << endl;
    cout << "Diameter in edges: " << diameterEdges(root2) << endl;
    
    cout << "\nDiameter path: ";
    for (int x : getDiameterPath(root2)) cout << x << " ";
    cout << endl;
    
    // Larger tree
    /*
              1
            /   \
           2     3
          / \   / \
         4   5 6   7
        /         / \
       8         9   10
    */
    vector<int> nodes3 = {1, 2, 3, 4, 5, 6, 7, 8, -1, -1, -1, -1, -1, 9, 10};
    TreeNode* root3 = buildTree(nodes3);
    
    Solution1 sol2;
    cout << "\nLarger tree diameter: " << sol2.diameterOfBinaryTree(root3) << endl;
    cout << "Diameter path: ";
    for (int x : getDiameterPath(root3)) cout << x << " ";
    cout << endl;
    
    cout << "Paths with diameter length: " << countDiameterPaths(root3) << endl;
    
    return 0;
}

