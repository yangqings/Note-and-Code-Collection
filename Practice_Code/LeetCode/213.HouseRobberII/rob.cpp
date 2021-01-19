/**
 * @brief 打家劫舍，环形数组
 *        解题思路：
 *        1.分两种情况，第一间屋子抢，则最后一间屋子不能抢
 *        2.第一间屋子不抢，最后一间屋子可抢
 *        3.然后按照正常的rob动态规划思路处理
 *        4.最后返回两者的最大结果
 */
class Solution {
public:
    int rob(vector<int>& nums) {
        int size = nums.size();
        if(size == 0)return 0;
        else if(size == 1)return nums[0];

        int pre = 0, cur1 = 0, cur2 = 0, tmp;
        for(int i = 1; i < size; ++i){
            tmp = cur1;
            cur1 = max(pre + nums[i], cur1);
            pre = tmp;
        }
        pre = 0;
        for(int i = 0; i < size-1; ++i){
            tmp = cur2;
            cur2 = max(pre + nums[i], cur2);
            pre = tmp;
        }
        return max(cur1, cur2);
    }

};