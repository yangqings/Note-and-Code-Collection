//数字全排列，回溯算法
//技巧，由于需要给出数字排列组合，不需要新的容器存放新的排列，而是将原容器的元素swap(a,b)（排列），然后执行撤回操作swap(a,b)

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        backTrack(ans, nums, 0, nums.size());
        return ans;
    }

private:
    void backTrack(vector<vector<int>>& ans, vector<int>& output, int first, int len){
        if(first == len){
            ans.emplace_back(output);
            for(auto & num : output){
                cout<<num<<" ";
            }
            cout<<endl;            
            return;
        }
        for(int i = first; i < len; ++i){
            swap(output[i], output[first]);         //do choice
            backTrack(ans, output, first + 1, len);
            swap(output[i], output[first]);         //undo
        }
    }
};