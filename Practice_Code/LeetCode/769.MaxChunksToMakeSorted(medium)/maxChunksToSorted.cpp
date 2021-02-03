/**
 * @brief 最多能完成排序的块
 *        需要注意题目的条件：
 *        1.数组元素的值的范围是数组长度
 *        2.元素不重复 0~n
 *        解题思路：
 *        1.当遍历到数组的位置 i 时，i == max(arr[0]~arr[i-1]), chunk++
 */
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size();
        if(n == 0)return 0;

        int ans = 0, num_max = arr[0];

        for(int i = 0; i < n; ++i){
            if(arr[i] > num_max) num_max = arr[i];
            if(num_max == i){
                ++ans;
            }
        }
        return ans;
    }
};