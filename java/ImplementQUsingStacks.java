import java.util.Stack;
class MyQueue {
    private Stack<Integer> stk1 = new Stack<>();
    private Stack<Integer> stk2 = new Stack<>();
    private void move() {
        while(stk1.empty() == false)
            stk2.push(stk1.pop());
    }
    // Push element x to the back of queue.
    public void push(int x) {
        stk1.push(x);
    }

    // Removes the element from in front of queue.
    public void pop() {
        if(stk2.empty())move();
        stk2.pop();
    }

    // Get the front element.
    public int peek() {
        if(stk2.empty())move();
        return stk2.peek();
    }

    // Return whether the queue is empty.
    public boolean empty() {
        return stk1.empty() && stk2.empty();
    }
}
