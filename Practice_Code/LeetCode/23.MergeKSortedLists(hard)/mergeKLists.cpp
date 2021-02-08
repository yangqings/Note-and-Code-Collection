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

 /**
  * @brief k个链表合并成有序链表
  *        思路，将k个链表节点用优先队列存放，然后从优先队列逐个取出，构成有序链表

  */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) return nullptr;

        auto cmp = [] (ListNode* l1, ListNode* l2){
            return l1->val > l2->val;
        };

        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> q(cmp);
        for(ListNode* list : lists){
            if(list){
                q.push(list);
            }
        }

        ListNode* dummy = new ListNode(0), *cur = dummy;
        while(!q.empty()){
            cur->next = q.top();
            q.pop();
            cur = cur->next;
            if(cur->next){
                q.push(cur->next);
            }
        }

        return dummy->next;
    }
};