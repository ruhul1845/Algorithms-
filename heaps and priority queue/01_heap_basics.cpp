/*
 * Heap - Basic Operations and Implementation
 * Min Heap, Max Heap, Priority Queue
 */

#include <bits/stdc++.h>
using namespace std;

// 1. Min Heap Implementation
class MinHeap {
    vector<int> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] > heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }
    
    void heapifyDown(int i) {
        int minIdx = i;
        int left = leftChild(i);
        int right = rightChild(i);
        
        if (left < heap.size() && heap[left] < heap[minIdx]) {
            minIdx = left;
        }
        
        if (right < heap.size() && heap[right] < heap[minIdx]) {
            minIdx = right;
        }
        
        if (minIdx != i) {
            swap(heap[i], heap[minIdx]);
            heapifyDown(minIdx);
        }
    }
    
public:
    void insert(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }
    
    int extractMin() {
        if (heap.empty()) return -1;
        
        int minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty()) {
            heapifyDown(0);
        }
        
        return minVal;
    }
    
    int getMin() {
        return heap.empty() ? -1 : heap[0];
    }
    
    int size() {
        return heap.size();
    }
    
    bool empty() {
        return heap.empty();
    }
    
    void print() {
        for (int x : heap) cout << x << " ";
        cout << endl;
    }
};

// 2. Max Heap Implementation
class MaxHeap {
    vector<int> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }
    
    void heapifyDown(int i) {
        int maxIdx = i;
        int left = leftChild(i);
        int right = rightChild(i);
        
        if (left < heap.size() && heap[left] > heap[maxIdx]) {
            maxIdx = left;
        }
        
        if (right < heap.size() && heap[right] > heap[maxIdx]) {
            maxIdx = right;
        }
        
        if (maxIdx != i) {
            swap(heap[i], heap[maxIdx]);
            heapifyDown(maxIdx);
        }
    }
    
public:
    void insert(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }
    
    int extractMax() {
        if (heap.empty()) return -1;
        
        int maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty()) {
            heapifyDown(0);
        }
        
        return maxVal;
    }
    
    int getMax() {
        return heap.empty() ? -1 : heap[0];
    }
    
    int size() {
        return heap.size();
    }
    
    bool empty() {
        return heap.empty();
    }
};

// 3. Kth Largest Element
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    for (int num : nums) {
        minHeap.push(num);
        if (minHeap.size() > k) {
            minHeap.pop();
        }
    }
    
    return minHeap.top();
}

// 4. Kth Smallest Element
int kthSmallest(vector<int>& nums, int k) {
    priority_queue<int> maxHeap;
    
    for (int num : nums) {
        maxHeap.push(num);
        if (maxHeap.size() > k) {
            maxHeap.pop();
        }
    }
    
    return maxHeap.top();
}

// 5. Top K Frequent Elements
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for (int num : nums) {
        freq[num]++;
    }
    
    auto comp = [](pair<int, int>& a, pair<int, int>& b) {
        return a.second > b.second;
    };
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> minHeap(comp);
    
    for (auto& p : freq) {
        minHeap.push(p);
        if (minHeap.size() > k) {
            minHeap.pop();
        }
    }
    
    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().first);
        minHeap.pop();
    }
    
    return result;
}

// 6. Merge K Sorted Lists (using heap)
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    auto comp = [](ListNode* a, ListNode* b) { return a->val > b->val; };
    priority_queue<ListNode*, vector<ListNode*>, decltype(comp)> minHeap(comp);
    
    for (ListNode* list : lists) {
        if (list) minHeap.push(list);
    }
    
    ListNode dummy(0);
    ListNode* tail = &dummy;
    
    while (!minHeap.empty()) {
        ListNode* node = minHeap.top();
        minHeap.pop();
        
        tail->next = node;
        tail = tail->next;
        
        if (node->next) {
            minHeap.push(node->next);
        }
    }
    
    return dummy.next;
}

// 7. Sort Nearly Sorted Array
vector<int> sortNearlySorted(vector<int>& arr, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    vector<int> result;
    
    for (int i = 0; i < arr.size(); i++) {
        minHeap.push(arr[i]);
        
        if (minHeap.size() > k) {
            result.push_back(minHeap.top());
            minHeap.pop();
        }
    }
    
    while (!minHeap.empty()) {
        result.push_back(minHeap.top());
        minHeap.pop();
    }
    
    return result;
}

// 8. Connect Ropes with Minimum Cost
int connectRopes(vector<int>& ropes) {
    priority_queue<int, vector<int>, greater<int>> minHeap(ropes.begin(), ropes.end());
    
    int totalCost = 0;
    
    while (minHeap.size() > 1) {
        int first = minHeap.top(); minHeap.pop();
        int second = minHeap.top(); minHeap.pop();
        
        int cost = first + second;
        totalCost += cost;
        
        minHeap.push(cost);
    }
    
    return totalCost;
}

// 9. Find Median in Stream
class MedianFinder {
    priority_queue<int> maxHeap; // Left half
    priority_queue<int, vector<int>, greater<int>> minHeap; // Right half
    
public:
    void addNum(int num) {
        if (maxHeap.empty() || num <= maxHeap.top()) {
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }
        
        // Balance heaps
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() {
        if (maxHeap.size() == minHeap.size()) {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }
        return maxHeap.top();
    }
};

// 10. Ugly Number II
int nthUglyNumber(int n) {
    priority_queue<long, vector<long>, greater<long>> minHeap;
    unordered_set<long> seen;
    
    minHeap.push(1);
    seen.insert(1);
    
    long ugly = 1;
    vector<int> primes = {2, 3, 5};
    
    for (int i = 0; i < n; i++) {
        ugly = minHeap.top();
        minHeap.pop();
        
        for (int prime : primes) {
            long next = ugly * prime;
            if (seen.find(next) == seen.end()) {
                minHeap.push(next);
                seen.insert(next);
            }
        }
    }
    
    return ugly;
}

int main() {
    // Test Min Heap
    MinHeap minHeap;
    minHeap.insert(5);
    minHeap.insert(3);
    minHeap.insert(7);
    minHeap.insert(1);
    
    cout << "Min Heap: ";
    minHeap.print();
    cout << "Extract min: " << minHeap.extractMin() << endl;
    
    // Test Kth Largest
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    cout << "2nd largest element: " << findKthLargest(nums, 2) << endl;
    
    // Test Top K Frequent
    vector<int> nums2 = {1, 1, 1, 2, 2, 3};
    vector<int> topK = topKFrequent(nums2, 2);
    cout << "Top 2 frequent: ";
    for (int x : topK) cout << x << " ";
    cout << endl;
    
    // Test Median Finder
    MedianFinder mf;
    mf.addNum(1);
    mf.addNum(2);
    cout << "Median after adding 1, 2: " << mf.findMedian() << endl;
    mf.addNum(3);
    cout << "Median after adding 3: " << mf.findMedian() << endl;
    
    return 0;
}

