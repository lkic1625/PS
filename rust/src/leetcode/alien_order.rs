use std::collections::HashSet;

/// There is a new alien language that uses the English alphabet. However, the order of the letters is unknown to you.
/// You are given a list of strings words from the alien language's dictionary. Now it is claimed that the strings in words are sorted lexicographically by the rules of this new language.
/// If this claim is incorrect, and the given arrangement of string in words cannot correspond to any order of letters, return "".
/// Otherwise, return a string of the unique letters in the new alien language sorted in lexicographically increasing order by the new language's rules. If there are multiple solutions, return any of them.

/// Example 1:
/// Input: words = ["wrt","wrf","er","ett","rftt"]
/// Output: "wertf"

/// 위상 정렬을 적용하면 바로 떠올릴 수 있는 문제이지만, 엣지 케이스 처리가 까다로웠음.
/// 1. abc -> ab 와 같은 형식이면 반드시 실패하는 케이스이기에 "" 처리
/// 2. DAG 가 아닌 cyclic graph 의 경우 "" 처리
/// 3. 모든 엣지끼리 연결이 안되는 경우, 방문 노드를 나열해야함.
struct Solution;

impl Solution {
    pub fn alien_order(words: Vec<String>) -> String {
        let mut indegree = vec![HashSet::new(); 26];
        let mut outdegree = vec![HashSet::new(); 26];
        let mut visited = vec![false; 26];

        for (i, word) in words.iter().enumerate() {
            let word = word.as_bytes();
            word.iter()
                .map(|&ch| (ch - b'a') as usize)
                .for_each(|i| visited[i] = true);
            if i == 0 {
                continue;
            }
            let bef = words[i - 1].as_bytes();
            let range = 0..(std::cmp::min(bef.len(), word.len()));

            for i in range {
                if bef[i] == word[i] {
                    continue;
                } else {
                    indegree[(word[i] - b'a') as usize].insert(bef[i]);
                    outdegree[(bef[i] - b'a') as usize].insert(word[i]);
                    break;
                }
            }
        }

        if indegree.iter().all(|edges| edges.is_empty()) {
            return visited
                .iter()
                .enumerate()
                .filter(|(i, x)| **x)
                .map(|(i, _)| (i as u8 + b'a') as char)
                .collect::<String>();
        }

        let mut queue = Vec::new();
        let mut ret = String::new();
        for (i, idg) in indegree.iter().enumerate() {
            if idg.len() == 0 && visited[i] {
                queue.push((b'a' + i as u8) as char);
            }
        }

        let total_vertices = visited.iter().filter(|x| **x).count();
        let mut visited = vec![false; 26];
        while !queue.is_empty() {
            let vertex = queue.pop().unwrap();
            let index = (vertex as u8 - b'a') as usize;
            if visited[index] {
                return "".to_string();
            } else {
                visited[index] = true;
                ret.push(vertex);
            }

            for &neighbor in &outdegree[index] {
                let n_index = (neighbor - b'a') as usize;
                indegree[n_index].remove(&(vertex as u8));
                if indegree[n_index].len() == 0 {
                    queue.push(neighbor as char);
                }
            }
        }
        let processed = visited.iter().filter(|x| **x).count();
        if processed != total_vertices {
            return "".to_string();
        }

        ret
    }
}
#[cfg(test)]
mod tests {
    use crate::Solution;

    #[test]
    fn test_alien_order_example1() {
        let words = vec![
            "wrt".to_string(),
            "wrf".to_string(),
            "er".to_string(),
            "ett".to_string(),
            "rftt".to_string(),
        ];
        let result = Solution::alien_order(words);
        assert_eq!(result, "wertf");
    }

    #[test]
    fn test_alien_order_same_words() {
        let words = vec!["za".to_string(), "za".to_string()];
        let result = Solution::alien_order(words);
        assert_eq!(result, "az");
    }

    #[test]
    fn test_alien_order_invalid() {
        let words = vec![
            "z".to_string(),
            "x".to_string(),
            "a".to_string(),
            "zb".to_string(),
            "zx".to_string(),
        ];
        let result = Solution::alien_order(words);
        assert_eq!(result, "");
    }
}
