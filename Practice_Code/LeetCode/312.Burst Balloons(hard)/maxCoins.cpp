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
 *        dp[i][j]表示填满开区间能得到的最多硬币数
 */

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        int rec[n+2][n+2];
        int val[n+2];
        val[0] = val[n+1] = 1;
        for(int i = 1; i <= n; ++i){
            val[i] = nums[i-1];
        }

        for(int i = 0; i<n+2; ++i){
            for(int j = 0;j<n+2; ++j){
                rec[i][j] = 0;
            }
        }

        for(int i=n-1; i >= 0; i--){
            for(int j = i+2; j <= n+1; j++){
                for(int k = i+1; k < j; k++){
                    int sum = val[i] * val[k] * val[j];
                    sum += rec[i][k] + rec[k][j];
                    rec[i][j] = max(rec[i][j], sum);
                }
            }
        }

        return rec[0][n+1];
    }
};
