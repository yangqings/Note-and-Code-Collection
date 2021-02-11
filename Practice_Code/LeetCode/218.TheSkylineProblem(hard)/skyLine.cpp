
/**
 * @brief 优先队列，求解skyline
 * 
 */
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {

        vector<vector<int>> ans;
        priority_queue<pair<int, int>> max_heap;//<高度，右端点>
        int i = 0, len = buildings.size();
        int cur_x, cur_h;

        while( i < len || !max_heap.empty() ){

            //if：优先队列为空 && 当前建筑的左端点 小于等于 队列最大高度建筑右端点
            if(max_heap.empty() || i < len && buildings[i][0] <= max_heap.top().second){
                cur_x = buildings[i][0];
                //cout<<"cur_x_left: "<<cur_x<<endl;
                while(i < len && cur_x == buildings[i][0]){
                    max_heap.emplace(buildings[i][2], buildings[i][1]);//<高度，右端点>
                    ++i;
                }
            }else{
                cur_x = max_heap.top().second;
                //cout<<"cur_x_right: "<<cur_x<<endl;
                while(!max_heap.empty() && cur_x >= max_heap.top().second){
                    max_heap.pop();
                }
            }

            cur_h = (max_heap.empty()) ? 0 : max_heap.top().first;
            if(ans.empty() || cur_h != ans.back()[1]){
                ans.push_back({cur_x,cur_h});
            }
        }

        return ans;
    }
};

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        multiset<pair<int, int>> all;
        vector<vector<int>> res;
        
        for (auto& e : buildings) {
            all.insert(make_pair(e[0], -e[2])); // critical point, left corner
            all.insert(make_pair(e[1], e[2]));  // critical point, right corner
        }
        
        multiset<int> heights({0}); // 保存当前位置所有高度。
        vector<int> last = {0, 0};  // 保存上一个位置的横坐标以及高度
        for (auto& p : all) {
            if (p.second < 0) heights.insert(-p.second); // 左端点，高度入堆
            else heights.erase(heights.find(p.second));  // 右端点，移除高度
            
            // 当前关键点，最大高度
            auto maxHeight = *heights.rbegin();
            
            // 当前最大高度如果不同于上一个高度，说明这是一个转折点
            if (last[1] != maxHeight) {
                // 更新 last，并加入结果集
                last[0] = p.first;
                last[1] = maxHeight;
                res.push_back(last);
            }
        }
        
        return res;
    }
};
