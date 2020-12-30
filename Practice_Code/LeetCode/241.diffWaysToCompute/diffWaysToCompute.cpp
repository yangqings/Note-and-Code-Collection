/**
 * @file diffWaysToCompute.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/*方法1：分治递归
*       以操作符为界，分割，递归计算
*       递归基，只剩下一个数字
*/
class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        vector<int> ways;
        for(int i=0; i < input.length(); i ++){
            char c = input[i];
            if(c == '+' || c == '-' || c == '*'){
                vector<int> left = diffWaysToCompute(input.substr(0, i));
                vector<int> right = diffWaysToCompute(input.substr(i+1));
                for(const int & l : left){
                    for(const int & r : right){
                        switch(c){
                            case '+':ways.push_back(l + r); break;
                            case '-':ways.push_back(l - r); break;
                            case '*':ways.push_back(l * r); break;
                        }
                    }
                }
            }
        }
        if(ways.empty())ways.push_back(stoi(input));//string to num
        return ways;
    }
};


/*方法2：分治递归 + 备忘录优化
*       以操作符为界，分割，递归计算
*       递归基，只剩下一个数字
*/
class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        vector<int> ways;
        for(int i=0; i < input.length(); i ++){
            char c = input[i];
            if(c == '+' || c == '-' || c == '*'){  //找到操作符，分割
                string s1 = input.substr(0, i);    
                string s2 = input.substr(i+1);
                vector<int> left, right;

                if(!hash.count(s1))
                    left = diffWaysToCompute(s1);  //左边递归
                else left = hash[s1];

                if(!hash.count(s2))
                    right = diffWaysToCompute(s2); //右边递归
                else right = hash[s2];

                for(const int & l : left){
                    for(const int & r : right){
                        switch(c){
                            case '+':ways.push_back(l + r); break;
                            case '-':ways.push_back(l - r); break;
                            case '*':ways.push_back(l * r); break;
                        }
                    }
                }
            }
        }
        if(ways.empty())ways.push_back(stoi(input));//string to num
        hash[input] = ways;                         //save result, memoization
        return ways;
    }
private:
    unordered_map<string, vector<int>> hash;
};

/*方法2：分治递归 + 备忘录优化 另一种写法，似乎没有上一种写的好
*       以操作符为界，分割，递归计算
*       递归基，只剩下一个数字
*/
class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        int index = 0;
        int num = 0;

        while(index < input.size() && isdigit(input[index])) //把字符转换成数字
            num = num * 10 + input[index++] - '0';
        if(index == input.size()){  //递归基，只有一个数字
            hash[input] = {num};
            return {num};
        }

        vector<int> ans;
        for(int i = 0; i < input.size(); i++){
            if(isOp(input[i])){
                string s1 = input.substr(0,i);
                string s2 = input.substr(i);
                vector<int> result1, result2;
                if(!hash.count(s1))
                    result1 = diffWaysToCompute(input.substr(0,i));
                else
                    result1 = hash[s1];
                if(!hash.count(s2))
                    result2 = diffWaysToCompute(input.substr(i+1));
                else
                    result2 = hash[s2];
                for(int r1 : result1){
                    for(int r2 : result2){
                        ans.push_back(calculate(r1,input[i],r2));
                    }
                }
            }
        }
        hash[input] = ans;
        return ans;
    }

    bool isOp(const char& c){
        return c == '+' || c == '-' || c == '*';
    }

    int calculate(const int& num1, const char& op, const int& num2){
        if(op == '+')
            return num1 + num2;
        else if(op == '-')
            return num1 - num2;
        else
            return num1 * num2;
    }
private:
    unordered_map<string,vector<int>> hash;
};


/*方法3：动态规划
*       预处理：将数字和操作符分开保存
*       dp表定义：
*                例子，2 * 3 - 4 * 5 
*                dp[1][3] 就代表第一个数字 3 到第三个数字 5 范围内的表达式 3 - 4 * 5 的所有解。
*       状态转换：
*/

class Solution{
public:
    vector<int> diffWaysToCompute(string input){
        vector<int> data;
        vector<int> ops;
        int num = 0;
        char op = ' ';
        istringstream ss(input + "+");
        while (ss >> num && ss >> op){
            data.push_back(num);
            ops.push_back(op); 
        }
        int n = data.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>()));

        for (int i = 0; i < n; ++i){
            for(int j = i; j >= 0; --j){
                if(i == j ){
                    dp[j][i].push_back(data[i]);
                } else {
                    for(int k = j; k < i; k += 1){
                        for(auto left : dp[j][k])
                    }
                }
            }
        }
        
    }
}

