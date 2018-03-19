package leetcode

import scala.math.min

//https://leetcode.com/problems/min-stack/
class MinStack {
    /** initialize your data structure here. */
    
    private var stk: List[(Int, Int)] = List()
  
    def push(x: Int) {
        stk = (if(true == stk.isEmpty) x else min(x, stk(0)._1), x)::stk
    }
  
    def pop() {
        stk = stk.drop(1)
    }
  
    def top(): Int = {
        stk(0)._2 
    }
    
    def getMin(): Int = {
        stk(0)._1
    }
}
