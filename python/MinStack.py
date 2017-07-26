class MinStack(object):

    def __init__(self):
       self.stack = list()

    def push(self, number):
        self.stack.append((number, number if 0 == len(self.stack) else min(number, self.stack[-1][1])))

    def pop(self):
        return self.stack.pop()[0]

    def min(self):
        return self.stack[-1][1]
