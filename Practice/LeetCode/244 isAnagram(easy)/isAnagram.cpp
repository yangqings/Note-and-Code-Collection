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