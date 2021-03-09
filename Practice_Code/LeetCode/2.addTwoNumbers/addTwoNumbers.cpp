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

 //简单思路：遍历链表
 //注意链表的长度，实现加法只能逐位加，并进位
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* res = nullptr;
        ListNode* res_head = nullptr;
        ListNode* node_l1 = l1;
        ListNode* node_l2 = l2;
        stack<int> s;

        int temp, carry = 0;
        res_head = new ListNode(-1);
        res = res_head;
        while(node_l1 != nullptr && node_l2 != nullptr){
            temp = node_l1->val + node_l2->val + carry;
            carry = temp / 10;
            res->next = new ListNode(temp % 10);
            node_l1 = node_l1->next;
            node_l2 = node_l2->next;
            res = res->next;
            temp = 0;
        }

        while(node_l1 != nullptr){
            temp = node_l1->val + carry;
            carry = temp / 10;
            res->next = new ListNode(temp % 10);
            node_l1 = node_l1->next;
            res = res->next;
            temp = 0;
        }
        while(node_l2 != nullptr){
            temp = node_l2->val + carry;
            carry = temp / 10;
            res->next = new ListNode(temp % 10);
            node_l2 = node_l2->next;
            res = res->next;
            temp = 0;
        }

        if(carry != 0){
            res->next = new ListNode(carry);
        }

        return res_head->next;
    }
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *head = nullptr, *tail = nullptr;
        int carry = 0;
        head = new ListNode(-1);
        tail = head;
        while (l1 || l2) {
            int n1 = l1 ? l1->val: 0;
            int n2 = l2 ? l2->val: 0;
            int sum = n1 + n2 + carry;

            tail->next = new ListNode(sum % 10);
            tail = tail->next;

            carry = sum / 10;
            if (l1) {
                l1 = l1->next;
            }
            if (l2) {
                l2 = l2->next;
            }
        }
        if (carry > 0) {
            tail->next = new ListNode(carry);
        }
        return head->next;
    }
};
