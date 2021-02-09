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
 * @brief 解法一：直接思路，循环顺序合并两个链表，直到处理完所有
 *               时间复杂度：O(n)
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode *a, ListNode *b) {
        if ((!a) || (!b)) return a ? a : b;
        ListNode head, *tail = &head, *aPtr = a, *bPtr = b;
        while (aPtr && bPtr) {
            if (aPtr->val < bPtr->val) {
                tail->next = aPtr; aPtr = aPtr->next;
            } else {
                tail->next = bPtr; bPtr = bPtr->next;
            }
            tail = tail->next;
        }
        tail->next = (aPtr ? aPtr : bPtr);
        return head.next;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* ans = nullptr;
        for(auto list : lists){
            ans = mergeTwoLists(ans,list);
        }
        return ans;
    }
};


/**
 * @brief 解法二：并归优化
 *               渐进时间复杂度为 O(Kn*logK)
 *               由于使用递归，空间复杂度O(logk)
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode *a, ListNode *b) {
        if ((!a) || (!b)) return a ? a : b;
        ListNode head, *tail = &head, *aPtr = a, *bPtr = b;
        while (aPtr && bPtr) {
            if (aPtr->val < bPtr->val) {
                tail->next = aPtr; aPtr = aPtr->next;
            } else {
                tail->next = bPtr; bPtr = bPtr->next;
            }
            tail = tail->next;
        }
        tail->next = (aPtr ? aPtr : bPtr);
        return head.next;
    }

    ListNode* merge(vector<ListNode*> lists, int l, int r){
        if(l == r) return lists[l];
        if(l > r) return nullptr;
        int mid = (l + r) >> 1;
        return mergeTwoLists(merge(lists, l, mid), merge(lists, mid + 1, r));
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return merge(lists, 0, lists.size() - 1);
    }
};


 /**
  * @brief k个有序链表合并成一个有序链表
  *        思路，将k个链表节点用优先队列存放，然后从优先队列逐个取出，构成有序链表
  *        优先队列，获得最大（最小）元素时间复杂度O(1),插入或者删除元素O(logn)
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