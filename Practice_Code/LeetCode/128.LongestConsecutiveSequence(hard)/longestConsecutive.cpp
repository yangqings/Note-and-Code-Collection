
/**
 * @brief 无序数组，求数字最长连续长度，时间复杂度要求O(n)
 *        排序后再遍历一次，时间复杂度到不了O(n)
 */
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        //暴力解法
        int n = nums.size();
        if(n == 0)return 0;   

        sort(nums.begin(), nums.end());

        int ans = 1;
        int last = nums[0];//上一个元素
        int max = 1;

        for(int i = 1; i < n; ++i ){
            int temp = nums[i] - last;
            if( temp == 1){ //连续递增
                ans++;
            }else if(temp == 0){
                //ans = 1;
            }else{
                ans = 1;
            }
            if(ans > max){
                max = ans;
            }
            last = nums[i];
        }
        return max;
    }
};


/**
 * @brief Leetcode官方解，写的不是太好
 * 
 */
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> num_set;
        for (const int& num : nums) {
            num_set.insert(num);
        }

        int longestStreak = 0;

        for (const int& num : num_set) {
            if (!num_set.count(num - 1)) {
                int currentNum = num;
                int currentStreak = 1;

                while (num_set.count(currentNum + 1)) {
                    currentNum += 1;
                    currentStreak += 1;
                }

                longestStreak = max(longestStreak, currentStreak);
            }
        }

        return longestStreak;           
    }
};

/**
 * @brief 思路：
 *        1.unordered_set 存储数字（无重复元素）
 *        2.从一个元素开始，分别递减和递增，元素连续，且存在set中，erase移除，找到最大长度就是连续数字的最大长度
 */
class Solution{
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();
        if(n == 0)return 0;

        unordered_set<int> hashSet;
        for(const int& num : nums){
            hashSet.insert(num);
        }

        int ans = 0;
        while(!hashSet.empty()){
            int cur = *(hashSet.begin());
            hashSet.erase(cur);
            int next = cur + 1, prev = cur - 1;
            while(hashSet.count(next)){
                hashSet.erase(next++);
            }
            while(hashSet.count(prev)){
                hashSet.erase(prev--);
            }
            ans = max(ans, next - prev - 1);
        }
        return ans;
    }
};
