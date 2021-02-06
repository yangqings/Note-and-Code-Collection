/**
 * @brief 递增单调栈，栈顶保持最小元素
 *        新元素比栈顶元素小或栈空，入栈
 *        新元素比栈顶元素大，栈顶元素出栈
 */
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n);
        stack<int> indices;
        for(int i = 0; i < n; ++i) { //只需要把天数push进栈
            while( !indices.empty() ) {
                int pre_index = indices.top();
                if( temperatures[ i ] <= temperatures[ pre_index ] ) {
                    break;
                }
                indices.pop();
                ans[ pre_index ] = i - pre_index;
            }
            indices.push(i);
        }
        return ans;
    }
};