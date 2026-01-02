/*
 * Linked List - Advanced Problems
 * Complex manipulations and algorithms
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 1. Merge Two Sorted Lists
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    
    while (l1 && l2) {
        if (l1->val < l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}

// 2. Merge K Sorted Lists
ListNode* mergeKLists(vector<ListNode*>& lists) {
    auto comp = [](ListNode* a, ListNode* b) { return a->val > b->val; };
    priority_queue<ListNode*, vector<ListNode*>, decltype(comp)> pq(comp);
    
    for (ListNode* list : lists) {
        if (list) pq.push(list);
    }
    
    ListNode dummy(0);
    ListNode* tail = &dummy;
    
    while (!pq.empty()) {
        ListNode* node = pq.top();
        pq.pop();
        
        tail->next = node;
        tail = tail->next;
        
        if (node->next) {
            pq.push(node->next);
        }
    }
    
    return dummy.next;
}

// 3. Reverse Nodes in K-Group
ListNode* reverseKGroup(ListNode* head, int k) {
    if (!head || k == 1) return head;
    
    ListNode dummy(0);
    dummy.next = head;
    
    ListNode* prevGroupEnd = &dummy;
    ListNode* curr = head;
    
    while (curr) {
        // Check if k nodes available
        ListNode* temp = curr;
        int count = 0;
        while (temp && count < k) {
            temp = temp->next;
            count++;
        }
        
        if (count < k) break;
        
        // Reverse k nodes
        ListNode* prev = prevGroupEnd;
        ListNode* groupStart = curr;
        
        for (int i = 0; i < k; i++) {
            ListNode* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }
        
        prevGroupEnd->next = prev;
        groupStart->next = curr;
        prevGroupEnd = groupStart;
    }
    
    return dummy.next;
}

// 4. Copy List with Random Pointer
struct RandomNode {
    int val;
    RandomNode* next;
    RandomNode* random;
    RandomNode(int x) : val(x), next(nullptr), random(nullptr) {}
};

RandomNode* copyRandomList(RandomNode* head) {
    if (!head) return nullptr;
    
    unordered_map<RandomNode*, RandomNode*> oldToNew;
    
    // First pass: create nodes
    RandomNode* curr = head;
    while (curr) {
        oldToNew[curr] = new RandomNode(curr->val);
        curr = curr->next;
    }
    
    // Second pass: connect pointers
    curr = head;
    while (curr) {
        oldToNew[curr]->next = oldToNew[curr->next];
        oldToNew[curr]->random = oldToNew[curr->random];
        curr = curr->next;
    }
    
    return oldToNew[head];
}

// 5. Flatten a Multilevel Doubly Linked List
struct MultiNode {
    int val;
    MultiNode* prev;
    MultiNode* next;
    MultiNode* child;
    MultiNode(int x) : val(x), prev(nullptr), next(nullptr), child(nullptr) {}
};

MultiNode* flatten(MultiNode* head) {
    if (!head) return nullptr;
    
    MultiNode* curr = head;
    while (curr) {
        if (curr->child) {
            MultiNode* next = curr->next;
            MultiNode* child = flatten(curr->child);
            
            curr->next = child;
            child->prev = curr;
            curr->child = nullptr;
            
            // Find tail of child list
            while (curr->next) {
                curr = curr->next;
            }
            
            if (next) {
                curr->next = next;
                next->prev = curr;
            }
        }
        curr = curr->next;
    }
    return head;
}

// 6. Add Two Numbers (represented as linked lists)
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    int carry = 0;
    
    while (l1 || l2 || carry) {
        int sum = carry;
        if (l1) {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2) {
            sum += l2->val;
            l2 = l2->next;
        }
        
        carry = sum / 10;
        tail->next = new ListNode(sum % 10);
        tail = tail->next;
    }
    
    return dummy.next;
}

// 7. Sort List (Merge Sort)
ListNode* sortList(ListNode* head) {
    if (!head || !head->next) return head;
    
    // Find middle
    ListNode* slow = head;
    ListNode* fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    ListNode* mid = slow->next;
    slow->next = nullptr;
    
    // Recursively sort both halves
    ListNode* left = sortList(head);
    ListNode* right = sortList(mid);
    
    // Merge
    return mergeTwoLists(left, right);
}

// 8. Partition List
ListNode* partition(ListNode* head, int x) {
    ListNode lessHead(0), greaterHead(0);
    ListNode* less = &lessHead;
    ListNode* greater = &greaterHead;
    
    while (head) {
        if (head->val < x) {
            less->next = head;
            less = less->next;
        } else {
            greater->next = head;
            greater = greater->next;
        }
        head = head->next;
    }
    
    greater->next = nullptr;
    less->next = greaterHead.next;
    
    return lessHead.next;
}

// 9. Rotate List
ListNode* rotateRight(ListNode* head, int k) {
    if (!head || !head->next || k == 0) return head;
    
    // Find length
    int len = 1;
    ListNode* tail = head;
    while (tail->next) {
        tail = tail->next;
        len++;
    }
    
    k = k % len;
    if (k == 0) return head;
    
    // Find new tail
    ListNode* newTail = head;
    for (int i = 0; i < len - k - 1; i++) {
        newTail = newTail->next;
    }
    
    ListNode* newHead = newTail->next;
    newTail->next = nullptr;
    tail->next = head;
    
    return newHead;
}

void printList(ListNode* head) {
    while (head) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

int main() {
    // Test Merge Two Sorted Lists
    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(2);
    l1->next->next = new ListNode(4);
    
    ListNode* l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);
    
    cout << "List 1: ";
    printList(l1);
    cout << "List 2: ";
    printList(l2);
    
    ListNode* merged = mergeTwoLists(l1, l2);
    cout << "Merged: ";
    printList(merged);
    
    return 0;
}

