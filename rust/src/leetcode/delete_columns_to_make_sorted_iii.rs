use std::cmp::max;

struct Solution;

impl Solution {
    pub fn min_deletion_size(strs: Vec<String>) -> i32 {
        let n = strs.len();
        let str_len = strs.first().unwrap().len();
        let mut adj = vec![vec![0; str_len]; str_len];
        let mut dp = vec![vec![-1; str_len]; str_len];

        for i in 0..str_len {
            for j in i + 1.. str_len {
                let mut flag = true;
                for k in 0..n {
                    if strs[k].chars().nth(i) > strs[k].chars().nth(j) {
                        flag = false;
                        break;
                    }
                }
                if flag {
                    adj[i][j] = 1;
                }
            }
        }

        let mut ret = 0;
        for i in 0..str_len {
            ret = max(1 + Solution::dp(&adj, &mut dp, i, str_len - 1), ret);
        }

        str_len as i32 - ret
    }

    pub fn dp(adj: &Vec<Vec<i32>>, cache: &mut Vec<Vec<i32>>, i: usize, j: usize) -> i32 {
        if cache[i][j] != -1 {
            return cache[i][j];
        }

        if j - i <= 1 {
            return adj[i][j];
        }

        let mut ret = 0;
        for idx in i + 1..=j {
            if adj[i][idx] == 1 {
                ret = max(1 + Solution::dp(adj, cache, idx, j), ret);
            }
        }

        cache[i][j] = ret;
        cache[i][j]
    }
}

#[cfg(test)]
mod test {
    use crate::Solution;

    #[test]
    fn test() {
        let strs = ["baabab"].iter().map(|&s| String::from(s)).collect();
        let ret = Solution::min_deletion_size(strs);

        assert_eq!(ret, 2)
    }
}