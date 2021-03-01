class Solution {
public:
    int longestSubstring(string s, int k) {
        if (s.size() < k) return 0;
        unordered_set<char> chars(s.begin(), s.end());
        unordered_map<char, int> counter;
        for (char c : s) 
            counter[c] ++;
        for (char c : chars) {
            vector<string> t; 
            if (counter[c] < k) {
                split(s, t, c);
                int res = 0;
                for (string tn : t) {
                    res = max(res, longestSubstring(tn, k));
                }
                return res;
            }
        }
        return s.size();
    }
    void split(const string& s, vector<string>& sv,const char flag = ' ') {
    sv.clear();
    istringstream iss(s);
    string temp;

    while (getline(iss, temp, flag)) {
        sv.push_back(temp);
    }
}
};


class Solution{
public:
    int dfs(string& s, int l, int r. int k){
        if( r - l + 1 < k)return 0;
        vector<int> cnt(26, 0);

        for(int i = l; i <= r; ++i){  //统计字母出现次数
            cnt[ s[i] - 'a' ] ++;
        }

        char split = 0;
        for(int i = 0; i < 26; ++i){  //找到分割字母
            if(cnt[i] > 0 && cnt[i] < k){
                split = s[i] + 'a';
                break;
            }
        }

        if(split == 0) return r - l + 1; 

        int i = l;
        int ret = 0;
        while( i <= r){
            while(i <= r && s[i] == split){ //找 left
                ++i;
            }
            if(l > r)break;

            int start = i; 
            while(i <= r && s[i] != split){ //找 right
                ++i;
            }

            int length = dfs(s, start, i - 1; k);
            ret = max(ret, length);
        }

        return ret;
    }

    int longestSubstring(string s, int k){
        int n = string.length();
        return dfs(s, 0, n - 1, k);
    }
}   