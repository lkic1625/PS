use std::cell::RefCell;
use std::i32;
use std::rc::Rc;

// A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence at most once. Note that the path does not need to pass through the root.
// The path sum of a path is the sum of the node's values in the path.
// Given the root of a binary tree, return the maximum path sum of any non-empty path.

// Input: root = [-10,9,20,null,null,15,7]
// Output: 42
// Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.

// hard 아닌 듯, 그냥 dfs 만 잘하면 풀리는 문제임. 엣지케이스 고민은 해볼 수 있겠는데 이게 문제 난이도를 올린다고는 안 느껴짐

// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
    pub val: i32,
    pub left: Option<Rc<RefCell<TreeNode>>>,
    pub right: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
    #[inline]
    pub fn new(val: i32) -> Self {
        TreeNode {
            val,
            left: None,
            right: None,
        }
    }
}

struct Solution;

impl Solution {
    pub fn max_path_sum(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        let mut max_val = i32::MIN;
        let path_sum = if let Some(path_sum) = Self::dfs(root, &mut max_val) {
            return std::cmp::max(path_sum, max_val);
        };
        max_val
    }

    pub fn dfs(curr: Option<Rc<RefCell<TreeNode>>>, max_val: &mut i32) -> Option<i32> {
        if let Some(curr) = curr {
            let node = curr.borrow();
            let mut ret = node.val;
            let mut left: Option<i32> = Self::dfs(node.left.clone(), max_val);
            let mut right: Option<i32> = Self::dfs(node.right.clone(), max_val);
            if let Some(lv) = left {
                ret = std::cmp::max(node.val + lv, ret);
                *max_val = std::cmp::max(*max_val, lv);
            }
            if let Some(rv) = right {
                ret = std::cmp::max(node.val + rv, ret);
                *max_val = std::cmp::max(*max_val, rv);
            }

            if left.is_some() && right.is_some() {
                *max_val = std::cmp::max(node.val + left.unwrap() + right.unwrap(), *max_val);
            }

            *max_val = std::cmp::max(*max_val, ret);

            return Some(ret);
        }

        None
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    // 헬퍼 함수: 트리 노드를 쉽게 생성
    fn node(
        val: i32,
        left: Option<Rc<RefCell<TreeNode>>>,
        right: Option<Rc<RefCell<TreeNode>>>,
    ) -> Option<Rc<RefCell<TreeNode>>> {
        Some(Rc::new(RefCell::new(TreeNode { val, left, right })))
    }

    fn leaf(val: i32) -> Option<Rc<RefCell<TreeNode>>> {
        node(val, None, None)
    }

    #[test]
    fn test_example1() {
        // Input: root = [-10,9,20,null,null,15,7]
        // Output: 42
        // 트리 구조:
        //       -10
        //       / \
        //      9  20
        //        /  \
        //       15   7
        let root = node(-10, leaf(9), node(20, leaf(15), leaf(7)));
        assert_eq!(Solution::max_path_sum(root), 42);
    }

    #[test]
    fn test_example2() {
        // Input: root = [1,2,3]
        // Output: 6
        // 트리 구조:
        //      1
        //     / \
        //    2   3
        let root = node(1, leaf(2), leaf(3));
        assert_eq!(Solution::max_path_sum(root), 6);
    }
}
