/**
 * @brief 最长递增子序列
 *        动态规划解法  O(N^2)
 *        dp[i]表示以nums[i]数字结尾的最长子递增序列长度
 *        结果为dp[i]中的最大值
 */

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int len = nums.size();
        if(len == 0)return 0;

        int dp[len];//dp[i]保存以nums[i]数字结尾的最长子递增序列长度
        int max_inc_length = 1, max_num = nums[0];

        for(int i = 0; i < len; i++)dp[i]=1;

        for(int i = 0; i < len; i++){
            for(int j = 0; j < i; j++){
                if(nums[j] < nums[i]){ //找到之前序列中比nums[i]小的数nums[j]
                    dp[i] = max(dp[i], dp[j]+1);//以nums[j]为倒数第二个数，最后拼接nums[i]，
                                                //最小子序列长度+1, 比较所有结果，得到dp[i]最长子序列
                }
            }  
            if(dp[i] > max_inc_length)max_inc_length = dp[i];
        }
        return max_inc_length;
    }
};


/**
 * @brief 二分查找解法 O(NlogN)
 *        以扑克牌为例理解：
 *        1.按顺序取出扑克，只能把点数小的扑克放在比它大的牌上
 *        2.如果当前扑克点数大，没有可放置的堆，则新建一个堆
 *        3.最后，堆的数量就是最长递增子序列长度
 */
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int len = nums.size();
        if(len == 0)return 0;

        int cell[len]; //保存最长上升子序列,扑克堆，cell[i]表示第i堆顶部的扑克，也就是该堆值最小的扑克
        int piles = 0; //堆数

        for(int i = 0; i < nums.size(); i ++){
            int poker = nums[i];

            /*二分查找，找到合适的堆位置*/
            int left = 0, right = piles;
            while(left < right){
                int mid = (left + right) / 2;
                if(cell[mid] > poker){
                    right = mid;
                }else if(cell[mid] < poker){
                    left = mid + 1;
                }else{
                    right = mid;
                }
            }
            
            /*找不到合适的堆，新建*/
            /*注意理解为什么是left == piles*/
            /*扑克找不到合适位置插入，必然意味着它比所有堆顶扑克值要大，二分查找，left边界更新到右边界*/
            if(left == piles) piles++;  //新建堆
            cell[left] = poker;         //堆顶放置扑克
        }

        return piles;//返回堆数
    }
};