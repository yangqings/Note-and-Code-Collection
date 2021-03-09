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
