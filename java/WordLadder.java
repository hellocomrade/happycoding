//https://leetcode.com/problems/word-ladder/
//A more efficient version should be given shortly
import java.util.LinkedList;
import java.util.Set;
public class SolutionWordLadder {
    /**
      * @param start, a string
      * @param end, a string
      * @param dict, a set of string
      * @return an integer
      */
    public int ladderLength(String start, String end, Set<String> dict) {
        if(start.equals(end))return 1;
        LinkedList<String> queue = new LinkedList<>();
        queue.add(start);
        int sz = 0, len = start.length(), count = 1;
        String candidate = null, node = null;
        StringBuilder root = null;
        char oldChr;
        while(queue.size() > 0) {
            sz = queue.size();
            for(int i = 0; i < sz; ++i) {
                root = new StringBuilder(queue.pop());
                for(int j = 0; j < len; ++j) {
                    for(char k = 'a'; k <= 'z'; ++k) {
                        oldChr = root.charAt(j);
                        root.setCharAt(j, k);
                        node = root.toString();
                        if(node.equals(end))return count + 1;
                        if(dict.contains(node)) {
                            queue.add(node);
                            dict.remove(node);
                        }
                        root.setCharAt(j, oldChr);
                    }
                }
            }
            ++count;
        }
        return 0;
    }
}
