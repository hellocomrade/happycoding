//https://leetcode.com/problems/implement-stack-using-queues/
import java.util.Queue;
import java.util.LinkedList;
class MyStack {
    private Queue<Integer> q1 = new LinkedList<>();
    private Queue<Integer> q2 = new LinkedList<>();
    private void move(Queue<Integer> from, Queue<Integer> to) {
        while(from.peek() != null)
            to.add(from.remove());
    }
    // Push element x onto stack.
    public void push(int x) {
        if(q1.peek() == null){
            q1.add(x);
            move(q2, q1);
        }
        else {
            q2.add(x);
            move(q1, q2);
        }
    }

    // Removes the element on top of the stack.
    public void pop() {
        if(q1.peek() == null)q2.remove();
        else q1.remove();
    }

    // Get the top element.
    public int top() {
        if(q1.peek() == null)return q2.peek();
        else return q1.peek();
    }

    // Return whether the stack is empty.
    public boolean empty() {
        return q1.peek() == null && q2.peek() == null;
    }
}
