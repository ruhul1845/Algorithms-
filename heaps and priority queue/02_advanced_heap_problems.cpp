/*
 * Advanced Heap Problems
 * Sliding window, meeting rooms, task scheduling
 */

#include <bits/stdc++.h>
using namespace std;

// 1. Sliding Window Median
vector<double> medianSlidingWindow(vector<int>& nums, int k) {
    multiset<int> window(nums.begin(), nums.begin() + k);
    auto mid = next(window.begin(), k / 2);
    vector<double> medians;
    
    for (int i = k; ; i++) {
        medians.push_back((double(*mid) + *prev(mid, 1 - k % 2)) / 2);
        
        if (i == nums.size()) break;
        
        window.insert(nums[i]);
        if (nums[i] < *mid) mid--;
        
        if (nums[i - k] <= *mid) mid++;
        window.erase(window.lower_bound(nums[i - k]));
    }
    
    return medians;
}

// 2. Task Scheduler
int leastInterval(vector<char>& tasks, int n) {
    vector<int> freq(26, 0);
    for (char task : tasks) {
        freq[task - 'A']++;
    }
    
    priority_queue<int> maxHeap;
    for (int f : freq) {
        if (f > 0) maxHeap.push(f);
    }
    
    int time = 0;
    
    while (!maxHeap.empty()) {
        vector<int> temp;
        
        for (int i = 0; i <= n; i++) {
            if (!maxHeap.empty()) {
                int f = maxHeap.top();
                maxHeap.pop();
                temp.push_back(f - 1);
            }
        }
        
        for (int f : temp) {
            if (f > 0) maxHeap.push(f);
        }
        
        time += maxHeap.empty() ? temp.size() : n + 1;
    }
    
    return time;
}

// 3. Meeting Rooms II (Minimum Meeting Rooms)
int minMeetingRooms(vector<vector<int>>& intervals) {
    if (intervals.empty()) return 0;
    
    sort(intervals.begin(), intervals.end());
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    minHeap.push(intervals[0][1]);
    
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] >= minHeap.top()) {
            minHeap.pop();
        }
        
        minHeap.push(intervals[i][1]);
    }
    
    return minHeap.size();
}

// 4. Reorganize String
string reorganizeString(string s) {
    unordered_map<char, int> freq;
    for (char c : s) freq[c]++;
    
    priority_queue<pair<int, char>> maxHeap;
    for (auto& p : freq) {
        maxHeap.push({p.second, p.first});
    }
    
    string result = "";
    pair<int, char> prev = {-1, '#'};
    
    while (!maxHeap.empty()) {
        auto curr = maxHeap.top();
        maxHeap.pop();
        
        result += curr.second;
        
        if (prev.first > 0) {
            maxHeap.push(prev);
        }
        
        curr.first--;
        prev = curr;
    }
    
    return result.length() == s.length() ? result : "";
}

// 5. K Closest Points to Origin
vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    auto comp = [](vector<int>& a, vector<int>& b) {
        return a[0] * a[0] + a[1] * a[1] < b[0] * b[0] + b[1] * b[1];
    };
    
    priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> maxHeap(comp);
    
    for (auto& point : points) {
        maxHeap.push(point);
        if (maxHeap.size() > k) {
            maxHeap.pop();
        }
    }
    
    vector<vector<int>> result;
    while (!maxHeap.empty()) {
        result.push_back(maxHeap.top());
        maxHeap.pop();
    }
    
    return result;
}

// 6. Smallest Range Covering Elements from K Lists
vector<int> smallestRange(vector<vector<int>>& nums) {
    auto comp = [](pair<int, pair<int, int>>& a, pair<int, pair<int, int>>& b) {
        return a.first > b.first;
    };
    
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, decltype(comp)> minHeap(comp);
    
    int maxVal = INT_MIN;
    
    for (int i = 0; i < nums.size(); i++) {
        minHeap.push({nums[i][0], {i, 0}});
        maxVal = max(maxVal, nums[i][0]);
    }
    
    int rangeStart = 0, rangeEnd = INT_MAX;
    
    while (minHeap.size() == nums.size()) {
        auto curr = minHeap.top();
        minHeap.pop();
        
        int minVal = curr.first;
        int listIdx = curr.second.first;
        int elemIdx = curr.second.second;
        
        if (maxVal - minVal < rangeEnd - rangeStart) {
            rangeStart = minVal;
            rangeEnd = maxVal;
        }
        
        if (elemIdx + 1 < nums[listIdx].size()) {
            int nextVal = nums[listIdx][elemIdx + 1];
            minHeap.push({nextVal, {listIdx, elemIdx + 1}});
            maxVal = max(maxVal, nextVal);
        }
    }
    
    return {rangeStart, rangeEnd};
}

