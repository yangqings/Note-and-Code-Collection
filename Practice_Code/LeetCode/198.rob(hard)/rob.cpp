class Solution {
public:
    int rob(vector<int>& nums) {
        //dp数组法，自底向上
        int n = nums.size();
        if(n == 0)return 0;
        int dp[n][2];//n号房屋，0不抢，1抢

        dp[0][1] = nums[0];
        dp[0][0] = 0;
        for(int i=1; i<n; i++){
            dp[i][1] = dp[i-1][0] + nums[i];
            dp[i][0] = max(dp[i-1][0], dp[i-1][1]);//n号屋子不抢，可能上一号屋子抢过，也可能没抢，选max
        }
        return max(dp[n-1][0], dp[n-1][1]);
    }
};

class Solution {
public:
    int rob(vector<int>& nums) {
        //备忘录优化的递归方法，自顶向下
        vector<int> memo(nums.size(),-1);
        return dp(nums,0,memo);
    }
private:

    int dp(vector<int>& nums, int start, vector<int>&memo)
    {
        if(start>=nums.size())return 0;
        if(memo[start] != -1)return memo[start];

        int res = max(dp(nums, start+1, memo), nums[start]+dp(nums,start+2, memo));
        memo[start] = res;
        return res;
    }
};