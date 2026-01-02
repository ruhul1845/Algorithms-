/*
    Travelling Salesman Problem (TSP) - Bitmask DP
    Problem: Find shortest route visiting all cities exactly once and returning home.
    
    Time: O(n² * 2ⁿ), Space: O(n * 2ⁿ)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<vector<int>> dist;
    int n;
    
    int solve(int curr, int mask) {
        if (mask == (1 << n) - 1) {
            return dist[curr][0]; // Return to start
        }
        if (dp[curr][mask] != -1) return dp[curr][mask];
        
        int minDist = INT_MAX;
        
        for (int next = 0; next < n; next++) {
            if (!(mask & (1 << next))) {
                int newMask = mask | (1 << next);
                minDist = min(minDist, dist[curr][next] + solve(next, newMask));
            }
        }
        
        return dp[curr][mask] = minDist;
    }
    
public:
    int tsp(vector<vector<int>>& d) {
        dist = d;
        n = dist.size();
        dp.assign(n, vector<int>(1 << n, -1));
        return solve(0, 1); // Start from city 0
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int tsp(vector<vector<int>>& dist) {
        int n = dist.size();
        
        // dp[mask][i] = min cost to reach city i with visited cities = mask
        vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));
        dp[1][0] = 0; // Start at city 0
        
        for (int mask = 1; mask < (1 << n); mask++) {
            for (int curr = 0; curr < n; curr++) {
                if (!(mask & (1 << curr))) continue;
                if (dp[mask][curr] == INT_MAX) continue;
                
                for (int next = 0; next < n; next++) {
                    if (mask & (1 << next)) continue;
                    
                    int newMask = mask | (1 << next);
                    dp[newMask][next] = min(dp[newMask][next], 
                                           dp[mask][curr] + dist[curr][next]);
                }
            }
        }
        
        int fullMask = (1 << n) - 1;
        int minTour = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (dp[fullMask][i] != INT_MAX) {
                minTour = min(minTour, dp[fullMask][i] + dist[i][0]);
            }
        }
        
        return minTour;
    }
    
    // Get the tour
    vector<int> getTour(vector<vector<int>>& dist) {
        int n = dist.size();
        
        vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));
        vector<vector<int>> parent(1 << n, vector<int>(n, -1));
        dp[1][0] = 0;
        
        for (int mask = 1; mask < (1 << n); mask++) {
            for (int curr = 0; curr < n; curr++) {
                if (!(mask & (1 << curr))) continue;
                if (dp[mask][curr] == INT_MAX) continue;
                
                for (int next = 0; next < n; next++) {
                    if (mask & (1 << next)) continue;
                    
                    int newMask = mask | (1 << next);
                    if (dp[mask][curr] + dist[curr][next] < dp[newMask][next]) {
                        dp[newMask][next] = dp[mask][curr] + dist[curr][next];
                        parent[newMask][next] = curr;
                    }
                }
            }
        }
        
        // Find last city
        int fullMask = (1 << n) - 1;
        int minTour = INT_MAX, lastCity = 0;
        for (int i = 0; i < n; i++) {
            if (dp[fullMask][i] != INT_MAX && dp[fullMask][i] + dist[i][0] < minTour) {
                minTour = dp[fullMask][i] + dist[i][0];
                lastCity = i;
            }
        }
        
        // Reconstruct tour
        vector<int> tour;
        int mask = fullMask, curr = lastCity;
        while (curr != -1) {
            tour.push_back(curr);
            int prev = parent[mask][curr];
            mask ^= (1 << curr);
            curr = prev;
        }
        reverse(tour.begin(), tour.end());
        tour.push_back(0); // Return to start
        
        return tour;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter number of cities: ";
    cin >> n;
    
    vector<vector<int>> dist(n, vector<int>(n));
    cout << "Enter distance matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
        }
    }
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.tsp(dist) << endl;
    cout << "Bottom-Up: " << bu.tsp(dist) << endl;
    
    cout << "Tour: ";
    vector<int> tour = bu.getTour(dist);
    for (int city : tour) cout << city << " ";
    cout << endl;
    
    return 0;
}









