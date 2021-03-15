//双指针，先排序，按start升序排列，当end[i] < end[i + 1]连续区间结束
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.size() == 0) return {};
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> merged;
        int len = intervals.size();

        for(int i = 0; i < len; ++i){
            int L = intervals[i][0], R = intervals[i][1];
            //end[i] < satrt[i + 1];
            if (!merged.size() || merged.back()[1] < L) { 
                merged.push_back({L, R});
            }
            else {//短区间被包含在长区间内部
                merged.back()[1] = max(merged.back()[1], R);
            }          
        }
        return merged;
    }
};