/**
 * @brief 桶排序解决前 K 个高频元素问题
 * 解题思路：
 * 1.为每个值设立一个桶，桶内记录这个值出现的次数
 * 2.对桶进行排序，得到每个数字出现次数的排序
 * 3.根据k值找到第k个高频元素
 */
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> counts;
        int max_count = 0;
        for(const int & num : nums){
            max_count = max(max_count, ++counts[num]);
        }

        vector< vector<int> > buckets(max_count + 1);
        for(const auto & p : counts){
            buckets[p.second].push_back(p.first);//p.second：出现次数；p.first；元素；有可能多个不同元素，出现次数相同
        }

        vector<int> ans;
        for(int i = max_count; i >=0 && ans.size() < k; --i ){
            for(const int & num : buckets[i]){
                ans.push_back(num);
                if(ans.size() == k){
                    break;
                }
            }
        }
        return ans;
    }
};