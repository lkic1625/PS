// You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.
// Return the size of the largest island in grid after applying this operation.
// An island is a 4-directionally connected group of 1s.

// Example 1:
// Input: grid = [[1,0],[0,1]]
// Output: 3
// Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.

// Example 2:
// Input: grid = [[1,1],[1,0]]
// Output: 4
// Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 4.

// Example 3:
// Input: grid = [[1,1],[1,1]]
// Output: 4
// Explanation: Can't change any 0 to 1, only one island with area = 4.
//
// 매우 직관적이고 hard 치고 쉬운 문제로 보임, Union find 를 접근할 수는 있는데 유의미한지는 모르겠음.

use std::collections::HashSet;

struct Solution;

// clockwise
const DIRECTIONS: [(i32, i32); 4] = [(1, 0), (0, 1), (-1, 0), (0, -1)];

impl Solution {
    pub fn largest_island(grid: Vec<Vec<i32>>) -> i32 {
        let len = grid.len();
        let mut marker = vec![vec![-1; grid.len() + 2]; grid.len() + 2];
        let mut num_of_island = 0;
        let mut padded = vec![vec![-1; len + 2]; len + 2];
        for (i, row) in grid.into_iter().enumerate() {
            for (j, val) in row.into_iter().enumerate() {
                padded[i + 1][j + 1] = val;
            }
        }
        let mut island_landscape = Vec::new();
        for i in 1..=len {
            for j in 1..=len {
                if padded[i][j] == 1 && marker[i][j] == -1 {
                    island_landscape.push(Self::dfs(
                        i as i32,
                        j as i32,
                        &padded,
                        &mut marker,
                        num_of_island,
                    ));
                    num_of_island += 1;
                }
            }
        }

        let mut ret = *island_landscape.iter().max().unwrap();
        for i in 1..=len {
            for j in 1..=len {
                if padded[i][j] != 0 {
                    continue;
                }
                let mut set = HashSet::new();
                for direction in DIRECTIONS {
                    let ni = (i as i32 + direction.0) as usize;
                    let nj = (j as i32 + direction.1) as usize;
                    if padded[ni][nj] == 1 && marker[ni][nj] != -1 {
                        set.insert(marker[ni][nj]);
                    }
                }
                ret = std::cmp::max(
                    1 + set
                        .iter()
                        .map(|&index| island_landscape[index as usize])
                        .sum::<i32>(),
                    ret,
                );
            }
        }

        ret
    }

    pub fn dfs(i: i32, j: i32, grid: &Vec<Vec<i32>>, marker: &mut Vec<Vec<i32>>, idx: i32) -> i32 {
        let i = i as usize;
        let j = j as usize;
        if grid[i][j] == -1 || grid[i][j] == 0 {
            return 0;
        }

        if marker[i][j] != -1 {
            print!("{}", marker[i][j]);
            return 0;
        }

        marker[i][j] = idx;
        let mut ret = 1;
        for direction in DIRECTIONS {
            ret += Self::dfs(
                i as i32 + direction.0,
                j as i32 + direction.1,
                grid,
                marker,
                idx,
            );
        }

        ret
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example1() {
        let grid = vec![vec![1, 0], vec![0, 1]];
        assert_eq!(Solution::largest_island(grid), 3);
    }

    #[test]
    fn test_example2() {
        let grid = vec![vec![1, 1], vec![1, 0]];
        assert_eq!(Solution::largest_island(grid), 4);
    }

    #[test]
    fn test_example3() {
        let grid = vec![vec![1, 1], vec![1, 1]];
        assert_eq!(Solution::largest_island(grid), 4);
    }
}
