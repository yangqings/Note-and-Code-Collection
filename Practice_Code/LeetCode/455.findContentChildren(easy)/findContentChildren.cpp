//分发饼干
//贪心算法：先对胃口值和饼干量进行排序，优先满足胃口值最小的小孩；
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int child_num = g.size(), cookie_num = s.size(); 
        int child = 0, cookies = 0;
        
        while(child < child_num &&  cookies < cookie_num){
            if(g[child] <= s[cookies])++child;
            ++cookies;
        }
        return child;
    }
};