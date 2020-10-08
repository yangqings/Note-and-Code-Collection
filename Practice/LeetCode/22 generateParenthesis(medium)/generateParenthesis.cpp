class Solution {
public:
    vector<string> res;

    vector<string> generateParenthesis(int n) {
        /*回溯法*/
        string str;/*保存一个有效组合*/
        backtrack(0,0,n,str);
        return res;
    }
private:
    void backtrack(int left,int right ,int& len, string& str)
    {
        /*递归结束*/
        if (str.length() == 2 * len) {
                res.push_back(str);
                //cout <<left <<" "<<right << " " <<str << " "<<endl;
            return;
        }
        if (left < len) {
            str += '('; 
            backtrack(left+1, right, len, str);
            str.pop_back();
        }
        if (right < left) {
            str += ')';
            backtrack(left, right+1, len, str);
            str.pop_back();
        }
    }

};