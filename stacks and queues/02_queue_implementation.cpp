/*
 * Queue Implementation and Operations
 * Linear Queue, Circular Queue, Deque
 */

#include <bits/stdc++.h>
using namespace std;

// 1. Queue using Array
class ArrayQueue {
    int* arr;
    int front, rear, capacity, count;
    
public:
    ArrayQueue(int size) {
        arr = new int[size];
        capacity = size;
        front = 0;
        rear = -1;
        count = 0;
    }
    
    ~ArrayQueue() {
        delete[] arr;
    }
    
    void enqueue(int x) {
        if (isFull()) {
            cout << "Queue Overflow" << endl;
            return;
        }
        rear = (rear + 1) % capacity;
        arr[rear] = x;
        count++;
    }
    
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow" << endl;
            return -1;
        }
        int val = arr[front];
        front = (front + 1) % capacity;
        count--;
        return val;
    }
    
    int peek() {
        if (isEmpty()) return -1;
        return arr[front];
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    bool isFull() {
        return count == capacity;
    }
    
    int size() {
        return count;
    }
};

// 2. Queue using Linked List
struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

class LinkedQueue {
    Node* front;
    Node* rear;
    int count;
    
public:
    LinkedQueue() : front(nullptr), rear(nullptr), count(0) {}
    
    void enqueue(int x) {
        Node* newNode = new Node(x);
        
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        count++;
    }
    
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow" << endl;
            return -1;
        }
        
        Node* temp = front;
        int val = temp->data;
        front = front->next;
        
        if (front == nullptr) {
            rear = nullptr;
        }
        
        delete temp;
        count--;
        return val;
    }
    
    int peek() {
        if (isEmpty()) return -1;
        return front->data;
    }
    
    bool isEmpty() {
        return front == nullptr;
    }
    
    int size() {
        return count;
    }
};

// 3. Circular Queue
class CircularQueue {
    vector<int> data;
    int front, rear, size, capacity;
    
public:
    CircularQueue(int k) {
        data.resize(k);
        capacity = k;
        front = -1;
        rear = -1;
        size = 0;
    }
    
    bool enQueue(int value) {
        if (isFull()) return false;
        
        if (isEmpty()) {
            front = 0;
        }
        
        rear = (rear + 1) % capacity;
        data[rear] = value;
        size++;
        return true;
    }
    
    bool deQueue() {
        if (isEmpty()) return false;
        
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % capacity;
        }
        size--;
        return true;
    }
    
    int Front() {
        if (isEmpty()) return -1;
        return data[front];
    }
    
    int Rear() {
        if (isEmpty()) return -1;
        return data[rear];
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    bool isFull() {
        return size == capacity;
    }
};

// 4. Queue using Two Stacks
class QueueUsingStacks {
    stack<int> s1, s2;
    
public:
    void enqueue(int x) {
        s1.push(x);
    }
    
    int dequeue() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        
        if (s2.empty()) return -1;
        
        int val = s2.top();
        s2.pop();
        return val;
    }
    
    int peek() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        
        if (s2.empty()) return -1;
        return s2.top();
    }
    
    bool empty() {
        return s1.empty() && s2.empty();
    }
};

// 5. Deque Implementation
class Deque {
    vector<int> arr;
    int front, rear, size, capacity;
    
public:
    Deque(int k) {
        arr.resize(k);
        capacity = k;
        front = -1;
        rear = 0;
        size = 0;
    }
    
    bool insertFront(int value) {
        if (isFull()) return false;
        
        if (front == -1) {
            front = 0;
            rear = 0;
        } else if (front == 0) {
            front = capacity - 1;
        } else {
            front--;
        }
        
        arr[front] = value;
        size++;
        return true;
    }
    
    bool insertLast(int value) {
        if (isFull()) return false;
        
        if (front == -1) {
            front = 0;
            rear = 0;
        } else {
            rear = (rear + 1) % capacity;
        }
        
        arr[rear] = value;
        size++;
        return true;
    }
    
    bool deleteFront() {
        if (isEmpty()) return false;
        
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % capacity;
        }
        size--;
        return true;
    }
    
    bool deleteLast() {
        if (isEmpty()) return false;
        
        if (front == rear) {
            front = -1;
            rear = -1;
        } else if (rear == 0) {
            rear = capacity - 1;
        } else {
            rear--;
        }
        size--;
        return true;
    }
    
    int getFront() {
        if (isEmpty()) return -1;
        return arr[front];
    }
    
    int getRear() {
        if (isEmpty()) return -1;
        return arr[rear];
    }
    
    bool isEmpty() {
        return front == -1;
    }
    
    bool isFull() {
        return size == capacity;
    }
};

int main() {
    // Test Array Queue
    ArrayQueue q(5);
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    
    cout << "Queue front: " << q.peek() << endl;
    cout << "Dequeued: " << q.dequeue() << endl;
    cout << "Queue front now: " << q.peek() << endl;
    
    // Test Circular Queue
    CircularQueue cq(3);
    cq.enQueue(1);
    cq.enQueue(2);
    cq.enQueue(3);
    cout << "\nCircular Queue Front: " << cq.Front() << endl;
    cout << "Circular Queue Rear: " << cq.Rear() << endl;
    
    return 0;
}










