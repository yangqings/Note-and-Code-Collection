/**
 * @brief 一个栈作为输入，一个栈作为输出
 *        可以在push操作或者pop操作时，将输入栈的元素反转放到输出栈
 */
class MyQueue {
public:
    /** Initialize your data structure here. */
    stack<int> in,out;
    MyQueue() {}
    
    /** Push element x to the back of queue. */
    void push(int x) {
        in.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() { /*判断out Stack是否为空，为空则把in stack搬运过去，使得最先入栈的元素在out stack的栈顶*/
        in2out();
        int x = out.top();
        out.pop();
        return x;
    }
    
    /** Get the front element. */
    int peek() {
        in2out();/*判断out Stack是否为空，为空则把in stack搬运过去，使得最先入栈的元素在out stack的栈顶*/
        return out.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return (in.empty() && out.empty());
    }

    void in2out(){
        if(out.empty()){/*必须是要空stack才能push*/
            while(!in.empty()){
                int x = in.top();
                in.pop();
                out.push(x);
            }
        }
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */