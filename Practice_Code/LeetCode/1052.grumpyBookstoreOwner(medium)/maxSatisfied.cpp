/**
 * @brief 思路：
 *            1.第一次遍历计算不使用技巧情况下的最大结果
 *            2.滑动窗口，计算窗口内使用技巧带来的结果增量
 *            3.滑动窗口的精髓，每次滑动窗口，窗口前的元素移除，新元素移进来，不需要重复计算窗口内不改变的元素；
 * 
 */
class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int X) {
        //首先计算不适用技巧的顾客结果数量
        int ans = 0;
        int increase = 0, n = customers.size();
        for(int i = 0; i < n; ++i){
            //ans += (customers[i] * !(grumpy[i]));
            if(grumpy[i] == 0)ans += customers[i];
        }

        //使用技巧后挽回的最大顾客数
        for(int i = 0; i < X; ++i){
            increase += customers[i]*grumpy[i];
        }
        /*要注意结果返回的是ans+increase_max
        *所以当元素个数刚好等于窗口大小时，下面的循环不会被执行，这里执行赋值语句很重要
        */
        int increase_max = increase;

        for(int i = X; i < n; ++i){
            /*关键，减去被移除的元素，增加新移进的元素*/
            increase = increase - customers[i-X] * grumpy[i-X] + customers[i] * grumpy[i];
            increase_max = max(increase_max, increase);
        }

        return ans + increase_max;
    }
};
