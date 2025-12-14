use std::cmp;

struct Solution;

impl Solution {
    pub fn job_scheduling(start_time: Vec<i32>, end_time: Vec<i32>, profit: Vec<i32>) -> i32 {
        let mut jobs = Vec::with_capacity(start_time.len());
        for i in 0..start_time.len() {
            jobs.push((start_time[i], end_time[i], profit[i]));
        }
        // padding
        jobs.push((-1, -1, 0));
        jobs.push((1000000001, 1000000001, 0));
        jobs.sort();

        let mut dp = vec![0; jobs.len()];
        for i in (0.. dp.len()).rev() {
            let target_time = jobs[i].1;
            let pos = jobs.binary_search_by(|&(start, _end, _profit)| {
                if start >= target_time {
                    cmp::Ordering::Greater
                } else {
                    cmp::Ordering::Less
                }
            }).unwrap_or_else(|pos| pos);
            let mut curr = jobs[i].2;
            if pos != jobs.len() {
                curr += dp[pos];
            }
            // dp[i] =  i ~ n까지 노드 중에 가장 큰 조합
            dp[i] = cmp::max(dp[i + 1], curr);
        }

        dp[0]
    }
}
