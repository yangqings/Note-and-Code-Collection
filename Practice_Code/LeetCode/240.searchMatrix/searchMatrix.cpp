/**
 * @brief 已排序二维数组找到目标元素
 *        1.选取右上角为第一个查找目标
 *        2.target < 元素，往左查找
 *        3.target > 元素，往下查找
 *        4.命中返回true，直到左下角不命中，返回false
 */
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        
        int m = matrix.size();

        if(m == 0){
            return false;
        }

        int n = matrix[0].size();
        int i = 0, j = n - 1;

        while(i < m && j >= 0){ 
            if(matrix[i][j] == target){
                return true;
            }else if(matrix[i][j] > target){
                j --;
            }else{
                i ++;
            }       
        }
        return false;
    }
};


/**
 * @brief 已排序二维数组找到目标元素
 *        二分查找
 */


