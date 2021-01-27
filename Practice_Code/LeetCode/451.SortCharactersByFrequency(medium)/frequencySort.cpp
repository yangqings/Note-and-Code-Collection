/**
 * 桶排序解按词频排列元素
 * */
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> counts;
        int max_count = 0;
        for(const char& c : s){/*统计词频*/
            max_count = max(max_count, ++counts[c]);
        }


        vector<vector<char>> buckets(max_count+1);
        for(const auto& p : counts){/*按照词频放入桶*/
            buckets[p.second].push_back(p.first);
        }

        string ans;
        for(int i = max_count; i>0; --i){/*从词频高到低，遍历桶*/
            for(const char& c : buckets[i]){/*桶每个元素按照出现次数push进ans*/
                for(int j=i; j>0; --j)/*去掉后，元素只有一个*/
                    ans  += c;
            }
        }
        return ans;
    }
};

