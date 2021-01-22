/**
 * @brief 递归（分治）+ 备忘录 解决戳气球问题；很慢。。。
 *        1.每次戳掉一个气球后会使得原来不相邻的气球相邻，难以处理        
 *        2.逆向思维，从[1][1]base case开始插入气球
 *        3.插入第一个气球后，val[i] * val[mid] * val[right]
 *        4.然后递归地计算solve(i,mid)和solve(mid,j)
 *        5.for循环计算所有的mid = i
 *        6.sum = val[left] * val[i] * val[right] + solve(left, i) + solve(i, right);
 *        7.rec[left][right] = max((val[i] * val[mid] * val[right]), sum);//经过循环后保存最大值作为结果
 */
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        val.resize(n+2);

        for(int i = 1; i <= n; ++i){
            val[i] = nums[i - 1];
        }
        val[0] = val[n+1] = 1;
        rec.resize(n + 2, vector<int>(n + 2, -1));

        return solve(0, n+1);
    }

private:
    vector<vector<int>> rec;
    vector<int> val;

    int solve(int left, int right){
        if(rec[left][right] != -1){ //备忘优化
            return rec[left][right];
        }
        if(left >= right - 1){
            return 0;
        }
        for(int i = left + 1; i < right; ++i){
            int sum = val[left] * val[i] * val[right];
            sum += solve(left, i) + solve(i, right);
            rec[left][right] = max(rec[left][right], sum);
        }
        return rec[left][right];
    }
};

/**
 * @brief 动态规划法
 *        dp[i][j]表示戳破i，j之间的气球获得的最高分数（不包括i，j），则结果就是dp[0][n+1]
 *        base case: dp[i][j] = 0，其中0 <= i <= n+1, j <= i+1, 此情况下无气球可戳破
 *        正向思考：回溯算法
 *        反向思考：最后被戳破的气球是哪个？
 */

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        int rec[n+2][n+2];
        int val[n+2];
        val[0] = val[n+1] = 1; //增加左右边界两个元素，方便处理
        for(int i = 1; i <= n; ++i){
            val[i] = nums[i-1];
        }

        for(int i = 0; i<n+2; ++i){
            for(int j = 0;j<n+2; ++j){
                rec[i][j] = 0; //初始化
            }
        }

        /**
         * 思考1：dp表定义
         * 回答：dp[i][j]表示，戳破开区间(i,j)之间的气球得到的最大分数值，注意是开区间
         *
         * 思考2：for循环遍历如何写？
         * 回答：选择戳破(i,j)中的nums[k]
         *      dp[i][k]和dp[k][j]恰巧也是dp表的定义，即戳破这两个区间的气球，最后剩下nums[i]nums[k]nums[j]
         *      rec[i][j] = dp[i][k] + dp[k][j] + nums[i] * nums[k] * nums[j]
         *      状态转移依赖的状态必须被提前计算
         *      技巧：在计算dp[i][j]时候，必须先得到dp[i][k]和dp[k][j]，可以从base case和最终状态推导
         *           比如，计算dp[n][n+1]时，先计算dp[n][n]和dp[n+1][n+1],刚好这两个都是base case， = 0
         *                计算dp[n-1][n]时，先计算dp[n-1][n-1]和dp[n][n];
         *                得到dp[n][n+1]和dp[n-1][n]就可以计算dp[n-1][n+1]了，以此类推
         * */
        for(int i=n-1; i >= 0; i--){//为什么倒着遍历? 下往上
            for(int j = i+2; j <= n+1; j++){ //左往右
                for(int k = i+1; k < j; k++){//穷举所有的k
                    int sum = val[i] * val[k] * val[j];
                    sum += rec[i][k] + rec[k][j];
                    rec[i][j] = max(rec[i][j], sum);//do best choice
                }
            }
        }

        return rec[0][n+1];
    }
};
