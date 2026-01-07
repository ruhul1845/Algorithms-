/*
 * Backtracking - Optimization Problems
 * Job Assignment, Traveling Salesman, Branch and Bound techniques
 */

#include <bits/stdc++.h>
using namespace std;

// 1. Job Assignment Problem (Assign n jobs to n workers with minimum cost)
int jobAssignmentHelper(vector<vector<int>>& cost, int job, vector<bool>& assigned, int currentCost, int& minCost) {
    int n = cost.size();
    
    if (job == n) {
        minCost = min(minCost, currentCost);
        return minCost;
    }
    
    // Pruning: if current cost already exceeds minimum, no need to continue
    if (currentCost >= minCost) {
        return minCost;
    }
    
    for (int worker = 0; worker < n; worker++) {
        if (!assigned[worker]) {
            assigned[worker] = true;
            jobAssignmentHelper(cost, job + 1, assigned, currentCost + cost[job][worker], minCost);
            assigned[worker] = false;
        }
    }
    
    return minCost;
}

int jobAssignment(vector<vector<int>>& cost) {
    int n = cost.size();
    vector<bool> assigned(n, false);
    int minCost = INT_MAX;
    return jobAssignmentHelper(cost, 0, assigned, 0, minCost);
}

// 2. Traveling Salesman Problem (TSP)
int tspHelper(vector<vector<int>>& dist, int pos, vector<bool>& visited, int count, int cost, int& minCost) {
    int n = dist.size();
    
    if (count == n) {
        minCost = min(minCost, cost + dist[pos][0]);
        return minCost;
    }
    
    // Pruning
    if (cost >= minCost) {
        return minCost;
    }
    
    for (int city = 0; city < n; city++) {
        if (!visited[city]) {
            visited[city] = true;
            tspHelper(dist, city, visited, count + 1, cost + dist[pos][city], minCost);
            visited[city] = false;
        }
    }
    
    return minCost;
}

int tsp(vector<vector<int>>& dist) {
    int n = dist.size();
    vector<bool> visited(n, false);
    visited[0] = true;
    int minCost = INT_MAX;
    return tspHelper(dist, 0, visited, 1, 0, minCost);
}

// 3. 0/1 Knapsack (Backtracking approach)
int knapsackHelper(vector<int>& weights, vector<int>& values, int capacity, int idx, int currentValue, int& maxValue) {
    if (idx >= weights.size() || capacity <= 0) {
        maxValue = max(maxValue, currentValue);
        return maxValue;
    }
    
    // Pruning: check if remaining capacity can improve solution
    int remainingValue = 0;
    for (int i = idx; i < weights.size(); i++) {
        remainingValue += values[i];
    }
    
    if (currentValue + remainingValue <= maxValue) {
        return maxValue;
    }
    
    // Include current item
    if (weights[idx] <= capacity) {
        knapsackHelper(weights, values, capacity - weights[idx], idx + 1, 
                      currentValue + values[idx], maxValue);
    }
    
    // Exclude current item
    knapsackHelper(weights, values, capacity, idx + 1, currentValue, maxValue);
    
    return maxValue;
}

int knapsack(vector<int>& weights, vector<int>& values, int capacity) {
    int maxValue = 0;
    return knapsackHelper(weights, values, capacity, 0, 0, maxValue);
}

// 4. M Coloring Optimization (Find minimum colors needed)
bool canColorWithMColors(vector<vector<int>>& graph, int m, vector<int>& color, int v) {
    int n = graph.size();
    if (v == n) return true;
    
    for (int c = 1; c <= m; c++) {
        bool isSafe = true;
        for (int i = 0; i < n; i++) {
            if (graph[v][i] && color[i] == c) {
                isSafe = false;
                break;
            }
        }
        
        if (isSafe) {
            color[v] = c;
            if (canColorWithMColors(graph, m, color, v + 1)) {
                return true;
            }
            color[v] = 0;
        }
    }
    
    return false;
}

