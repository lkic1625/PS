//! # Course Schedule II
//!
//! - Platform: LeetCode
//! - Number: 210
//! - Difficulty: Medium
//! - URL: https://leetcode.com/problems/course-schedule-ii/
//! - Tags: Depth-First Search,Breadth-First Search,Graph Theory,Topological Sort

// There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

// For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
// Return the ordering of courses you should take to finish all courses. If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.

// Example 1:
// Input: numCourses = 2, prerequisites = [[1,0]]
// Output: [0,1]
// Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1].

// Example 2:
// Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
// Output: [0,2,1,3]
// Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
// So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].

// Example 3:
// Input: numCourses = 1, prerequisites = []
// Output: [0]

use std::collections::VecDeque;

pub struct Solution;

impl Solution {
    pub fn find_order(num_courses: i32, prerequisites: Vec<Vec<i32>>) -> Vec<i32> {
        let mut parents = vec![Vec::new(); num_courses as usize];
        let mut childs = vec![0; num_courses as usize];
        for pre in prerequisites {
            parents[pre[1] as usize].push(pre[0]);
            childs[pre[0] as usize] += 1;
        }

        let mut q = VecDeque::new();
        for (i, &child) in childs.iter().enumerate() {
            if child == 0 {
                q.push_front(i);
            }
        }

        let mut ret = Vec::new();
        while !q.is_empty() {
            let node = q.pop_front().unwrap();
            ret.push(node as i32);
            for &parent in parents[node].iter() {
                childs[parent as usize] -= 1;
                if childs[parent as usize] == 0 {
                    q.push_front(parent as usize);
                }
            }
        }
        
        for child in childs {
            if child != 0 {
                return Vec::new();
            }
        }

        ret
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn is_valid_order(num_courses: i32, prerequisites: &[Vec<i32>], order: &[i32]) -> bool {
        if order.len() != num_courses as usize {
            return false;
        }
        let mut pos = vec![0usize; num_courses as usize];
        for (i, &c) in order.iter().enumerate() {
            pos[c as usize] = i;
        }
        prerequisites
            .iter()
            .all(|pre| pos[pre[1] as usize] < pos[pre[0] as usize])
    }

    #[test]
    fn test_example1() {
        let prereqs = vec![vec![1, 0]];
        let result = Solution::find_order(2, prereqs.clone());
        assert!(is_valid_order(2, &prereqs, &result));
    }

    #[test]
    fn test_example2() {
        let prereqs = vec![vec![1, 0], vec![2, 0], vec![3, 1], vec![3, 2]];
        let result = Solution::find_order(4, prereqs.clone());
        assert!(is_valid_order(4, &prereqs, &result));
    }

    #[test]
    fn test_example3() {
        let prereqs: Vec<Vec<i32>> = vec![];
        let result = Solution::find_order(1, prereqs.clone());
        assert!(is_valid_order(1, &prereqs, &result));
    }
}