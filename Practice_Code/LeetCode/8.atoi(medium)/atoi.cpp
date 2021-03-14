class Solution {
public:
    int myAtoi(string s) {
        int i = 0, len = s.length(); 
        int ans = 0;
        bool isNegative = false;

        while(i < len){ // 处理前导字符
            if(s[i] == ' '){ //忽略前导空格
                i++;
                continue;
            }else if(s[i] == '-'){ //只能有一个正负符号
                isNegative = true;
                i++;
                break;
            }else if(s[i] == '+'){ //只能有一个正负符号
                isNegative = false;
                i++;
                break;
            }else if('0' <= s[i] && s[i] <= '9'){ //遇到数字，前导字符处理完
                break;
            }else{ //遇到其他字符，返回0
                return 0;
            }
        }


        while(i < len){
            if( '0' <= s[i] && s[i] <= '9'){
                long int temp = (long int)ans * 10 + (s[i] - '0');//用long int暂存结果
                  if(isNegative && (- temp + 1) <= -(INT_MAX)){   //超出或等于最大负数
                      return -(INT_MAX) - 1;
                  }else if( !isNegative && temp >= INT_MAX){      //超出或等于最大正数
                      return INT_MAX;
                  }else{
                      ans = ans * 10 + (s[i] - '0');
                  }
            }else{  //非数字字符
                break;
            }
            i++;
        }
        return isNegative ? (-1 * ans) : ans;
    }
};