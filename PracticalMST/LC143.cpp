/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head) return;
        vector<ListNode*> n;
        ListNode* temp = head;

        while(temp) {
            n.push_back(temp);
            temp = temp->next;
        }

        int i = 0;
        int j = n.size() - 1;

        while(i<j) {
            n[i]->next = n[j];
            i++;

            if(i==j) break;

            n[j]->next = n[i];
            j--;
        }
        n[i]->next = nullptr;
    }
};