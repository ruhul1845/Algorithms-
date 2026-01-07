/*
    Box Stacking Problem
    Problem: Stack boxes to maximize height. Box can only be placed on
             another if its base is strictly smaller in both dimensions.
    
    Trick: Generate all rotations, sort by base area, then LIS-style DP.
*/

#include <bits/stdc++.h>
using namespace std;

struct Box {
    int h, w, d; // height, width, depth
    int area;    // base area for sorting
};

// ==================== SOLUTION ====================
class Solution {
public:
    int maxStackHeight(vector<tuple<int, int, int>>& boxes) {
        vector<Box> allBoxes;
        
        // Generate all 3 rotations for each box
        for (auto& [h, w, d] : boxes) {
            // Rotation 1: height = h
            allBoxes.push_back({h, max(w, d), min(w, d), max(w, d) * min(w, d)});
            // Rotation 2: height = w
            allBoxes.push_back({w, max(h, d), min(h, d), max(h, d) * min(h, d)});
            // Rotation 3: height = d
            allBoxes.push_back({d, max(h, w), min(h, w), max(h, w) * min(h, w)});
        }
        
        // Sort by base area (decreasing)
        sort(allBoxes.begin(), allBoxes.end(), [](const Box& a, const Box& b) {
            return a.area > b.area;
        });
        
        int n = allBoxes.size();
        
        // dp[i] = max height with box i on top
        vector<int> dp(n);
        for (int i = 0; i < n; i++) {
            dp[i] = allBoxes[i].h;
        }
        
        // LIS-style DP
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (allBoxes[j].w > allBoxes[i].w && allBoxes[j].d > allBoxes[i].d) {
                    dp[i] = max(dp[i], dp[j] + allBoxes[i].h);
                }
            }
        }
        
        return *max_element(dp.begin(), dp.end());
    }
    
    // Get the boxes in stack
    vector<tuple<int, int, int>> getStack(vector<tuple<int, int, int>>& boxes) {
        vector<Box> allBoxes;
        
        for (auto& [h, w, d] : boxes) {
            allBoxes.push_back({h, max(w, d), min(w, d), max(w, d) * min(w, d)});
            allBoxes.push_back({w, max(h, d), min(h, d), max(h, d) * min(h, d)});
            allBoxes.push_back({d, max(h, w), min(h, w), max(h, w) * min(h, w)});
        }
        
        sort(allBoxes.begin(), allBoxes.end(), [](const Box& a, const Box& b) {
            return a.area > b.area;
        });
        
        int n = allBoxes.size();
        vector<int> dp(n), parent(n, -1);
        
        for (int i = 0; i < n; i++) dp[i] = allBoxes[i].h;
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (allBoxes[j].w > allBoxes[i].w && allBoxes[j].d > allBoxes[i].d) {
                    if (dp[j] + allBoxes[i].h > dp[i]) {
                        dp[i] = dp[j] + allBoxes[i].h;
                        parent[i] = j;
                    }
                }
            }
        }
        
        // Find top box
        int maxIdx = 0;
        for (int i = 1; i < n; i++) {
            if (dp[i] > dp[maxIdx]) maxIdx = i;
        }
        
        // Reconstruct stack
        vector<tuple<int, int, int>> stack;
        int curr = maxIdx;
        while (curr != -1) {
            stack.push_back({allBoxes[curr].h, allBoxes[curr].w, allBoxes[curr].d});
            curr = parent[curr];
        }
        reverse(stack.begin(), stack.end());
        
        return stack;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter number of boxes: ";
    cin >> n;
    
    vector<tuple<int, int, int>> boxes(n);
    cout << "Enter dimensions (h w d) for each box:" << endl;
    for (int i = 0; i < n; i++) {
        int h, w, d;
        cin >> h >> w >> d;
        boxes[i] = {h, w, d};
    }
    
    Solution sol;
    
    cout << "\n--- Results ---" << endl;
    cout << "Maximum Height: " << sol.maxStackHeight(boxes) << endl;
    
    cout << "Stack (bottom to top):" << endl;
    auto stack = sol.getStack(boxes);
    for (auto& [h, w, d] : stack) {
        cout << "  h=" << h << " w=" << w << " d=" << d << endl;
    }
    
    return 0;
}


















