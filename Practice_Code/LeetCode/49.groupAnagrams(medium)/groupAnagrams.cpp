class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;
        for (string s : strs){
            string t  = s;
            sort(t.begin(), t.end());
            mp[t].emplace_back(s);/*排序后的字符串作为键Key，原字符作为值value*/
        }
        vector< vector<string> > anagrams;
        for(auto p : mp){
            anagrams.emplace_back(p.second);/*p.second取值value， p.first取键值Key*/
        }
        return anagrams;
    }
private:
    string strSort(string str){
        int count[26]={0};
        for(char c : str){
            count[c - 'a'] ++;
        }
        string res;
        for(int c = 0; c < 26; c++){
            res += string(count[c], c + 'a');
        }
        return res;
    }
};