int chromaticNumber(vector<vector<int>>& graph) {
    int n = graph.size();
    
    for (int colors = 1; colors <= n; colors++) {
        vector<int> color(n, 0);
        if (canColorWithMColors(graph, colors, color, 0)) {
            return colors;
        }
    }
    
    return n;
}

// 5. Sum of Subsets with Optimization
void sumOfSubsetsHelper(vector<int>& arr, int target, int idx, int currentSum, 
                       vector<int>& current, vector<vector<int>>& result, int remainingSum) {
    if (currentSum == target) {
        result.push_back(current);
        return;
    }
    
    if (idx >= arr.size() || currentSum > target) {
        return;
    }
    
    // Pruning: if current sum + remaining sum < target, no solution possible
    if (currentSum + remainingSum < target) {
        return;
    }
    
    // Include current element
    current.push_back(arr[idx]);
    sumOfSubsetsHelper(arr, target, idx + 1, currentSum + arr[idx], current, result, 
                      remainingSum - arr[idx]);
    current.pop_back();
    
    // Exclude current element
    sumOfSubsetsHelper(arr, target, idx + 1, currentSum, current, result, remainingSum - arr[idx]);
}

vector<vector<int>> sumOfSubsets(vector<int>& arr, int target) {
    sort(arr.begin(), arr.end());
    int totalSum = 0;
    for (int x : arr) totalSum += x;
    
    vector<vector<int>> result;
    vector<int> current;
    sumOfSubsetsHelper(arr, target, 0, 0, current, result, totalSum);
    return result;
}

// 6. Optimal Binary Search Tree Keys Selection
int optimalBSTHelper(vector<int>& keys, int start, int end, vector<bool>& selected, 
                    int& minCost, int level) {
    if (start > end) return 0;
    
    int cost = INT_MAX;
    
    for (int i = start; i <= end; i++) {
        if (!selected[i]) {
            selected[i] = true;
            
            int leftCost = optimalBSTHelper(keys, start, i - 1, selected, minCost, level + 1);
            int rightCost = optimalBSTHelper(keys, i + 1, end, selected, minCost, level + 1);
            
            int currentCost = keys[i] * level + leftCost + rightCost;
            cost = min(cost, currentCost);
            
            selected[i] = false;
        }
    }
    
    return cost;
}

// 7. Maximum Product Subarray (Backtracking approach)
void maxProductHelper(vector<int>& nums, int idx, long long currentProduct, long long& maxProduct) {
    if (idx == nums.size()) {
        maxProduct = max(maxProduct, currentProduct);
        return;
    }
    
    // Include current element
    maxProductHelper(nums, idx + 1, currentProduct * nums[idx], maxProduct);
    
    // Start new subarray from current element
    maxProductHelper(nums, idx + 1, nums[idx], maxProduct);
    
    // Skip current element
    if (idx + 1 < nums.size()) {
        maxProductHelper(nums, idx + 1, currentProduct, maxProduct);
    }
}

// 8. Find Maximum Sum with No Two Adjacent Elements
int maxSumNoAdjacentHelper(vector<int>& arr, int idx, bool prevIncluded, int currentSum, int& maxSum) {
    if (idx >= arr.size()) {
        maxSum = max(maxSum, currentSum);
        return maxSum;
    }
    
    // Exclude current element
    maxSumNoAdjacentHelper(arr, idx + 1, false, currentSum, maxSum);
    
    // Include current element (only if previous was not included)
    if (!prevIncluded) {
        maxSumNoAdjacentHelper(arr, idx + 1, true, currentSum + arr[idx], maxSum);
    }
    
    return maxSum;
}

int maxSumNoAdjacent(vector<int>& arr) {
    int maxSum = 0;
    return maxSumNoAdjacentHelper(arr, 0, false, 0, maxSum);
}

