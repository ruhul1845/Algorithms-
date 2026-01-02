/*
 * Greedy Algorithms - Basic Problems
 * Activity selection, interval scheduling, fractional knapsack
 */

#include <bits/stdc++.h>
using namespace std;

// 1. Activity Selection Problem
int activitySelection(vector<int>& start, vector<int>& end) {
    int n = start.size();
    vector<pair<int, int>> activities;
    
    for (int i = 0; i < n; i++) {
        activities.push_back({end[i], start[i]});
    }
    
    sort(activities.begin(), activities.end());
    
    int count = 1;
    int lastEnd = activities[0].first;
    
    for (int i = 1; i < n; i++) {
        if (activities[i].second >= lastEnd) {
            count++;
            lastEnd = activities[i].first;
        }
    }
    
    return count;
}

// 2. Fractional Knapsack
struct Item {
    int value, weight;
    
    Item(int v, int w) : value(v), weight(w) {}
};

double fractionalKnapsack(int capacity, vector<Item>& items) {
    auto comp = [](Item& a, Item& b) {
        double r1 = (double)a.value / a.weight;
        double r2 = (double)b.value / b.weight;
        return r1 > r2;
    };
    
    sort(items.begin(), items.end(), comp);
    
    double totalValue = 0.0;
    
    for (Item& item : items) {
        if (capacity >= item.weight) {
            totalValue += item.value;
            capacity -= item.weight;
        } else {
            totalValue += item.value * ((double)capacity / item.weight);
            break;
        }
    }
    
    return totalValue;
}

// 3. Minimum Coins (Greedy works for standard denominations)
int minCoins(vector<int>& coins, int amount) {
    sort(coins.rbegin(), coins.rend());
    
    int count = 0;
    for (int coin : coins) {
        if (amount == 0) break;
        
        count += amount / coin;
        amount %= coin;
    }
    
    return amount == 0 ? count : -1;
}

// 4. Jump Game
bool canJump(vector<int>& nums) {
    int maxReach = 0;
    
    for (int i = 0; i < nums.size(); i++) {
        if (i > maxReach) return false;
        maxReach = max(maxReach, i + nums[i]);
    }
    
    return true;
}

// 5. Jump Game II (Minimum Jumps)
int minJumps(vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) return 0;
    
    int jumps = 0, currentEnd = 0, farthest = 0;
    
    for (int i = 0; i < n - 1; i++) {
        farthest = max(farthest, i + nums[i]);
        
        if (i == currentEnd) {
            jumps++;
            currentEnd = farthest;
            
            if (currentEnd >= n - 1) break;
        }
    }
    
    return jumps;
}

// 6. Assign Cookies
int findContentChildren(vector<int>& greed, vector<int>& cookies) {
    sort(greed.begin(), greed.end());
    sort(cookies.begin(), cookies.end());
    
    int child = 0, cookie = 0;
    
    while (child < greed.size() && cookie < cookies.size()) {
        if (cookies[cookie] >= greed[child]) {
            child++;
        }
        cookie++;
    }
    
    return child;
}

// 7. Lemonade Change
bool lemonadeChange(vector<int>& bills) {
    int five = 0, ten = 0;
    
    for (int bill : bills) {
        if (bill == 5) {
            five++;
        } else if (bill == 10) {
            if (five == 0) return false;
            five--;
            ten++;
        } else { // bill == 20
            if (ten > 0 && five > 0) {
                ten--;
                five--;
            } else if (five >= 3) {
                five -= 3;
            } else {
                return false;
            }
        }
    }
    
    return true;
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

// 9. Boats to Save People
int numRescueBoats(vector<int>& people, int limit) {
    sort(people.begin(), people.end());
    
    int left = 0, right = people.size() - 1;
    int boats = 0;
    
    while (left <= right) {
        if (people[left] + people[right] <= limit) {
            left++;
        }
        right--;
        boats++;
    }
    
    return boats;
}

// 10. Task Scheduler
int leastInterval(vector<char>& tasks, int n) {
    vector<int> freq(26, 0);
    for (char task : tasks) {
        freq[task - 'A']++;
    }
    
    sort(freq.rbegin(), freq.rend());
    
    int maxFreq = freq[0];
    int idleTime = (maxFreq - 1) * n;
    
    for (int i = 1; i < 26; i++) {
        idleTime -= min(freq[i], maxFreq - 1);
    }
    
    idleTime = max(0, idleTime);
    
    return tasks.size() + idleTime;
}

int main() {
    // Test Activity Selection
    vector<int> start = {1, 3, 0, 5, 8, 5};
    vector<int> end = {2, 4, 6, 7, 9, 9};
    cout << "Maximum activities: " << activitySelection(start, end) << endl;
    
    // Test Fractional Knapsack
    vector<Item> items = {{60, 10}, {100, 20}, {120, 30}};
    cout << "Max value in knapsack: " << fractionalKnapsack(50, items) << endl;
    
    // Test Jump Game
    vector<int> nums1 = {2, 3, 1, 1, 4};
    cout << "Can jump: " << (canJump(nums1) ? "Yes" : "No") << endl;
    
    // Test Minimum Jumps
    vector<int> nums2 = {2, 3, 1, 1, 4};
    cout << "Minimum jumps: " << minJumps(nums2) << endl;
    
    return 0;
}

