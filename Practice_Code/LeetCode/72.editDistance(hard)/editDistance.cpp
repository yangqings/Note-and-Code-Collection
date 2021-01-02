// Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

// You have the following three operations permitted on a word:

// Insert a character
// Delete a character
// Replace a character

//属于动态规划的子序列问题
// 代码基本结构
// if s1[i] == s2[j]:
//     nothing to do
//     i, j move

// else
//     choice:
//         insert;
//         delete;
//         replace;


/**       dp表解法
 * @brief dp表定义：dp[i][j] 返回s1[0...i] s2[0...j]最小编辑距离
 *        边界情况  dp[0][...]和dp[...][0]
 */       
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();
        
        if(n*m == 0)return n + m;

        int dp[n+1][m+1];

        for(int i = 0; i < n + 1; i++){
            dp[i][0] = i;
        }

        for(int j = 0; j < m + 1; j++){
            dp[0][j] = j;
        }

        for(int i = 1; i < n + 1; i++){
            for(int j = 1; j < m + 1; j++){
                if(word1[i-1] == word2[j-1]){//注意理解[i-1][j-1]表示当前的字符，因为比较字符是从[1][1]开始的，而数组是从[0][0]开始的
                    dp[i][j] = dp[i-1][j-1];
                }else{
                    dp[i][j] = min(dp[i-1][j] + 1, min(dp[i][j-1] + 1, dp[i-1][j-1]+1));
                }
            }
        }
        return dp[n][m];
    }
};

/**       递归+备忘录解法
 * @brief dp表定义：dp[i][j] 返回s1[0...i] s2[0...j]最小编辑距离
 *        边界情况  dp[0][...]和dp[...][0]
 */       
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();
        vector<vector<int>> mem(n+1, vector<int>(m+1, -1));

        return min_dist(word1, n, word2, m, mem);
    }

private:
    int min_dist(const string& word1, int i, const string& word2, int j, vector<vector<int>>& dp){
        if(dp[i][j] > 0)return dp[i][j];
        if(i == 0 || j == 0){
            dp[i][j] = i + j;
        }else{
            if(word1[i-1] == word2[j-1]) dp[i][j] = min_dist(word1, i-1, word2, j-1, dp);
            else{
                dp[i][j] = 1 + min( min( min_dist(word1, i-1, word2, j, dp), min_dist(word1, i, word2, j-1, dp) )
                                    ,min_dist(word1, i-1, word2, j-1, dp));
            }
        }
        return dp[i][j];
    }
};