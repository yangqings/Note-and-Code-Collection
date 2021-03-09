class Solution{
public:
    int lengthOfLongestSubstring(string s){
        int n = s.length(), ans = 0, left = 0, right = -1;
        unordered_set<char> hash;

        for(; left < n; ++left){
            if(left != 0){
                hash.erase(s[left - 1]);
            }

            while(right + 1 < n && !hash.count(s[right + 1])){
                hash.insert(s[right + 1]);
                ++right;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};


//使用hashMap优化，key: char , value : index
//找到重复字符，且index在start后，这样就可以保证重复字符不是之前已经处理过的字符
class Solution{
public:
    int lengthOfLongestSubstring(string s){
        int n = s.length(), ans = 0, len = 0, start = 0, end = 0;
        unordered_map<char,int> hash; //<char, index>

        while(end < n){
            char c = s[end];
            if(hash.find(c) != hash.end() && hash[c] >= start){//找到重复字符且index在start后,
                start = hash[c] + 1;//将start移到重复字符的下一个位置
                len = end - start;
            }
            hash[c] = end;

            end ++;
            len ++;
            ans = max(ans, len); 
        }
        return ans;
    }
};

//数组（桶）优化
class Solution{
public:
    int lengthOfLongestSubstring(string s){
        int n = s.length(), ans = 0, len = 0, start = 0, end = 0;
        unordered_map<char,int> hash; //<char, index>
        vector<int> bucket(128, -1);

        while(end < n){
            char c = s[end];
            if(bucket[int(c)] >= start){
                start = bucket[int(c)] + 1;
                len = end - start;
            }
            bucket[int(c)] = end;
            end ++;
            len ++;
            ans = max(ans, len);
        }
        return ans;
    }
};