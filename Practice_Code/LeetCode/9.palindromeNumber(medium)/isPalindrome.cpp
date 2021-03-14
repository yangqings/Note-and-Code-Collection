//简单暴力解法
class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0)return false;
        else if(x != 0 && x % 10 == 0)return false;
        else if( x < 9 )return true;
        vector<int> v;
        while(x != 0){
            v.emplace_back(x%10);
            x = x/10;
            //cout<<x<<" ";
        }

        int start = 0, end = v.size() - 1;
        while(start < end){
            if(v[start] == v[end]){
                start ++;
                end --;
            }else{
                return false;
            }
        }
        return true;
    }
};


//将一般数字反转，如果这一半数字等于前一半数字，则是回文字符
class Solution {
public:
    bool isPalindrome(int x) {
        if((x < 0) || (x % 10 == 0 && x != 0  ))return false;
        else if( x == 0 )return true;

        int revertX = 0;
        while(x > revertX){  //当x < 已经反转的数字，说明已经处理一半数字
            revertX = revertX * 10 + (x % 10);
            x = x/10;
        }
        //      长度为偶数       长度为奇数
        return (x == revertX)||(x == revertX / 10);
    }
};
