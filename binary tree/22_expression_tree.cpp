/*
    Expression Tree
    ===============
    
    Binary tree representation of mathematical expressions.
    - Leaf nodes: Operands (numbers/variables)
    - Internal nodes: Operators (+, -, *, /, etc.)
    
    Time Complexity: O(n) for evaluation/traversal
    Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

struct ExprNode {
    string val;
    ExprNode* left;
    ExprNode* right;
    
    ExprNode(string v) : val(v), left(nullptr), right(nullptr) {}
};

// Check if string is operator
bool isOperator(const string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/" || 
           s == "^" || s == "%" ;
}

// Check if character is operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || 
           c == '^' || c == '%';
}

// Get operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '^') return 3;
    return 0;
}

// ==================== BUILD FROM POSTFIX ====================

ExprNode* buildFromPostfix(vector<string>& tokens) {
    stack<ExprNode*> st;
    
    for (const string& token : tokens) {
        if (isOperator(token)) {
            ExprNode* node = new ExprNode(token);
            node->right = st.top(); st.pop();
            node->left = st.top(); st.pop();
            st.push(node);
        } else {
            st.push(new ExprNode(token));
        }
    }
    
    return st.top();
}

// ==================== BUILD FROM PREFIX ====================

ExprNode* buildFromPrefix(vector<string>& tokens, int& idx) {
    if (idx >= tokens.size()) return nullptr;
    
    ExprNode* node = new ExprNode(tokens[idx++]);
    
    if (isOperator(node->val)) {
        node->left = buildFromPrefix(tokens, idx);
        node->right = buildFromPrefix(tokens, idx);
    }
    
    return node;
}

// ==================== BUILD FROM INFIX ====================

// Convert infix to postfix, then build tree
vector<string> infixToPostfix(const string& expr) {
    vector<string> output;
    stack<char> ops;
    
    int i = 0;
    while (i < expr.size()) {
        if (isspace(expr[i])) {
            i++;
            continue;
        }
        
        if (isdigit(expr[i])) {
            string num;
            while (i < expr.size() && (isdigit(expr[i]) || expr[i] == '.')) {
                num += expr[i++];
            }
            output.push_back(num);
        } else if (isalpha(expr[i])) {
            string var;
            while (i < expr.size() && isalnum(expr[i])) {
                var += expr[i++];
            }
            output.push_back(var);
        } else if (expr[i] == '(') {
            ops.push('(');
            i++;
        } else if (expr[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                output.push_back(string(1, ops.top()));
                ops.pop();
            }
            ops.pop(); // Remove '('
            i++;
        } else if (isOperator(expr[i])) {
            while (!ops.empty() && ops.top() != '(' && 
                   precedence(ops.top()) >= precedence(expr[i])) {
                output.push_back(string(1, ops.top()));
                ops.pop();
            }
            ops.push(expr[i]);
            i++;
        } else {
            i++;
        }
    }
    
    while (!ops.empty()) {
        output.push_back(string(1, ops.top()));
        ops.pop();
    }
    
    return output;
}

ExprNode* buildFromInfix(const string& expr) {
    vector<string> postfix = infixToPostfix(expr);
    return buildFromPostfix(postfix);
}

// ==================== EVALUATE ====================

double evaluate(ExprNode* root, map<string, double>& vars = *(new map<string, double>())) {
    if (!root) return 0;
    
    // Leaf node - operand
    if (!root->left && !root->right) {
        if (vars.count(root->val)) {
            return vars[root->val];
        }
        return stod(root->val);
    }
    
    double left = evaluate(root->left, vars);
    double right = evaluate(root->right, vars);
    
    if (root->val == "+") return left + right;
    if (root->val == "-") return left - right;
    if (root->val == "*") return left * right;
    if (root->val == "/") return left / right;
    if (root->val == "%") return (int)left % (int)right;
    if (root->val == "^") return pow(left, right);
    
    return 0;
}

// ==================== TRAVERSALS TO GET EXPRESSIONS ====================

// Infix (with parentheses)
string toInfix(ExprNode* root) {
    if (!root) return "";
    
    if (!root->left && !root->right) {
        return root->val;
    }
    
    string left = toInfix(root->left);
    string right = toInfix(root->right);
    
    return "(" + left + " " + root->val + " " + right + ")";
}

// Prefix (Polish notation)
string toPrefix(ExprNode* root) {
    if (!root) return "";
    
    if (!root->left && !root->right) {
        return root->val;
    }
    
    return root->val + " " + toPrefix(root->left) + " " + toPrefix(root->right);
}

// Postfix (Reverse Polish notation)
string toPostfix(ExprNode* root) {
    if (!root) return "";
    
    if (!root->left && !root->right) {
        return root->val;
    }
    
    return toPostfix(root->left) + " " + toPostfix(root->right) + " " + root->val;
}

// ==================== SIMPLIFY ====================

// Simplify expression tree (basic constant folding)
ExprNode* simplify(ExprNode* root) {
    if (!root) return nullptr;
    
    // Leaf node
    if (!root->left && !root->right) {
        return new ExprNode(root->val);
    }
    
    ExprNode* left = simplify(root->left);
    ExprNode* right = simplify(root->right);
    
    // Check if both children are numbers
    bool leftNum = !left->left && !left->right && 
                   (isdigit(left->val[0]) || (left->val[0] == '-' && left->val.size() > 1));
    bool rightNum = !right->left && !right->right && 
                    (isdigit(right->val[0]) || (right->val[0] == '-' && right->val.size() > 1));
    
    if (leftNum && rightNum) {
        double l = stod(left->val);
        double r = stod(right->val);
        double result;
        
        if (root->val == "+") result = l + r;
        else if (root->val == "-") result = l - r;
        else if (root->val == "*") result = l * r;
        else if (root->val == "/") result = l / r;
        else if (root->val == "^") result = pow(l, r);
        else result = 0;
        
        return new ExprNode(to_string(result));
    }
    
    // Identity simplifications
    if (root->val == "+" && rightNum && stod(right->val) == 0) return left;
    if (root->val == "+" && leftNum && stod(left->val) == 0) return right;
    if (root->val == "*" && rightNum && stod(right->val) == 1) return left;
    if (root->val == "*" && leftNum && stod(left->val) == 1) return right;
    if (root->val == "*" && ((rightNum && stod(right->val) == 0) || 
                             (leftNum && stod(left->val) == 0))) {
        return new ExprNode("0");
    }
    
    ExprNode* newNode = new ExprNode(root->val);
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

// ==================== DIFFERENTIATE ====================

// Symbolic differentiation with respect to variable
ExprNode* differentiate(ExprNode* root, const string& var) {
    if (!root) return nullptr;
    
    // Constant
    if (!root->left && !root->right) {
        if (root->val == var) {
            return new ExprNode("1");
        }
        return new ExprNode("0");
    }
    
    if (root->val == "+") {
        ExprNode* node = new ExprNode("+");
        node->left = differentiate(root->left, var);
        node->right = differentiate(root->right, var);
        return node;
    }
    
    if (root->val == "-") {
        ExprNode* node = new ExprNode("-");
        node->left = differentiate(root->left, var);
        node->right = differentiate(root->right, var);
        return node;
    }
    
    if (root->val == "*") {
        // Product rule: (f*g)' = f'*g + f*g'
        ExprNode* node = new ExprNode("+");
        
        ExprNode* left = new ExprNode("*");
        left->left = differentiate(root->left, var);
        left->right = simplify(root->right);
        
        ExprNode* right = new ExprNode("*");
        right->left = simplify(root->left);
        right->right = differentiate(root->right, var);
        
        node->left = left;
        node->right = right;
        return node;
    }
    
    return new ExprNode("0");
}

void printTree(ExprNode* root, string prefix = "", bool isLeft = true) {
    if (!root) return;
    
    cout << prefix;
    cout << (isLeft ? "├──" : "└──");
    cout << root->val << endl;
    
    printTree(root->left, prefix + (isLeft ? "│   " : "    "), true);
    printTree(root->right, prefix + (isLeft ? "│   " : "    "), false);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << "=== Expression Tree ===" << endl;
    
    // Build from postfix
    vector<string> postfix = {"3", "4", "+", "2", "*", "7", "/"};
    ExprNode* root1 = buildFromPostfix(postfix);
    
    cout << "\n1. From Postfix: 3 4 + 2 * 7 /" << endl;
    cout << "   Tree:" << endl;
    printTree(root1);
    cout << "   Infix: " << toInfix(root1) << endl;
    cout << "   Prefix: " << toPrefix(root1) << endl;
    cout << "   Value: " << evaluate(root1) << endl;
    
    // Build from infix
    string infix = "(3 + 4) * 2 / 7";
    ExprNode* root2 = buildFromInfix(infix);
    
    cout << "\n2. From Infix: " << infix << endl;
    cout << "   Postfix: " << toPostfix(root2) << endl;
    cout << "   Value: " << evaluate(root2) << endl;
    
    // With variables
    string exprWithVars = "x * 2 + y";
    ExprNode* root3 = buildFromInfix(exprWithVars);
    
    map<string, double> vars;
    vars["x"] = 5;
    vars["y"] = 3;
    
    cout << "\n3. Expression with variables: " << exprWithVars << endl;
    cout << "   With x=5, y=3: " << evaluate(root3, vars) << endl;
    
    // Simplification
    string complex = "x * 1 + 0 + 2 * 3";
    ExprNode* root4 = buildFromInfix(complex);
    ExprNode* simplified = simplify(root4);
    
    cout << "\n4. Simplification:" << endl;
    cout << "   Original: " << toInfix(root4) << endl;
    cout << "   Simplified: " << toInfix(simplified) << endl;
    
    // Differentiation
    string diffExpr = "x * x + 2 * x";
    ExprNode* root5 = buildFromInfix(diffExpr);
    ExprNode* derivative = differentiate(root5, "x");
    ExprNode* simplifiedDeriv = simplify(derivative);
    
    cout << "\n5. Differentiation:" << endl;
    cout << "   Expression: " << toInfix(root5) << endl;
    cout << "   d/dx: " << toInfix(derivative) << endl;
    cout << "   Simplified: " << toInfix(simplifiedDeriv) << endl;
    
    return 0;
}
















