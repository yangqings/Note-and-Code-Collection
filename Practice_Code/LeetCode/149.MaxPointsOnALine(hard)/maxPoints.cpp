/**
 * @brief 此题特别需要注意的一点，求斜率时用double保存数据，可能会因为精度问题而导致误判
 *        解决这个问题有几个思路：
 *        1. long double
 *        2. 转换位string保存
 *        3. 判断一个点是否处于两点构成的直线上，将(x1)
 */
class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        unordered_map<long double, int> hash;         //<斜率，点数>
        int n = points.size();
        int same_y = 1, same = 1;
        int max_counts = 0;
        for(int i = 0; i < n; ++i){
            same_y = 1, same  = 1;
            for(int j = i + 1; j < n; ++j){           //前i个不用再遍历，因为在处理地i个时，i-1之前已经被处理过
                if(points[i][1] == points[j][1]){     //y相同, 额外标记，防止除零
                    ++same_y;
                     if(points[i][0] == points[j][0]){//x,y相同，同一点
                        ++same;
                    }
                } else {
                    long double dx = points[i][0] - points[j][0], dy = points[i][1] - points[j][1];
                    ++hash[ dx / dy ];
                }
            }

            for(auto item : hash){                    //不同斜率的最大点数
                max_counts = max(max_counts, same + item.second);
            }
            max_counts = max(max_counts, same_y);

            hash.clear();
        }
        return max_counts;
    }
};