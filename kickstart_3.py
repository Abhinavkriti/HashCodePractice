from collections import defaultdict


class TrieNode:
    def __init__(self):
        self.children = defaultdict()
        self.terminating = False

class Trie:
    def __init__(self, K):
        self.root = TrieNode()
        self.K = K

    def get_index(self, ch):
        return ord(ch) - ord('a')

    def insert(self, word):
        root = self.root
        len1 = len(word)
        for i in range(len1):
            index = self.get_index(word[i])
            if index not in root.children:
                root.children[index] = self.TrieNode()
            root = root.children.get(index)
        root.terminating = True

    def find_scores(self):
        root = self.root
        for i in self.root.children:
            if(i.size() > self.K):
                root = root.children
            if not root:
                return False
            root = root.children.get(index)
        return root if root and root.terminating else None
        
    
