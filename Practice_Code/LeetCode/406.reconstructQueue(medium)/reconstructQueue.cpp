//按照[hi, ki]排队，h为身高，k为前面有多少个人同高或者更高
//处理技巧，两个因素（身高、位次）按照相反的顺序排列，再来处理
class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        //按身高升序，若身高相同，按K降序，排列
        sort(people.begin(), people.end(), [](const vector<int>& P1, const vector<int>& P2){
            return P1[0] > P2[0] || (P1[0] == P2[0] && P1[1] < P2[1]);
        });

        vector<vector<int>> queue; 
        for(auto& item : people){
            if(queue.size() < item[1]) queue.push_back(item);
            else{
                queue.insert(queue.begin() + item[1], item);
            }
        }

        return queue;
    }
};