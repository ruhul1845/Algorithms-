/*
 * Greedy - Interval Problems
 * Merge intervals, meeting rooms, non-overlapping intervals
 */

#include <bits/stdc++.h>
using namespace std;

// 1. Merge Intervals
vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};
    
    sort(intervals.begin(), intervals.end());
    
    vector<vector<int>> merged;
    merged.push_back(intervals[0]);
    
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] <= merged.back()[1]) {
            merged.back()[1] = max(merged.back()[1], intervals[i][1]);
        } else {
            merged.push_back(intervals[i]);
        }
    }
    
    return merged;
}

// 2. Insert Interval
vector<vector<int>> insertInterval(vector<vector<int>>& intervals, vector<int>& newInterval) {
    vector<vector<int>> result;
    int i = 0, n = intervals.size();
    
    // Add all intervals before newInterval
    while (i < n && intervals[i][1] < newInterval[0]) {
        result.push_back(intervals[i]);
        i++;
    }
    
    // Merge overlapping intervals
    while (i < n && intervals[i][0] <= newInterval[1]) {
        newInterval[0] = min(newInterval[0], intervals[i][0]);
        newInterval[1] = max(newInterval[1], intervals[i][1]);
        i++;
    }
    result.push_back(newInterval);
    
    // Add remaining intervals
    while (i < n) {
        result.push_back(intervals[i]);
        i++;
    }
    
    return result;
}

// 3. Non-overlapping Intervals
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) return 0;
    
    sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
        return a[1] < b[1];
    });
    
    int count = 0;
    int end = intervals[0][1];
    
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] < end) {
            count++;
        } else {
            end = intervals[i][1];
        }
    }
    
    return count;
}

// 4. Meeting Rooms
bool canAttendMeetings(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] < intervals[i-1][1]) {
            return false;
        }
    }
    
    return true;
}

// 5. Meeting Rooms II (Minimum Meeting Rooms)
int minMeetingRooms(vector<vector<int>>& intervals) {
    if (intervals.empty()) return 0;
    
    vector<int> start, end;
    for (auto& interval : intervals) {
        start.push_back(interval[0]);
        end.push_back(interval[1]);
    }
    
    sort(start.begin(), start.end());
    sort(end.begin(), end.end());
    
    int rooms = 0, maxRooms = 0;
    int i = 0, j = 0;
    
    while (i < start.size()) {
        if (start[i] < end[j]) {
            rooms++;
            maxRooms = max(maxRooms, rooms);
            i++;
        } else {
            rooms--;
            j++;
        }
    }
    
    return maxRooms;
}

// 6. Minimum Arrows to Burst Balloons
int findMinArrowShots(vector<vector<int>>& points) {
    if (points.empty()) return 0;
    
    sort(points.begin(), points.end(), [](auto& a, auto& b) {
        return a[1] < b[1];
    });
    
    int arrows = 1;
    int end = points[0][1];
    
    for (int i = 1; i < points.size(); i++) {
        if (points[i][0] > end) {
            arrows++;
            end = points[i][1];
        }
    }
    
    return arrows;
}

// 7. Car Pooling
bool carPooling(vector<vector<int>>& trips, int capacity) {
    map<int, int> timeline;
    
    for (auto& trip : trips) {
        timeline[trip[1]] += trip[0];
        timeline[trip[2]] -= trip[0];
    }
    
    int passengers = 0;
    for (auto& [time, change] : timeline) {
        passengers += change;
        if (passengers > capacity) {
            return false;
        }
    }
    
    return true;
}

// 8. Interval List Intersections
vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
    vector<vector<int>> result;
    int i = 0, j = 0;
    
    while (i < A.size() && j < B.size()) {
        int start = max(A[i][0], B[j][0]);
        int end = min(A[i][1], B[j][1]);
        
        if (start <= end) {
            result.push_back({start, end});
        }
        
        if (A[i][1] < B[j][1]) {
            i++;
        } else {
            j++;
        }
    }
    
    return result;
}

// 9. Maximum CPU Load
struct Job {
    int start, end, load;
};

int maxCPULoad(vector<Job>& jobs) {
    sort(jobs.begin(), jobs.end(), [](Job& a, Job& b) {
        return a.start < b.start;
    });
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    int maxLoad = 0, currentLoad = 0;
    
    for (Job& job : jobs) {
        while (!pq.empty() && pq.top().first <= job.start) {
            currentLoad -= pq.top().second;
            pq.pop();
        }
        
        pq.push({job.end, job.load});
        currentLoad += job.load;
        maxLoad = max(maxLoad, currentLoad);
    }
    
    return maxLoad;
}

// 10. Employee Free Time
struct Interval {
    int start, end;
    Interval(int s, int e) : start(s), end(e) {}
};

vector<Interval> employeeFreeTime(vector<vector<Interval>>& schedule) {
    vector<Interval> allIntervals;
    
    for (auto& employee : schedule) {
        for (auto& interval : employee) {
            allIntervals.push_back(interval);
        }
    }
    
    sort(allIntervals.begin(), allIntervals.end(), [](Interval& a, Interval& b) {
        return a.start < b.start;
    });
    
    vector<Interval> freeTime;
    int prevEnd = allIntervals[0].end;
    
    for (int i = 1; i < allIntervals.size(); i++) {
        if (allIntervals[i].start > prevEnd) {
            freeTime.push_back(Interval(prevEnd, allIntervals[i].start));
        }
        prevEnd = max(prevEnd, allIntervals[i].end);
    }
    
    return freeTime;
}

int main() {
    // Test Merge Intervals
    vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    vector<vector<int>> merged = mergeIntervals(intervals);
    cout << "Merged intervals: ";
    for (auto& interval : merged) {
        cout << "[" << interval[0] << "," << interval[1] << "] ";
    }
    cout << endl;
    
    // Test Non-overlapping Intervals
    vector<vector<int>> intervals2 = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
    cout << "Intervals to remove: " << eraseOverlapIntervals(intervals2) << endl;
    
    // Test Meeting Rooms II
    vector<vector<int>> meetings = {{0, 30}, {5, 10}, {15, 20}};
    cout << "Minimum meeting rooms: " << minMeetingRooms(meetings) << endl;
    
    return 0;
}










