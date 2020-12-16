/**
 * @brief 动态规划
 * 找出状态转换方程
 */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.empyt())return 0;
       
        int n = prices.size();
        int dp[n][2];
        //dp[i][0/1]：表示第i天，0没持有股票，1持有股票，dp保存最大收益
        dp[0][0] = 0;
        dp[0][1] = -prices[0];

        for(int i = 1; i < n; i++){
            //第i天，手中没持有股票的两种情况：1.前一天也没持有，并且没买入；2.前一天持有，但是卖出，获益prices
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
            //第i天，手中持有股票的两种情况：1.前一天也持有，并且没卖出；2.前一天没持有，但是买入；
            dp[i][1] = max(dp[i-1][1], dp[i-1][0]-prices[i]);
        }
       return dp[n - 1][0]; 
    }
};

/**
 * @brief 贪心算法 
 * 
 */

class Solution{
public:
    int maxProfit(vector<int>& prices){
        //贪心算法，逢低价便买入
        //前一天价格小于后一天价格便在前一天买入后一天卖出
        int maxProfit = 0;
        int n = prices.size();
        for(int i = 1; i < n; i++){
            maxProfit += max(prices[i] - prices[i-1], 0);
        }
        return  maxProfit;
    }
};