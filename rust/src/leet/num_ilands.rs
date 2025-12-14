
const NEIGHBORS: [(i32, i32); 4] = [(0, -1), (1, 0), (0, 1), (-1, 0)];

impl Solution {
    pub fn num_islands(grid: Vec<Vec<char>>) -> i32 {
        let mut expanded = vec![vec![false; grid[0].len() + 2]; grid.len() + 2];
        let mut vec = Vec::new();
        let mut visited = vec![vec![false; grid[0].len() + 2]; grid.len() + 2];

        for (i, row) in grid.iter().enumerate() {
            for (j, &c) in row.iter().enumerate() {
                if c == '1' {
                    expanded[i + 1][j + 1] = true;
                    vec.push((i + 1, j + 1));
                }
            }
        }

        let mut ret = 0;
        while let Some((i, j)) = vec.pop() {
            if visited[i][j] {
                continue;
            } else {
                ret += 1;

                let mut stack = vec![(i, j)];
                while let Some((i, j)) = stack.pop() {
                    visited[i][j] = true;
                    for (x, y) in NEIGHBORS.iter() {
                        let ni = (i as i32 + x) as usize;
                        let nj = (j as i32 + y) as usize;

                        if expanded[ni][nj] && !visited[ni][nj] {
                            stack.push((ni, nj));
                        }
                    }
                }
            }
        }

        ret
    }
}