/**
 * @brief 桶排序解决前 K 个高频元素问题
 * 解题思路：
 * 1.为每个值设立一个桶，桶内记录这个值出现的次数
 * 2.对桶进行排序，得到每个数字出现次数的排序
 * 3.将前k个高频元素push进vector
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

/**  1.统计词频
 *   2.根据词频，维持一个总大小为k的小顶堆
 *   3.判断下一个元素词频小于堆顶，则舍弃，大于堆顶，则pop堆顶，emplace进堆
 *   4.遍历完所有词频统计，得到的堆就是词频前k高的元素
 * */

class Solution{

public:
    vector<int> topKFrequent(vector<int>& nums, int k){
        unordered_map<int, int> occurences;
        for(auto& num : nums){
            occurences[num]++;
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&cmp)> q(cmp);

        for(auto& [num,count] : occurences){
            if(q.size() == k){
                if(q.top().second < count){//count大于堆顶，将堆顶元素pop
                    q.pop();
                    q.emplace(num, count);
                }
            }else{//小于k，继续往堆emplace
                q.emplace(num, count);
            }
        }

        vector<int> ret;
        while(!q.empty()){
            ret.emplace_back(q.top().first);
            q.pop();
        }
        return ret;
    }

private:
    static bool cmp(pair<int, int>& m, pair<int, int>& n){
        return m.second > n.second;
    }

};