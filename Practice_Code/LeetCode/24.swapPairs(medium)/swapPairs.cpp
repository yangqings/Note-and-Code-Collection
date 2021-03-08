/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(head == nullptr || head->next == nullptr)return head;
        
        ListNode* ansNode = head->next, *firstNode = head, *tempHead = head, *nextNode = head->next;

        while(nextNode != nullptr && firstNode != nullptr){
            tempHead->next = nextNode;
            tempHead = swapNode(firstNode, nextNode);
            firstNode = tempHead->next;
            if(firstNode != nullptr)
                nextNode = firstNode->next;
        }
        return ansNode;
    }

    //返回交换后的头节点
    ListNode* swapNode(ListNode* first, ListNode* second){
        first->next = second->next;
        second->next = first;
        return first;
    }
};