// 9. Longest Increasing Subsequence (Backtracking)
void lisHelper(vector<int>& arr, int idx, vector<int>& current, vector<int>& best) {
    if (idx == arr.size()) {
        if (current.size() > best.size()) {
            best = current;
        }
        return;
    }
    
    // Exclude current element
    lisHelper(arr, idx + 1, current, best);
    
    // Include current element (if it maintains increasing order)
    if (current.empty() || arr[idx] > current.back()) {
        current.push_back(arr[idx]);
        lisHelper(arr, idx + 1, current, best);
        current.pop_back();
    }
}

vector<int> longestIncreasingSubsequence(vector<int>& arr) {
    vector<int> current, best;
    lisHelper(arr, 0, current, best);
    return best;
}

// 10. Box Stacking Problem (Backtracking)
struct Box {
    int height, width, depth;
    
    Box(int h, int w, int d) : height(h), width(w), depth(d) {}
};

bool canPlaceOn(Box& top, Box& bottom) {
    return (top.width < bottom.width && top.depth < bottom.depth);
}

int boxStackingHelper(vector<Box>& boxes, int idx, int prevIdx, int currentHeight, int& maxHeight) {
    if (idx == boxes.size()) {
        maxHeight = max(maxHeight, currentHeight);
        return maxHeight;
    }
    
    // Exclude current box
    boxStackingHelper(boxes, idx + 1, prevIdx, currentHeight, maxHeight);
    
    // Include current box (if it can be placed on previous box)
    if (prevIdx == -1 || canPlaceOn(boxes[idx], boxes[prevIdx])) {
        boxStackingHelper(boxes, idx + 1, idx, currentHeight + boxes[idx].height, maxHeight);
    }
    
    return maxHeight;
}

int boxStacking(vector<Box>& boxes) {
    // Sort boxes by base area (width * depth)
    sort(boxes.begin(), boxes.end(), [](Box& a, Box& b) {
        return (a.width * a.depth) > (b.width * b.depth);
    });
    
    int maxHeight = 0;
    return boxStackingHelper(boxes, 0, -1, 0, maxHeight);
}

// 11. Minimum Number of Jumps to Reach End
int minJumpsHelper(vector<int>& arr, int idx, int jumps, int& minJumps) {
    int n = arr.size();
    
    if (idx >= n - 1) {
        minJumps = min(minJumps, jumps);
        return minJumps;
    }
    
    // Pruning
    if (jumps >= minJumps) {
        return minJumps;
    }
    
    // Try all possible jumps from current position
    for (int i = 1; i <= arr[idx] && idx + i < n; i++) {
        minJumpsHelper(arr, idx + i, jumps + 1, minJumps);
    }
    
    return minJumps;
}

int minJumps(vector<int>& arr) {
    if (arr.size() <= 1) return 0;
    if (arr[0] == 0) return -1;
    
    int minJumps = INT_MAX;
    minJumpsHelper(arr, 0, 0, minJumps);
    return (minJumps == INT_MAX) ? -1 : minJumps;
}

// 12. Word Break with All Solutions
void wordBreakHelper(string& s, int idx, unordered_set<string>& wordDict, 
                    string current, vector<string>& result) {
    if (idx == s.length()) {
        current.pop_back(); // Remove trailing space
        result.push_back(current);
        return;
    }
    
    for (int len = 1; len <= s.length() - idx; len++) {
        string word = s.substr(idx, len);
        if (wordDict.count(word)) {
            wordBreakHelper(s, idx + len, wordDict, current + word + " ", result);
        }
    }
}

vector<string> wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> dict(wordDict.begin(), wordDict.end());
    vector<string> result;
    wordBreakHelper(s, 0, dict, "", result);
    return result;
}

