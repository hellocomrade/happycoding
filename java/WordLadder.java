//https://leetcode.com/problems/word-ladder/
//A more efficient version should be given shortly
import java.util.LinkedList;
import java.util.Set;
import java.util.Queue;
import java.util.ArrayList;
import java.util.HashMap;

public class SolutionWordLadder {
    //A faster version
    public int ladderLength(String beginWord, String endWord, Set<String> wordList) {
        int ans = 1, qsize = 0, len = beginWord.length();
        if(endWord.equals(beginWord))return ans;
        HashMap<String, ArrayList<String>> map = new HashMap<>();
        final char mask = '?';
        char oldChar;
        String key, str;
        wordList.add(endWord);
        for(String s : wordList) {
            if(s.equals(beginWord))continue;
            StringBuilder sb = new StringBuilder(s);
            for(int i = 0; i < len; ++i) {
                oldChar = s.charAt(i);
                sb.setCharAt(i, mask);
                key = sb.toString();
                if(false == map.containsKey(key))
                    map.put(key, new ArrayList<String>());
                map.get(key).add(s);
                sb.setCharAt(i, oldChar);
            }
        }
        Queue<String> q = new LinkedList<>();
        q.add(beginWord);
        while(false == q.isEmpty()) {
            qsize = q.size();
            for(int i = 0; i < qsize; ++i) {
                str = q.remove();
                if(str.equals(endWord))return ans;
                StringBuilder sb = new StringBuilder(str);
                for(int j = 0; j < len; ++j) {
                    oldChar = str.charAt(j);
                    sb.setCharAt(j, mask);
                    key = sb.toString();
                    if(true == map.containsKey(key)) {
                        ArrayList<String> al = map.get(key);
                        for(String s : al) q.add(s);
                        map.remove(key);
                    }
                    sb.setCharAt(j, oldChar);
                }
            }
            ++ans;
        }
        return 0;
    }
    /**
      * @param start, a string
      * @param end, a string
      * @param dict, a set of string
      * @return an integer
      */
    public int ladderLength1(String start, String end, Set<String> dict) {
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
