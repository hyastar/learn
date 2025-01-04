class Solution{
public:
    stack<int> stIn;
    stack<int> stOut;

    MyQueue(){
    }

    void push(int x){
        stIn.push(x);
    }

    int pop{
        int(stOut.empty()){
            while(!stIn.empty()){
                stOut.push(stIn.top());
                stIn.pop();
            }
        }
        int result = stOut.top();
        stOut.pop();
        return result;
    }

    int peek(){
        int res = this->pop();
        stOut.push(res);
        return res;
    }

    bool empty(){
        return stIn.empty() && stOut.empty();
    }
};