// 13. Allocate Minimum Pages
bool isPossible(vector<int>& books, int n, int m, int maxPages) {
    int students = 1, currentPages = 0;
    
    for (int i = 0; i < n; i++) {
        if (books[i] > maxPages) return false;
        
        if (currentPages + books[i] > maxPages) {
            students++;
            currentPages = books[i];
            
            if (students > m) return false;
        } else {
            currentPages += books[i];
        }
    }
    
    return true;
}

int allocateMinimumPages(vector<int>& books, int m) {
    int n = books.size();
    if (m > n) return -1;
    
    int sum = 0, maxBook = 0;
    for (int book : books) {
        sum += book;
        maxBook = max(maxBook, book);
    }
    
    int low = maxBook, high = sum, result = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (isPossible(books, n, m, mid)) {
            result = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    return result;
}

int main() {
    // Test Job Assignment
    cout << "=== Job Assignment Problem ===" << endl;
    vector<vector<int>> cost = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}
    };
    cout << "Minimum cost: " << jobAssignment(cost) << "\n\n";
    
    // Test Traveling Salesman Problem
    cout << "=== Traveling Salesman Problem ===" << endl;
    vector<vector<int>> dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    cout << "Minimum tour cost: " << tsp(dist) << "\n\n";
    
    // Test 0/1 Knapsack
    cout << "=== 0/1 Knapsack ===" << endl;
    vector<int> weights = {2, 3, 4, 5};
    vector<int> values = {3, 4, 5, 6};
    cout << "Maximum value: " << knapsack(weights, values, 8) << "\n\n";
    
    // Test Chromatic Number
    cout << "=== Chromatic Number ===" << endl;
    vector<vector<int>> graph = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };
    cout << "Minimum colors needed: " << chromaticNumber(graph) << "\n\n";
    
    // Test Sum of Subsets
    cout << "=== Sum of Subsets ===" << endl;
    vector<int> arr1 = {3, 5, 6, 7};
    vector<vector<int>> subsets = sumOfSubsets(arr1, 15);
    cout << "Subsets with sum 15: " << subsets.size() << endl;
    
    // Test Max Sum No Adjacent
    cout << "=== Max Sum No Adjacent ===" << endl;
    vector<int> arr2 = {5, 5, 10, 100, 10, 5};
    cout << "Maximum sum: " << maxSumNoAdjacent(arr2) << "\n\n";
    
    // Test Longest Increasing Subsequence
    cout << "=== Longest Increasing Subsequence ===" << endl;
    vector<int> arr3 = {10, 22, 9, 33, 21, 50, 41, 60};
    vector<int> lis = longestIncreasingSubsequence(arr3);
    cout << "LIS length: " << lis.size() << ", Sequence: ";
    for (int x : lis) cout << x << " ";
    cout << "\n\n";
    
    // Test Box Stacking
    cout << "=== Box Stacking ===" << endl;
    vector<Box> boxes = {Box(4, 6, 7), Box(1, 2, 3), Box(4, 5, 6), Box(10, 12, 32)};
    cout << "Maximum height: " << boxStacking(boxes) << "\n\n";
    
    // Test Minimum Jumps
    cout << "=== Minimum Jumps to Reach End ===" << endl;
    vector<int> arr4 = {2, 3, 1, 1, 4};
    cout << "Minimum jumps: " << minJumps(arr4) << "\n\n";
    
    // Test Word Break
    cout << "=== Word Break ===" << endl;
    vector<string> wordDict = {"cat", "cats", "and", "sand", "dog"};
    vector<string> sentences = wordBreak("catsanddog", wordDict);
    cout << "Possible sentences: " << sentences.size() << endl;
    for (string& sentence : sentences) {
        cout << sentence << endl;
    }
    cout << "\n";
    
    // Test Allocate Minimum Pages
    cout << "=== Allocate Minimum Pages ===" << endl;
    vector<int> books = {12, 34, 67, 90};
    cout << "Minimum pages: " << allocateMinimumPages(books, 2) << endl;
    
    return 0;
}

