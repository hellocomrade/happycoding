package leetcode

//https://leetcode.com/problems/valid-parentheses/
object ValidParentheses {
    def isValid(s: String): Boolean = {
        if(null == s || true == s.isEmpty)
            return false
        var stk : List[Char] = List()
        for (c <- s) {
            c match {
                case '(' => stk = ')' :: stk
                case '{' => stk = '}' :: stk
                case '[' => stk = ']' :: stk
                case _ => {
                    if(stk.isEmpty || stk.head != c)
                        return false
                    else
                        stk = stk.drop(1)
                }
            }
        }
        return stk.isEmpty
    }  
}
