/*
 * Stack Implementation and Basic Operations
 * Array-based and Linked List-based implementations
 */

#include <bits/stdc++.h>
using namespace std;

// 1. Stack using Array
class ArrayStack {
    int* arr;
    int top;
    int capacity;
    
public:
    ArrayStack(int size) {
        arr = new int[size];
        capacity = size;
        top = -1;
    }
    
    ~ArrayStack() {
        delete[] arr;
    }
    
    void push(int x) {
        if (isFull()) {
            cout << "Stack Overflow" << endl;
            return;
        }
        arr[++top] = x;
    }
    
    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow" << endl;
            return -1;
        }
        return arr[top--];
    }
    
    int peek() {
        if (isEmpty()) return -1;
        return arr[top];
    }
    
    bool isEmpty() {
        return top == -1;
    }
    
    bool isFull() {
        return top == capacity - 1;
    }
    
    int size() {
        return top + 1;
    }
};

// 2. Stack using Linked List
struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

class LinkedStack {
    Node* top;
    int count;
    
public:
    LinkedStack() : top(nullptr), count(0) {}
    
    void push(int x) {
        Node* newNode = new Node(x);
        newNode->next = top;
        top = newNode;
        count++;
    }
    
    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow" << endl;
            return -1;
        }
        Node* temp = top;
        int val = temp->data;
        top = top->next;
        delete temp;
        count--;
        return val;
    }
    
    int peek() {
        if (isEmpty()) return -1;
        return top->data;
    }
    
    bool isEmpty() {
        return top == nullptr;
    }
    
    int size() {
        return count;
    }
};

// 3. Min Stack - Get minimum in O(1)
class MinStack {
    stack<int> st;
    stack<int> minSt;
    
public:
    void push(int x) {
        st.push(x);
        if (minSt.empty() || x <= minSt.top()) {
            minSt.push(x);
        }
    }
    
    void pop() {
        if (st.empty()) return;
        if (st.top() == minSt.top()) {
            minSt.pop();
        }
        st.pop();
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return minSt.top();
    }
};

// 4. Stack using Two Queues
class StackUsingQueues {
    queue<int> q1, q2;
    
public:
    void push(int x) {
        q2.push(x);
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        swap(q1, q2);
    }
    
    int pop() {
        if (q1.empty()) return -1;
        int val = q1.front();
        q1.pop();
        return val;
    }
    
    int top() {
        if (q1.empty()) return -1;
        return q1.front();
    }
    
    bool empty() {
        return q1.empty();
    }
};

// 5. Valid Parentheses
bool isValid(string s) {
    stack<char> st;
    
    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        } else {
            if (st.empty()) return false;
            
            char top = st.top();
            if ((c == ')' && top == '(') ||
                (c == '}' && top == '{') ||
                (c == ']' && top == '[')) {
                st.pop();
            } else {
                return false;
            }
        }
    }
    return st.empty();
}

// 6. Next Greater Element
vector<int> nextGreaterElement(vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1);
    stack<int> st;
    
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && st.top() <= arr[i]) {
            st.pop();
        }
        
        if (!st.empty()) {
            result[i] = st.top();
        }
        
        st.push(arr[i]);
    }
    return result;
}

int main() {
    // Test Array Stack
    ArrayStack stack(5);
    stack.push(10);
    stack.push(20);
    stack.push(30);
    
    cout << "Stack top: " << stack.peek() << endl;
    cout << "Stack size: " << stack.size() << endl;
    
    // Test Valid Parentheses
    cout << "Is '()[]{}' valid? " << (isValid("()[]{}") ? "Yes" : "No") << endl;
    cout << "Is '([)]' valid? " << (isValid("([)]") ? "Yes" : "No") << endl;
    
    // Test Next Greater Element
    vector<int> arr = {4, 5, 2, 10, 8};
    vector<int> nge = nextGreaterElement(arr);
    cout << "Next Greater Elements: ";
    for (int x : nge) cout << x << " ";
    cout << endl;
    
    return 0;
}










