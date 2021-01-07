/**
 * @brief 给定一个区间的集合，找到需要移除区间的最小数量，使剩余区间互不重叠。
 *        先根据end时间排序，从最小end时间开始找下一个，start时间不重叠，因为end时间已经排序，所以按顺序找到的下一个区间必然是最小的不重叠区间
 *        找不重叠最大区间数count，区间总数减去count即是需要移除的区间最小数量
 */

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        //先对end时间进行排序
        if(intervals.empty())return 0;
        sort(intervals.begin(), intervals.end(), [](const auto& u, const auto& v){
            return u[1] < v[1];  //intervals[][1]也就是end时间
        });

        int n = intervals.size();
        int count = 1, end = intervals[0][1];

        for(auto& interv : intervals){
            //cout<<interv[0]<<" "<<interv[1]<<",";
            int start = interv[0];
            if(start >= end){
                count++;
                end = interv[1];
            }
        }
        return n - count;
    }
};