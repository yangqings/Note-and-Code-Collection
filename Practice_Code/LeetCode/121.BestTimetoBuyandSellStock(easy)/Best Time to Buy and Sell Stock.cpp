class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int sell = 0, buy = INT_MIN;
        for(int i = 0; i < prices.size(); ++i){
            buy = max(buy, -prices[i]);        //保存最低买入价格
            sell = max(sell, buy + prices[i]); //此刻卖出的最大收益
        }
        return sell;
    }
};