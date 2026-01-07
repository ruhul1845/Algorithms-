/*
 * Linked List - Basic Operations
 * Fundamental operations on singly and doubly linked lists
 */

#include <bits/stdc++.h>
using namespace std;

// Node structure for singly linked list
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 1. Insert at Beginning
ListNode* insertAtBegin(ListNode* head, int val) {
    ListNode* newNode = new ListNode(val);
    newNode->next = head;
    return newNode;
}

// 2. Insert at End
ListNode* insertAtEnd(ListNode* head, int val) {
    ListNode* newNode = new ListNode(val);
    if (!head) return newNode;
    
    ListNode* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

// 3. Delete Node by Value
ListNode* deleteNode(ListNode* head, int val) {
    if (!head) return nullptr;
    
    if (head->val == val) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
        return head;
    }
    
    ListNode* curr = head;
    while (curr->next && curr->next->val != val) {
        curr = curr->next;
    }
    
    if (curr->next) {
        ListNode* temp = curr->next;
        curr->next = curr->next->next;
        delete temp;
    }
    return head;
}

// 4. Search Element
bool search(ListNode* head, int val) {
    ListNode* curr = head;
    while (curr) {
        if (curr->val == val) return true;
        curr = curr->next;
    }
    return false;
}

// 5. Reverse Linked List
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    
    while (curr) {
        ListNode* nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }
    return prev;
}

// 6. Find Length
int getLength(ListNode* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

// 7. Get Nth Node
ListNode* getNth(ListNode* head, int n) {
    int count = 0;
    while (head) {
        if (count == n) return head;
        count++;
        head = head->next;
    }
    return nullptr;
}

// 8. Print List
void printList(ListNode* head) {
    while (head) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

// Doubly Linked List Node
struct DListNode {
    int val;
    DListNode* prev;
    DListNode* next;
    DListNode(int x) : val(x), prev(nullptr), next(nullptr) {}
};

// 9. Insert at Beginning (Doubly)
DListNode* insertAtBeginDLL(DListNode* head, int val) {
    DListNode* newNode = new DListNode(val);
    if (head) {
        newNode->next = head;
        head->prev = newNode;
    }
    return newNode;
}

// 10. Delete Node (Doubly)
DListNode* deleteNodeDLL(DListNode* head, int val) {
    if (!head) return nullptr;
    
    DListNode* curr = head;
    while (curr && curr->val != val) {
        curr = curr->next;
    }
    
    if (!curr) return head;
    
    if (curr == head) {
        head = head->next;
        if (head) head->prev = nullptr;
    } else {
        if (curr->prev) curr->prev->next = curr->next;
        if (curr->next) curr->next->prev = curr->prev;
    }
    
    delete curr;
    return head;
}

int main() {
    // Test Singly Linked List
    ListNode* head = nullptr;
    head = insertAtEnd(head, 1);
    head = insertAtEnd(head, 2);
    head = insertAtEnd(head, 3);
    head = insertAtEnd(head, 4);
    
    cout << "Original List: ";
    printList(head);
    
    cout << "Length: " << getLength(head) << endl;
    
    head = reverseList(head);
    cout << "Reversed List: ";
    printList(head);
    
    head = deleteNode(head, 3);
    cout << "After deleting 3: ";
    printList(head);
    
    return 0;
}










