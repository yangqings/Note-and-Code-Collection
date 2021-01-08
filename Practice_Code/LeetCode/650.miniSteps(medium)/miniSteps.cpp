/**
 * @brief 动态规划方法
 *       dp[i]定义：i个字符时最小操作数
 */
class Solution {
public:
    int minSteps(int n) {

        vector<int> dp(n+1, 0);
        int h = sqrt(n);

        for(int i = 2; i <= n; ++i){
            dp[i] = i;
            for(int j = 2; j <= h; ++j){
                if(i % j == 0){
                    dp[i] = dp[j] + dp[i/j]; //关键理解这里，分解，比如6 = 2*3；dp[6] = min(dp[3]+2, dp[2]+3)，
                                             //实际上不用判断min, dp[j]+dp[i/j]，j最小即满足
                    break;
                }
            }
        }

        return dp[n];
    }
};

/**
 * @brief 素数分解方法，leetcode官方，最优解法
 *        当n为素数时，只能复制一次，粘贴多次
 *        当n为合数时，分解，比如6 = 2*3；dp[6] = min(dp[3]+2, dp[2]+3)
 */

class Solution {
    public int minSteps(int n) {
        int ans = 0, d = 2;
        while (n > 1) {
            while (n % d == 0) {
                ans += d;
                n /= d;
            }
            d++;
        }
        return ans;
    }
}