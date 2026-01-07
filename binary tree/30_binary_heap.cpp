/*
    Binary Heap
    ===========
    
    A complete binary tree that satisfies heap property:
    - Max Heap: parent >= children
    - Min Heap: parent <= children
    
    Time Complexity:
    - Insert: O(log n)
    - Extract: O(log n)
    - Peek: O(1)
    - Heapify: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

// Max Heap Implementation
class MaxHeap {
    vector<int> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] < heap[i]) {
            swap(heap[parent(i)], heap[i]);
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
        if (heap.empty()) return INT_MIN;
        
        int maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty()) heapifyDown(0);
        
        return maxVal;
    }
    
    int getMax() {
        return heap.empty() ? INT_MIN : heap[0];
    }
    
    void buildHeap(vector<int>& arr) {
        heap = arr;
        for (int i = heap.size() / 2 - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }
    
    bool empty() { return heap.empty(); }
    int size() { return heap.size(); }
};

// Min Heap Implementation
class MinHeap {
    vector<int> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] > heap[i]) {
            swap(heap[parent(i)], heap[i]);
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
        if (heap.empty()) return INT_MAX;
        
        int minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty()) heapifyDown(0);
        
        return minVal;
    }
    
    int getMin() { return heap.empty() ? INT_MAX : heap[0]; }
    bool empty() { return heap.empty(); }
    int size() { return heap.size(); }
};

// Heap Sort
void heapSort(vector<int>& arr) {
    int n = arr.size();
    
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        function<void(int, int)> heapify = [&](int idx, int size) {
            int largest = idx;
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;
            
            if (left < size && arr[left] > arr[largest]) largest = left;
            if (right < size && arr[right] > arr[largest]) largest = right;
            
            if (largest != idx) {
                swap(arr[idx], arr[largest]);
                heapify(largest, size);
            }
        };
        heapify(i, n);
    }
    
    // Extract elements
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        function<void(int, int)> heapify = [&](int idx, int size) {
            int largest = idx;
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;
            
            if (left < size && arr[left] > arr[largest]) largest = left;
            if (right < size && arr[right] > arr[largest]) largest = right;
            
            if (largest != idx) {
                swap(arr[idx], arr[largest]);
                heapify(largest, size);
            }
        };
        heapify(0, i);
    }
}

// Kth Largest Element
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

// Merge K Sorted Arrays
vector<int> mergeKSorted(vector<vector<int>>& arrays) {
    vector<int> result;
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
    
    for (int i = 0; i < arrays.size(); i++) {
        if (!arrays[i].empty()) {
            pq.push({arrays[i][0], i, 0});
        }
    }
    
    while (!pq.empty()) {
        auto [val, arrIdx, elemIdx] = pq.top();
        pq.pop();
        
        result.push_back(val);
        
        if (elemIdx + 1 < arrays[arrIdx].size()) {
            pq.push({arrays[arrIdx][elemIdx + 1], arrIdx, elemIdx + 1});
        }
    }
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << "=== Binary Heap ===" << endl;
    
    // Max Heap
    MaxHeap maxHeap;
    vector<int> vals = {3, 1, 6, 5, 2, 4};
    
    cout << "\nInserting: 3 1 6 5 2 4" << endl;
    for (int v : vals) maxHeap.insert(v);
    
    cout << "Max Heap extract order: ";
    while (!maxHeap.empty()) {
        cout << maxHeap.extractMax() << " ";
    }
    cout << endl;
    
    // Min Heap
    MinHeap minHeap;
    for (int v : vals) minHeap.insert(v);
    
    cout << "Min Heap extract order: ";
    while (!minHeap.empty()) {
        cout << minHeap.extractMin() << " ";
    }
    cout << endl;
    
    // Heap Sort
    vector<int> arr = {5, 2, 8, 1, 9, 3};
    cout << "\nArray: 5 2 8 1 9 3" << endl;
    heapSort(arr);
    cout << "After heap sort: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    // Kth Largest
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    cout << "\n2nd largest in [3,2,1,5,6,4]: " << findKthLargest(nums, 2) << endl;
    
    // Merge K Sorted Arrays
    vector<vector<int>> arrays = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
    cout << "\nMerged K sorted arrays: ";
    for (int x : mergeKSorted(arrays)) cout << x << " ";
    cout << endl;
    
    return 0;
}
















