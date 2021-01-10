class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int days = prices.size();
        if(days < 2)return 0;
        //分两种情况
        //case1: k >= days, 获益即可交易
        if(k >= days){
            int maxProfit = 0;
            for(int i = 1; i < days; ++i){
                if(prices[i] > prices[i - 1]){
                    maxProfit += prices[i] - prices[i - 1];
                }
            }
            return maxProfit;
        }

        //case2: k < days
        //buy,sell分别保存可买入和可出售状态下的最大收益
        //return sell[k]，获益最大，最后必然是没有持有股票
        vector<int> buy(k+1, INT_MIN), sell(k+1, 0);
        for(int i = 0; i < days; ++i){
            for(int j = 1; j <= k; ++j){
                buy[j] = max(buy[j], sell[j-1] - prices[i]); //保持 OR 买入
                sell[j] = max(sell[j], buy[j] + prices[i]);  //保持 OR 卖出
            }
        }

        return sell[k];

    }
};