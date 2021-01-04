/**
 * @brief 找出链表的环路的起始节点
 *        思路：快慢指针，Floyd判圈法
 *        step1：快指针走两步，满慢指针走一步，如果相遇，存在环
 *        step2: 慢指针位置不变，快指针位置移至head，再走一次，相遇的位置就是环路起始节点
 */


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
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head, *fast = head; 

        do{
            if(!fast || !fast->next) return nullptr;
            fast = fast->next->next;
            slow = slow->next;
        }while(fast != slow);

        fast = head;
        while(fast != slow){
            slow = slow->next;
            fast = fast->next;
        }

        return fast;
    }
};