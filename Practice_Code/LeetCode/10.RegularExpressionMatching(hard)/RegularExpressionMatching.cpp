/**
 * @brief 动态规划方法
 * 
 */
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector< vector<bool> > dp(m + 1, vector<bool>(n+1, false));
        dp[0][0] = true;

        for(int i = 1; i < n+1; ++i){
            if(p[i-1] == '*'){
                dp[0][i] = dp[0][i-2]; //?
            }
        }

        for(int i = 1; i < m + 1; ++i){
            for(int j = 1; j < n + 1; ++j){
                if(p[j-1] == '.'){
                    dp[i][j] = dp[i-1][j-1];
                }else if(p[j-1] != '*'){
                    dp[i][j] = dp[i-1][j-1] && p[j-1] == s[i-1];
                }else if(p[j-2] != s[i-1] && p[j-2] != '.'){    //如何理解这里？
                    dp[i][j] = dp[i][j-2];
                }else{
                    dp[i][j] = dp[i][j-1] || dp[i-1][j] || dp[i][j-2];
                }
            }
        }

        return dp[m][n];

    }
};

/**
 * @brief 动态规划方法+初始化优化
 * 
 */

class Solution {
public:
    bool isMatch(string s, string p) {
        s=" "+s;//防止该案例：""\n"c*"
        p=" "+p;
        int m=s.size(),n=p.size();
        bool dp[m+1][n+1];
        memset(dp,false,(m+1)*(n+1));
        dp[0][0]=true;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(s[i-1]==p[j-1] || p[j-1]=='.'){
                    dp[i][j]=dp[i-1][j-1];
                }
                else if(p[j-1]=='*'){                      //如何理解这里？
                    if(s[i-1]!=p[j-2] && p[j-2]!='.')
                        dp[i][j]=dp[i][j-2];
                    else{
                        dp[i][j]=dp[i][j-1] || dp[i][j-2] || dp[i-1][j];

                    }
                }
            }
        }
        return dp[m][n];
    }
};
