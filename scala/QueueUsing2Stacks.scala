import scala.io.StdIn
import java.util.Scanner

/*
I cheat here by using List, which can access elements from both sides...

So, instead of needing two "stacks", I only have one List here coz Stack is deprecated for Scala anyway.

The companion object is for HackerRanker, however, it got an ETL probably due to the wrong time limit setup for Scala at their end...

The reason I keep two versions is because I really love/hate HackerRanker who left handing input and output to end user, which gave me
an opportunity to play with scala stdin, java scanner and pattern match! Bonus!
*/
//https://leetcode.com/problems/implement-queue-using-stacks/
class QueueUsing2Stacks {
  private var stk: List[Int] = List()
    /** Initialize your data structure here. */
    

    /** Push element x to the back of queue. */
    def push(x: Int) {
        stk = x :: stk
    }

    /** Removes the element from in front of queue and returns that element. */
    def pop(): Int = {
        val i: Int = stk.last
        stk = stk.dropRight(1)
        i
    }

    /** Get the front element. */
    def peek(): Int = {
        stk.last
    }

    /** Returns whether the queue is empty. */
    def empty(): Boolean = {
        stk.isEmpty
    }
}
//https://www.hackerrank.com/challenges/queue-using-two-stacks/problem
object QueueUsing2Stacks {
    def solution(args: Array[String]) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution
*/
        val optcnt: Int = StdIn.readInt()
        var stk1: List[Int] = List() 
        for(i <- 1 to optcnt) {
            val line = new Scanner(StdIn.readLine())
            line.nextInt match {
                case 1 => stk1 = line.nextInt :: stk1 
                case 2 => stk1 = stk1.dropRight(1)
                case 3 => println(stk1.last)
            }
        }
    }
}
