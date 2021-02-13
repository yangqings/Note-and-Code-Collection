
/**
 * @brief 滑动窗口最大值
 *   思路：优先队列解法
 *        1.滑动窗口移动一位，滑动窗口内的元素实际只变化一位
 *        2.快速得到最值，想到优先队列、单调栈等数据结构
 *        3.窗口内的值进入队列，优先队列的最大值可能是窗口左侧的值，此时将其移除，
 *          直到队首是窗口内的值，则得到滑动窗口的最大值。
 *        优先队列时间复杂度：元素进入优先队列O(logn)，该解法一共n元素进入，总时间复杂度O(nlogn),空间复杂度O(n)
 */
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        priority_queue<pair<int, int>> q;  //<value, key>
        for (int i = 0; i < k; ++i) {      //优先队列初始化
            q.emplace(nums[i], i);         //k个元素进入优先队列q
        }
        vector<int> ans = {q.top().first};
        for (int i = k; i < n; ++i) {
            q.emplace(nums[i], i);            //新值进入队列
            while (q.top().second <= i - k) { //旧值，移出队列
                q.pop();
            }
            ans.push_back(q.top().first);     //优先队列的最大值就是当前窗口最大值
        }
        return ans;
    }
};

/**
 * @brief 双端队列解法（也叫单调队列，单调栈的延伸），妙，顶呱呱！
 *    思路：
 *        1.窗口右移，窗口左值从队列移除；
 *        3.右端新元素，若小于窗口右端值，进入队列；
 *          新元素若大于队列右端值，队列右端值出队列；
 *        4.双端队列最左端保持了窗口的最大元素值
 *        时间复杂度O(n)，空间复杂度O(k)
 */
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;
        vector<int> ans;
        for(int i = 0; i < nums.size(); ++i){       //操作数组的秩，而不是值
            if( !dq.empty() && dq.front() == i - k){//队列左值是窗口左值，左值移出队列，窗口右移
                dq.pop_front();                     //对这一步的理解：因为要更新窗口，所以要判断目前队列左值是不是窗口左值
            }
            while( !dq.empty() && nums[dq.back()] < nums[i] ){//新值大于队列右值，右值移出队列
                dq.pop_back();
            }
            dq.push_back(i);                                  //窗口新值进入队列
            if(i >= k - 1){
                ans.push_back(nums[dq.front()]);              //双端队列左端就是当前窗口最大值
            }
        }
        return ans;
    }
};


/**
 * @brief 分块+预处理解法 这个比较难，没有理解，可看leetcode官方题解
 * 
 */