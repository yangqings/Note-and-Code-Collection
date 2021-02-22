/**
 * @brief 重新规划行程 求解欧拉回路/欧拉通路，
 *        题目意思：“一笔画”，从指定起点出发，经过所有的边恰好一次，路径的字典序最小
 *                  题目保证存在这样的通路，也就是题目给出的数据必然是欧拉图或者半欧拉图
 *        思路：Hierholzer算法，这个hash + multiset实现的思路很巧妙！
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


/**
 * @brief Leetcode官方题解，求解欧拉回路/欧拉通路
 *        深度优先搜索 + 贪心 + 栈
 */

class Solution{
public:

    vector<string> findItinerary(vector<vector<string>>& tickets){

        for(auto& it : tickets){
            hash[it[0]].emplace(it[1]);
        }
        //DFS
        dfs("JFK");
        reverse(ans.begin(), ans.end());
        return ans;
    }
private:
    unordered_map<string, 
                  priority_queue<string, vector<string>,std::greater<string>>
                 > hash;
    vector<string> ans;
    
    void dfs(const string& str){
        while(hash.count(str) && hash[str].size() > 0){
            string tmp = hash[str].top();
            hash[str].pop();
            dfs(move(tmp));
        }
        ans.emplace_back(str);
    }

};