// 7. IPO (Maximize Capital)
int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
    int n = profits.size();
    vector<pair<int, int>> projects;
    
    for (int i = 0; i < n; i++) {
        projects.push_back({capital[i], profits[i]});
    }
    
    sort(projects.begin(), projects.end());
    
    priority_queue<int> maxHeap;
    int i = 0;
    
    for (int j = 0; j < k; j++) {
        while (i < n && projects[i].first <= w) {
            maxHeap.push(projects[i].second);
            i++;
        }
        
        if (maxHeap.empty()) break;
        
        w += maxHeap.top();
        maxHeap.pop();
    }
    
    return w;
}

// 8. Trapping Rain Water II
int trapRainWater(vector<vector<int>>& heightMap) {
    if (heightMap.empty()) return 0;
    
    int m = heightMap.size(), n = heightMap[0].size();
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> minHeap;
    
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    
    // Add boundary cells
    for (int i = 0; i < m; i++) {
        minHeap.push({heightMap[i][0], {i, 0}});
        minHeap.push({heightMap[i][n-1], {i, n-1}});
        visited[i][0] = visited[i][n-1] = true;
    }
    
    for (int j = 1; j < n - 1; j++) {
        minHeap.push({heightMap[0][j], {0, j}});
        minHeap.push({heightMap[m-1][j], {m-1, j}});
        visited[0][j] = visited[m-1][j] = true;
    }
    
    int water = 0;
    int maxHeight = 0;
    int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    
    while (!minHeap.empty()) {
        auto curr = minHeap.top();
        minHeap.pop();
        
        int height = curr.first;
        int x = curr.second.first;
        int y = curr.second.second;
        
        maxHeight = max(maxHeight, height);
        
        for (auto& dir : dirs) {
            int nx = x + dir[0];
            int ny = y + dir[1];
            
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && !visited[nx][ny]) {
                visited[nx][ny] = true;
                water += max(0, maxHeight - heightMap[nx][ny]);
                minHeap.push({heightMap[nx][ny], {nx, ny}});
            }
        }
    }
    
    return water;
}

// 9. Minimum Cost to Hire K Workers
double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
    int n = quality.size();
    vector<pair<double, int>> workers;
    
    for (int i = 0; i < n; i++) {
        workers.push_back({(double)wage[i] / quality[i], quality[i]});
    }
    
    sort(workers.begin(), workers.end());
    
    double minCost = DBL_MAX;
    int qualitySum = 0;
    priority_queue<int> maxHeap;
    
    for (auto& worker : workers) {
        double ratio = worker.first;
        int q = worker.second;
        
        maxHeap.push(q);
        qualitySum += q;
        
        if (maxHeap.size() > k) {
            qualitySum -= maxHeap.top();
            maxHeap.pop();
        }
        
        if (maxHeap.size() == k) {
            minCost = min(minCost, qualitySum * ratio);
        }
    }
    
    return minCost;
}

// 10. Kth Smallest Element in Sorted Matrix
int kthSmallestMatrix(vector<vector<int>>& matrix, int k) {
    int n = matrix.size();
    
    auto comp = [](pair<int, pair<int, int>>& a, pair<int, pair<int, int>>& b) {
        return a.first > b.first;
    };
    
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, decltype(comp)> minHeap(comp);
    
    for (int i = 0; i < min(n, k); i++) {
        minHeap.push({matrix[i][0], {i, 0}});
    }
    
    int result = 0;
    
    for (int i = 0; i < k; i++) {
        auto curr = minHeap.top();
        minHeap.pop();
        
        result = curr.first;
        int row = curr.second.first;
        int col = curr.second.second;
        
        if (col + 1 < n) {
            minHeap.push({matrix[row][col + 1], {row, col + 1}});
        }
    }
    
    return result;
}

int main() {
    // Test Task Scheduler
    vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
    cout << "Minimum time for tasks: " << leastInterval(tasks, 2) << endl;
    
    // Test Meeting Rooms II
    vector<vector<int>> meetings = {{0, 30}, {5, 10}, {15, 20}};
    cout << "Minimum meeting rooms: " << minMeetingRooms(meetings) << endl;
    
    // Test Reorganize String
    cout << "Reorganized 'aab': " << reorganizeString("aab") << endl;
    
    // Test K Closest Points
    vector<vector<int>> points = {{1, 3}, {-2, 2}, {5, 8}, {0, 1}};
    vector<vector<int>> closest = kClosest(points, 2);
    cout << "2 closest points: ";
    for (auto& p : closest) {
        cout << "[" << p[0] << "," << p[1] << "] ";
    }
    cout << endl;
    
    return 0;
}

