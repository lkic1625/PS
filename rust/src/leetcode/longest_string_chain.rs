
impl Solution {
    pub fn longest_str_chain(mut words: Vec<String>) -> i32 {
        let n = words.len();
        let mut chain = vec![vec![0; n]; n];

        words.sort_by(|lhs, rhs| {
            return lhs.len().cmp(&rhs.len());
        });

        for i in 0..n {
            for j in i + 1..n {
                if Solution::is_predecessor(&words[i], &words[j]) {
                    chain[i][j] = 1;
                }
            }
        }

        // dp[l][r] = l..r 최대 거리
        let mut cache = vec![vec![-1; n]; n];
        let mut ret = 0;

        for i in 0..n {
            ret = std::cmp::max(Self::dp(&mut cache, &chain, i, n - 1), ret);
        }

        ret + 1
    }

    pub fn dp(cache: &mut Vec<Vec<i32>>, chain: &Vec<Vec<i32>>, l: usize, r: usize) -> i32 {
        if cache[l][r] != -1 {
            return cache[l][r];
        }

        if l + 1 == r {
            return chain[l][r];
        }

        let mut ret = 0;
        for i in l + 1..=r {
            if chain[l][i] == 1 {
                ret = std::cmp::max(1 + Self::dp(cache, chain, i, r), ret);
            }
        }

        cache[l][r] = ret;
        ret
    }

    pub fn is_predecessor(lhs: &String, rhs: &String) -> bool {
        if lhs.len() + 1 == rhs.len() {
            let mut i = 0;
            let mut j = 0;
            let mut flag = false;
            while j < rhs.len() {
                if lhs.chars().nth(i) == rhs.chars().nth(j) {
                    i += 1;
                    j += 1;
                } else {
                    j += 1;
                    if flag {
                        return false;
                    }
                    flag = true;
                }

                if i == lhs.len() {
                    return true;
                }
            }
        }

        false
    }
}
