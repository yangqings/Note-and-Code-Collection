/**
 * 解题思路：
 * 增加辅助栈存储最小元素
 * 1 元素每次入数据栈时，元素值小于当前辅助栈最小值，入辅助栈
 * 2 出栈时，出栈元素等于辅助栈栈顶元素，辅助栈栈顶元素同时出栈
 * 3 取最小值时间复杂度O(1)
 */
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        dataStack.push_back(x);
        if(minStack.empty()){
            minStack.push_back(x);
        }
        else if(x <= minStack.back()){
            minStack.push_back( x );
        }
    }
    
    void pop() {
        if(! dataStack.empty() ){
            if(minStack.back() == dataStack.back())
                minStack.pop_back();
            dataStack.pop_back();
        }
    }
    
    int top() {
        return dataStack.back();
    }
    
    int getMin() {
        return minStack.back();
    }
private:
    vector<int> dataStack;
    vector<int> minStack;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */