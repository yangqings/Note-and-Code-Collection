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

//栈辅助
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* p = head;
        if(n == 0) return head;
        else if(n == 1){
            if(head->next != nullptr){
                while(p->next != nullptr && p->next->next != nullptr){
                    p = p->next;
                }
                p->next = nullptr;
                return head;
            }
            else{ //单节点删除情况
                delete head;
                return nullptr;
            }
        }

        stack<ListNode*> s;
        int count = 0;

        while(p != nullptr){
            s.emplace(p);
            count++;
            p = p->next;
        }

        int temp = 0;
        while(temp != (n-1)){
            p = s.top();
            s.pop();
            temp++;
        }

        if(s.size() != 1){
            s.pop();
            s.top()->next = p;
        }else{
            head = p;
        }

        return head;
    }
};

//LEeetcode官方题解 栈辅助
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0, head);
        stack<ListNode*> stk;
        ListNode* cur = dummy;
        while (cur) {
            stk.push(cur);
            cur = cur->next;
        }
        for (int i = 0; i < n; ++i) {
            stk.pop();
        }
        ListNode* prev = stk.top();
        prev->next = prev->next->next;
        ListNode* ans = dummy->next;
        delete dummy;
        return ans;
    }
};


//快慢指针，快指针刚好比慢指针快n个节点