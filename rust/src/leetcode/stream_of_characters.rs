use std::collections::HashMap;

struct Solution;

struct StreamChecker {
    trie: Trie,
    str: String,
    max_len: usize
}


#[derive(Default)]
struct TrieNode {
    is_end: bool,
    children: HashMap<char, TrieNode>,
}


struct Trie {
    root: TrieNode
}

impl Trie {
    pub fn new(words: Vec<String>) -> Self {
        let mut root = TrieNode::default();
        for word in words.iter() {
            let mut node = &mut root;
            for ch in word.chars().rev() {
                node = node.children.entry(ch).or_default();
            }
            node.is_end = true;
        }
        Trie {
            root
        }
    }

    pub fn find(&self, query: &String) -> bool {
        let mut node = &self.root;

        for ch in query.chars() {
            match node.children.get(&ch) {
                Some(found) => {
                    if found.is_end {
                        return true;
                    }
                    node = found;
                }
                None => return false,
            }
        }

        node.is_end
    }
}


/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl StreamChecker {

    fn new(words: Vec<String>) -> Self {
        let mut max_len = 0;
        for w in words.iter() {
            max_len = std::cmp::max(max_len, w.len());
        }
        Self {
            str: String::with_capacity(words.len()),
            trie: Trie::new(words),
            max_len
        }
    }

    fn query(&mut self, letter: char) -> bool {
        self.str.push(letter);
        self.str = self.str.chars().rev().take(self.max_len).collect::<Vec<_>>().into_iter().rev().collect();
        let test = self.trie.find(&self.str.chars().rev().collect::<String>());
        test
    }
}

/**
 * Your StreamChecker object will be instantiated and called as such:
 * let obj = StreamChecker::new(words);
 * let ret_1: bool = obj.query(letter);
 */

#[cfg(test)]
mod test {
    use crate::StreamChecker;

    #[test]
    fn test() {
        let words = vec!["ab", "a"]
            .iter().map(|&s| String::from(s)).collect();
        let mut obj = StreamChecker::new(words);
        let ret_1: bool = obj.query('a');
        let ret_1: bool = obj.query('a');
        let ret_1: bool = obj.query('b');
        assert_eq!(ret_1, true)
    }
}