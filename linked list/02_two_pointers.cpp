/*
 * Linked List - Two Pointer Techniques
 * Fast-slow pointer, cycle detection, finding middle
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 1. Find Middle of Linked List
ListNode* findMiddle(ListNode* head) {
    if (!head) return nullptr;
    
    ListNode* slow = head;
    ListNode* fast = head;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// 2. Detect Cycle (Floyd's Algorithm)
bool hasCycle(ListNode* head) {
    if (!head) return false;
    
    ListNode* slow = head;
    ListNode* fast = head;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) return true;
    }
    return false;
}

// 3. Find Cycle Start Node
ListNode* detectCycle(ListNode* head) {
    if (!head) return nullptr;
    
    ListNode* slow = head;
    ListNode* fast = head;
    bool hasCycle = false;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            hasCycle = true;
            break;
        }
    }
    
    if (!hasCycle) return nullptr;
    
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

// 4. Find Nth Node from End
ListNode* nthFromEnd(ListNode* head, int n) {
    ListNode* fast = head;
    ListNode* slow = head;
    
    for (int i = 0; i < n; i++) {
        if (!fast) return nullptr;
        fast = fast->next;
    }
    
    while (fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

// 5. Remove Nth Node from End
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    
    ListNode* fast = dummy;
    ListNode* slow = dummy;
    
    for (int i = 0; i <= n; i++) {
        fast = fast->next;
    }
    
    while (fast) {
        slow = slow->next;
        fast = fast->next;
    }
    
    ListNode* temp = slow->next;
    slow->next = slow->next->next;
    delete temp;
    
    return dummy->next;
}

// 6. Check if Palindrome
bool isPalindrome(ListNode* head) {
    if (!head || !head->next) return true;
    
    // Find middle
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // Reverse second half
    ListNode* prev = nullptr;
    ListNode* curr = slow->next;
    while (curr) {
        ListNode* nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }
    
    // Compare
    ListNode* p1 = head;
    ListNode* p2 = prev;
    while (p2) {
        if (p1->val != p2->val) return false;
        p1 = p1->next;
        p2 = p2->next;
    }
    return true;
}

// 7. Intersection of Two Linked Lists
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    if (!headA || !headB) return nullptr;
    
    ListNode* pA = headA;
    ListNode* pB = headB;
    
    while (pA != pB) {
        pA = pA ? pA->next : headB;
        pB = pB ? pB->next : headA;
    }
    return pA;
}

// 8. Reorder List (L0 → Ln → L1 → Ln-1 → ...)
void reorderList(ListNode* head) {
    if (!head || !head->next) return;
    
    // Find middle
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // Reverse second half
    ListNode* prev = nullptr;
    ListNode* curr = slow->next;
    slow->next = nullptr;
    
    while (curr) {
        ListNode* nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }
    
    // Merge
    ListNode* first = head;
    ListNode* second = prev;
    
    while (second) {
        ListNode* temp1 = first->next;
        ListNode* temp2 = second->next;
        
        first->next = second;
        second->next = temp1;
        
        first = temp1;
        second = temp2;
    }
}

void printList(ListNode* head) {
    while (head) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

int main() {
    // Create list: 1 -> 2 -> 3 -> 4 -> 5
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    
    cout << "Original List: ";
    printList(head);
    
    ListNode* middle = findMiddle(head);
    cout << "Middle element: " << middle->val << endl;
    
    ListNode* thirdFromEnd = nthFromEnd(head, 3);
    cout << "3rd from end: " << thirdFromEnd->val << endl;
    
    cout << "Has cycle: " << (hasCycle(head) ? "Yes" : "No") << endl;
    cout << "Is palindrome: " << (isPalindrome(head) ? "Yes" : "No") << endl;
    
    return 0;
}

