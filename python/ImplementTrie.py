#https://leetcode.com/problems/implement-trie-prefix-tree
class TrieNode:
    
    def __init__(self, endHere):
        self.buckets, self.isEnd = {}, endHere
        
class Trie:
    
    def __init__(self):
        """
        Initialize your data structure here.
        """
        self._root = TrieNode(False)

    def insert(self, word):
        """
        Inserts a word into the trie.
        :type word: str
        :rtype: void
        """
        if word is None:
            return
        tnode = self._root
        for c in word:
            if c not in tnode.buckets: 
                tnode.buckets[c] = TrieNode(False)
            tnode = tnode.buckets[c]
        tnode.isEnd = True
    
    def _dfs(self, word):
        if word is None:
            return False
        tnode = self._root
        for c in word:
            if c not in tnode.buckets:
                return None
            tnode = tnode.buckets[c]
        return tnode
    
    def search(self, word):
        """
        Returns if the word is in the trie.
        :type word: str
        :rtype: bool
        """
        tnode = self._dfs(word)
        return None != tnode and True == tnode.isEnd

    def startsWith(self, prefix):
        """
        Returns if there is any word in the trie that starts with the given prefix.
        :type prefix: str
        :rtype: bool
        """
        tnode = self._dfs(prefix)
        return None != tnode


# Your Trie object will be instantiated and called as such:
# obj = Trie()
# obj.insert(word)
# param_2 = obj.search(word)
# param_3 = obj.startsWith(prefix)
