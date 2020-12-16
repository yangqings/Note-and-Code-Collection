class Solution {
public:
    bool isAnagram(string s, string t) {
        //1.暴力求解：sort->compare
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        if(s.compare(t) == 0)return true;
        else return false;
    }
};

class Solution {
public:
    bool isAnagram(string s, string t) {
        //1.使用数组映射
        if(s.size() != t.size())return false;
        
        int record[26] = {0};
        for(int i = 0; i < s.size(); ++i){
            record[s[i] - 'a']++;
        }
        for(int i = 0; i < t.size(); ++i){
            if((--record[t[i] - 'a']) == -1)return false; //注意这里的巧妙判断
        }
        return true;
    }
};

class Solution {
public:
    bool isAnagram(string s, string t) {
        //1.使用数组映射
        if(s.size() != t.size())return false;
        
        unordered_map<char, int> map;
        for(char c : s)map[c] ++;
        for(char c : t)
            if(-- map[c] == -1)return false;
        return true;
    }
};