/*
 * Stack and Queue - Advanced Problems
 * LRU Cache, Sliding Window Maximum, Stock Span
 */

#include <bits/stdc++.h>
using namespace std;

// 1. LRU Cache
class LRUCache {
    int capacity;
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int, int>>::iterator> map;
    
public:
    LRUCache(int capacity) : capacity(capacity) {}
    
    int get(int key) {
        if (map.find(key) == map.end()) return -1;
        
        auto it = map[key];
        int value = it->second;
        cache.erase(it);
        cache.push_front({key, value});
        map[key] = cache.begin();
        
        return value;
    }
    
    void put(int key, int value) {
        if (map.find(key) != map.end()) {
            cache.erase(map[key]);
        } else if (cache.size() == capacity) {
            int oldKey = cache.back().first;
            cache.pop_back();
            map.erase(oldKey);
        }
        
        cache.push_front({key, value});
        map[key] = cache.begin();
    }
};

// 2. Largest Rectangle in Histogram
int largestRectangleArea(vector<int>& heights) {
    stack<int> st;
    int maxArea = 0;
    int n = heights.size();
    
    for (int i = 0; i <= n; i++) {
        int h = (i == n) ? 0 : heights[i];
        
        while (!st.empty() && h < heights[st.top()]) {
            int height = heights[st.top()];
            st.pop();
            
            int width = st.empty() ? i : i - st.top() - 1;
            maxArea = max(maxArea, height * width);
        }
        
        st.push(i);
    }
    
    return maxArea;
}

// 3. Stock Span Problem
vector<int> calculateSpan(vector<int>& prices) {
    int n = prices.size();
    vector<int> span(n);
    stack<int> st;
    
    for (int i = 0; i < n; i++) {
        while (!st.empty() && prices[st.top()] <= prices[i]) {
            st.pop();
        }
        
        span[i] = st.empty() ? (i + 1) : (i - st.top());
        st.push(i);
    }
    
    return span;
}

// 4. Evaluate Reverse Polish Notation
int evalRPN(vector<string>& tokens) {
    stack<int> st;
    
    for (string& token : tokens) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            
            if (token == "+") st.push(a + b);
            else if (token == "-") st.push(a - b);
            else if (token == "*") st.push(a * b);
            else st.push(a / b);
        } else {
            st.push(stoi(token));
        }
    }
    
    return st.top();
}

// 5. Simplify Path
string simplifyPath(string path) {
    stack<string> st;
    stringstream ss(path);
    string dir;
    
    while (getline(ss, dir, '/')) {
        if (dir == "" || dir == ".") continue;
        
        if (dir == "..") {
            if (!st.empty()) st.pop();
        } else {
            st.push(dir);
        }
    }
    
    string result = "";
    while (!st.empty()) {
        result = "/" + st.top() + result;
        st.pop();
    }
    
    return result.empty() ? "/" : result;
}

// 6. Sliding Window Maximum
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> result;
    
    for (int i = 0; i < nums.size(); i++) {
        if (!dq.empty() && dq.front() == i - k) {
            dq.pop_front();
        }
        
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    
    return result;
}

// 7. Basic Calculator
int calculate(string s) {
    stack<int> st;
    int num = 0;
    char op = '+';
    
    for (int i = 0; i < s.length(); i++) {
        if (isdigit(s[i])) {
            num = num * 10 + (s[i] - '0');
        }
        
        if ((!isdigit(s[i]) && s[i] != ' ') || i == s.length() - 1) {
            if (op == '+') {
                st.push(num);
            } else if (op == '-') {
                st.push(-num);
            } else if (op == '*') {
                int top = st.top();
                st.pop();
                st.push(top * num);
            } else if (op == '/') {
                int top = st.top();
                st.pop();
                st.push(top / num);
            }
            
            op = s[i];
            num = 0;
        }
    }
    
    int result = 0;
    while (!st.empty()) {
        result += st.top();
        st.pop();
    }
    
    return result;
}

// 8. Remove K Digits
string removeKdigits(string num, int k) {
    stack<char> st;
    
    for (char c : num) {
        while (!st.empty() && k > 0 && st.top() > c) {
            st.pop();
            k--;
        }
        st.push(c);
    }
    
    while (k > 0) {
        st.pop();
        k--;
    }
    
    string result = "";
    while (!st.empty()) {
        result += st.top();
        st.pop();
    }
    
    reverse(result.begin(), result.end());
    
    // Remove leading zeros
    int i = 0;
    while (i < result.length() && result[i] == '0') i++;
    
    result = result.substr(i);
    return result.empty() ? "0" : result;
}

int main() {
    // Test LRU Cache
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cout << "Get 1: " << cache.get(1) << endl;
    cache.put(3, 3);
    cout << "Get 2: " << cache.get(2) << endl;
    
    // Test Stock Span
    vector<int> prices = {100, 80, 60, 70, 60, 75, 85};
    vector<int> span = calculateSpan(prices);
    cout << "Stock Span: ";
    for (int x : span) cout << x << " ";
    cout << endl;
    
    // Test Sliding Window Maximum
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> maxWindow = maxSlidingWindow(nums, 3);
    cout << "Sliding Window Maximum: ";
    for (int x : maxWindow) cout << x << " ";
    cout << endl;
    
    return 0;
}










