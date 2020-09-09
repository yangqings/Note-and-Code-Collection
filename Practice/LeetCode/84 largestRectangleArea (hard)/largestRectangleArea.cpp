class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        //1.暴力解法，遍历数组，每次从数组向两边求最大面积
        //2.结果：超时无法通过
        int n = heights.size();
        int ans = 0;

        for (int left = 0; left < n; left++){
            int minHeight = INT_MAX;

            for (int right = left; right < n; right++){
                minHeight = min(minHeight, heights[right]);
                ans = max(ans, ( right - left + 1 ) * minHeight);
            }
            
        }

        return ans;
    }
};


class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        //1.优化解法,枚举每个高度的柱子对应的左边界和右边界
        //2.利用单调栈，也就是栈中存放的元素具有单调性
        //3.注意出栈的原则：遇到最近的小于当前height[i]的柱子作为边界，则大于当前height[i]的柱子都应该出栈
        //4.每次枚举一个height[i],完成出栈和入栈后，栈的前一个值就是当前元素的边界
    
        int n = heights.size();
        int ans = 0;
        vector<int> left(n), right(n);

        stack<int> men_stack;
        for (int i = 0; i < n; ++i){
            while (!men_stack.empty() && heights[men_stack.top()] >= heights[i]){
                men_stack.pop();
            }
            left[i] = (men_stack.empty() ? -1 : men_stack.top());
            men_stack.push(i);
        }

        men_stack = stack<int> ();
        for(int i = n-1; i >= 0; --i){
            while(!men_stack.empty() && heights[men_stack.top()] >= heights[i]){
                men_stack.pop();
            }
            right[i] = (men_stack.empty() ? n+1 : men_stack.top());
            men_stack.push(i);
        }

        for(int i = 0; i < n; ++i){
            ans = max(ans, (right[i]-left[i]-1)*heights[i]);
        }

        return ans;
    }
};


class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
    //常数优化
    int n = heights.size();
    vector<int> left(n),right(n,n);

    stack<int> mono_stack;
    for(int i = 0; i < n; ++i){
        while(!mono_stack.empty()  && heights[mono_stack.top()] >= heights[i]){
            right[mono_stack.top()] = i;
            mono_stack.pop();
        }
        left[i] = (mono_stack.empty() ? -1 : mono_stack.top());
        mono_stack.push(i);
    }
    
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        ans = max(ans, (right[i] - left[i] - 1)*heights[i]);
    }
    
    return ans;
    }
};

