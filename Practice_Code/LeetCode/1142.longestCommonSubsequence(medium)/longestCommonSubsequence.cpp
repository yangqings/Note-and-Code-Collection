/**
 * @brief 最长公共子序列
 *        子序列不要求连续，要求顺序相同
 *         dp table解法
 */
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m  = text1.length(), n = text2.length();
        if(n * m == 0)return 0;

        //dp[i][j],表示text1[0...i] 和 text2[0...j]的最长公共子序列
        int dp[m+1][n+1];

        for(int i = 0; i <= m; ++i) dp[i][0] = 0;
        for(int i = 0; i <= n; ++i) dp[0][i] = 0;
        
        for(int i = 1; i <= m; ++i){
            for(int j = 1; j <= n; ++j){
                if(text1[i-1] == text2[j-1]){
                    dp[i][j] = dp[i-1][j-1] + 1;
                }
                else{
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }

        return dp[m][n];
    }
};