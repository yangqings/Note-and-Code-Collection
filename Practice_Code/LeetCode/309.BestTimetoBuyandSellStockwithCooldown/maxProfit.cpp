/**
 * 股票卖出后需要保持一天冷冻期
 * 用状态机的方式来描述整个过程：
 * 买入buy、保持持有buy_hold、卖出sell、不持有sell_hold
 * */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
       int size = prices.size();
       if(size == 0)return 0;

       vector<int> buy(size),sell(size),sell_hold(size), buy_hold(size);
       buy[0] = buy_hold[0] = -prices[0];
       sell[0] = sell_hold[0] = 0;

       for(int i=1; i<size; ++i){
           buy[i] = sell_hold[i-1] - prices[i];       //卖出并保持一天后的状态转换而来
           buy_hold[i] = max(buy_hold[i-1], buy[i-1]);//卖出并保持，或者是刚卖出的状态转换而来
           sell[i] = max(buy[i-1] + prices[i], buy_hold[i-1] + prices[i]);//刚买入、或者买入并保持的状态转换过来
           sell_hold[i] = max(sell_hold[i-1], sell[i-1]);                 //不持有状态，或者刚卖出的状态转换而来
       }

        return max(sell[size-1],sell_hold[size-1]);
    }
};