/*
    Maximum Profit in Job Scheduling
    Problem: Non-overlapping jobs with start, end, profit.
             Maximize profit.
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<int> dp;
    vector<tuple<int, int, int>> jobs; // {start, end, profit}
    
    int findNext(int currEnd, int n) {
        int lo = 0, hi = n - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (get<0>(jobs[mid]) < currEnd) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        return get<0>(jobs[lo]) >= currEnd ? lo : n;
    }
    
    int solve(int idx) {
        int n = jobs.size();
        if (idx >= n) return 0;
        if (dp[idx] != -1) return dp[idx];
        
        // Skip current job
        int skip = solve(idx + 1);
        
        // Take current job
        int nextIdx = findNext(get<1>(jobs[idx]), n);
        int take = get<2>(jobs[idx]) + solve(nextIdx);
        
        return dp[idx] = max(skip, take);
    }
    
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        jobs.resize(n);
        
        for (int i = 0; i < n; i++) {
            jobs[i] = {startTime[i], endTime[i], profit[i]};
        }
        
        sort(jobs.begin(), jobs.end());
        
        dp.assign(n, -1);
        return solve(0);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<tuple<int, int, int>> jobs(n);
        
        for (int i = 0; i < n; i++) {
            jobs[i] = {endTime[i], startTime[i], profit[i]};
        }
        
        sort(jobs.begin(), jobs.end()); // Sort by end time
        
        // dp[i] = {endTime, maxProfit} at position i
        vector<pair<int, int>> dp;
        dp.push_back({0, 0});
        
        for (auto& [end, start, p] : jobs) {
            // Binary search for latest job that ends <= start
            int lo = 0, hi = dp.size() - 1;
            while (lo < hi) {
                int mid = (lo + hi + 1) / 2;
                if (dp[mid].first <= start) {
                    lo = mid;
                } else {
                    hi = mid - 1;
                }
            }
            
            int newProfit = dp[lo].second + p;
            if (newProfit > dp.back().second) {
                dp.push_back({end, newProfit});
            }
        }
        
        return dp.back().second;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter number of jobs: ";
    cin >> n;
    
    vector<int> startTime(n), endTime(n), profit(n);
    cout << "Enter start times: ";
    for (int i = 0; i < n; i++) cin >> startTime[i];
    cout << "Enter end times: ";
    for (int i = 0; i < n; i++) cin >> endTime[i];
    cout << "Enter profits: ";
    for (int i = 0; i < n; i++) cin >> profit[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.jobScheduling(startTime, endTime, profit) << endl;
    cout << "Bottom-Up: " << bu.jobScheduling(startTime, endTime, profit) << endl;
    
    return 0;
}


















