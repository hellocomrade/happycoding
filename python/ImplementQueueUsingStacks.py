class MyQueue(object):

    def __init__(self):
        self.stack1 = []
        self.stack2 = []
        

    def push(self, x):
        """
        Push element x to the back of queue.
        :type x: int
        :rtype: void
        """
        self.stack1.append(x)

    def swap(self):
        while len(self.stack1):
            self.stack2.append(self.stack1.pop())
            

    def pop(self):
        """
        Removes the element from in front of queue and returns that element.
        :rtype: int
        """
        if 0 == len(self.stack2):
            self.swap()
        return self.stack2.pop()
        

    def peek(self):
        """
        Get the front element.
        :rtype: int
        """
        if 0 == len(self.stack2):
            self.swap()
        return self.stack2[-1]
        

    def empty(self):
        """
        Returns whether the queue is empty.
        :rtype: bool
        """
        return 0 == len(self.stack1) and 0 == len(self.stack2)


# Your MyQueue object will be instantiated and called as such:
# obj = MyQueue()
# obj.push(x)
# param_2 = obj.pop()
# param_3 = obj.peek()
# param_4 = obj.empty()
