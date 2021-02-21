/**
 * @brief 重新规划行程 常规思路可能会想到图
 *        思路：这个思路很难想到！
 *             1.Hash + MultiSet（维持有序，元素可重复）
 *             2.使用栈保存路径，最后取反，得到最终结果！
 */

class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        vector<string> ans;
        if(tickets.empty()){
            return ans;
        }

        unordered_map<string, multiset<string>> hash; //hash <start, end>
        for(const auto & ticket : tickets){           //由于相同起点，终点有多种情况，且题目要求按字典序排列
            hash[ticket[0]].insert(ticket[1]);        //所以用MultiSet保存
        }

        stack<string> s;
        s.push("JFK");

        while(!s.empty()){
            string next = s.top();
            if(hash[next].empty()){                    //start --> empty
                ans.push_back(next);                  
                s.pop();
            }else{
                s.push( *hash[next].begin() );         //将start-->end中的end保存
                hash[next].erase( hash[next].begin() );//重要步骤，将end删除
            }
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};