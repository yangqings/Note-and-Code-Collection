/**
 * @brief KMP算法求解字符串匹配问题
 * 
 */
class Solution {
public:
    int strStr(string haystack, string needle) {
        int m = haystack.length(), n = needle.length(), k = -1;
        if(n == 0)return 0;
        vector<int> next(n, -1);

        calNext(needle, next);
        for(int i = 0; i < m; ++i){
            // case 1:部分匹配，回溯
            // case 2:无匹配
            // case 3:匹配成功
            while(k > -1 && needle[k+1] != haystack[i]){
                k = next[k];
            }
            if(needle[k+1] == haystack[i]){
                ++k;
            }
            if(k == n-1){
                return i - n + 1;
            }
        }
        return -1;
    }

    //计算next数组
    //next表计算只依赖模式串，与文本串无关
    //我对next表的理解：
    //1.根据当前未适配的字符串，尝试找到模式串(已适配范围)的最长适配前缀字符串
    //2.因为在文本串与模式串适配过程，已经适配的前缀字符串必然是模式串的前缀，
    //3.相当于在下一字符串适配时候，前面适配过的信息已知（与文本串无关）。
    //4.next数组只需要保存失配位置j对应的模式串应该偏移的量
    void calNext(const string& needle, vector<int>& next)
    {
        for(int j = 1, p = -1; j < needle.length(); ++j){
            while(p > -1 && needle[p+1] != needle[j]){  //注意理解为什么会有 p > -1
                p = next[p];
            }
            if(needle[p+1] == needle[j]){
                ++p;
            }
            next[j] = p;
        }
    }
};