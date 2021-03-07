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

 //暴力算法，建立表格保存链表
class Solution {
public:
    void reorderList(ListNode* head) {
        if(head == nullptr)return;
        ListNode* tempNode = head;
        vector<ListNode *> vec;
        
        while(tempNode != nullptr){
            vec.emplace_back(tempNode);
            tempNode = tempNode->next;
        }

        int i = 0, j = vec.size() - 1;
        while(i < j){
            vec[i]->next = vec[j];
            i++;
            if(i == j){
                break;
            }
            vec[j]->next = vec[i];
            j--;
        }
        vec[i]->next = nullptr;
    }
};