#include <iostream>
using namespace std;

    struct Node {
        int data;
        Node* next;
    };

    // Insert at the end

    void insertAtEnd(Node** head, int val) {
        Node* newNode = new Node();
        newNode -> data = val;
        newNode -> next = nullptr;

        if(*head == nullptr) {
            *head = newNode;
            return;
        }

        Node* temp = *head;
        while(temp -> next != nullptr) {
            temp = temp -> next;
        }
        temp -> next = newNode;
    }

    // Insert at the begining

    void insertAtStart(Node** head, int val) {
        Node* newNode = new Node();
        newNode -> data = val;
        newNode -> next = *head;
        *head = newNode;
    } 

    // Delete by value 

    void deleteNode(Node** head, int val) {
        if (*head == nullptr)
        return;

        // Delete head
        if((*head) -> data ==val) {
            Node* temp = *head;
            *head = (*head)->next;
            delete temp;
            return;
        }

        // Delete others
        Node* curr = *head;
        while(curr->next != nullptr && curr -> next -> data != val) {
            curr = curr->next;
        }

        if (curr->next != nullptr) {
            Node* temp = curr -> next;
            curr -> next = temp-> next;
            delete temp;
        }

    }

    // Display Function

    void disaply(Node* head) {
        while ( head != nullptr) {
            cout<< head -> data << " ";
            head = head -> next;
        }
        cout << "NULL" << endl;
    }

    // Main Function 

    int main() {
        Node* head = nullptr;
        insertAtEnd(&head, 10);
        insertAtEnd(&head, 20);
        insertAtEnd(&head, 30);
        insertAtStart(&head, 40);
        deleteNode(&head, 20);
        disaply(head);


    
    return 0;
}



// Leet Code - 142, 206