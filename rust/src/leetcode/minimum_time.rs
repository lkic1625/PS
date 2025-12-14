
/**
 * parallel-courses-iii(hard)
 * You are given an integer n, which indicates that there are n courses labeled from 1 to n. You are also given a 2D integer array relations where relations[j] = [prevCoursej, nextCoursej] denotes that course prevCoursej has to be completed before course nextCoursej (prerequisite relationship). Furthermore, you are given a 0-indexed integer array time where time[i] denotes how many months it takes to complete the (i+1)th course.
 * 
 * You must find the minimum number of months needed to complete all the courses following these rules:
 * You may start taking a course at any time if the prerequisites are met.
 * Any number of courses can be taken at the same time.
 * Return the minimum number of months needed to complete all the courses.
 * 
 * Note: The test cases are generated such that it is possible to complete every course (i.e., the graph is a directed acyclic graph).
 */

/**
 * 위상정렬 기준으로 DP를 이용하는 솔루션도 존재할 수 있음.
 * 단순한 Graph DP 문제로 풀었음.
 */

impl Solution {
    pub fn minimum_time(n: i32, relations: Vec<Vec<i32>>, mut time: Vec<i32>) -> i32 {
        time.insert(0, 0);
        let mut branch = vec![Vec::new(); (n + 1) as usize];
        let mut outdegries = vec![0; (n + 1) as usize];
        let mut memo = vec![-1; (n + 1) as usize];
        
        for vec in relations {
            let relation = (vec[0], vec[1]);
            branch[relation.1 as usize].push(relation.0);
            outdegries[relation.0 as usize] += 1;
        }

        let mut root: i32 = -1;
        let mut ret = 0;
        for (i, &indegree) in outdegries.iter().enumerate() {
            if indegree == 0 && i != 0 && branch[i].len() != 0 {
                ret = std::cmp::max(time[i] + Self::dfs(i as i32, &branch, &time, &mut memo), ret);
            }
        }
        ret
    }

    fn dfs(bef: i32, branch: &Vec<Vec<i32>>, time: &Vec<i32>, memo: &mut Vec<i32>) -> i32 {
        if memo[bef as usize] != -1 {
            return memo[bef as usize];
        }
        
        let mut ret = 0;
        for &child in &branch[bef as usize] {
            ret = std::cmp::max(time[child as usize] + Self::dfs(child, branch, time, memo), ret);
        }
        
        memo[bef as usize] = ret;

        ret
    }
}

#[cfg(test)]
mod tests {
    use crate::Solution;

    #[test]
    fn test_case_1() {
        let n = 5;
        let relations = vec![vec![1, 5], vec![2, 5], vec![3, 5], vec![3, 4], vec![4, 5]];
        let time = vec![1, 2, 3, 4, 5];

        let result = Solution::minimum_time(n, relations, time);
        assert_eq!(result, 12);
    }

    #[test]
    fn test_case_2() {
        let n = 6;
        let relations = vec![vec![1, 3], vec![3, 2], vec![1, 6]];
        let time = vec![1, 8, 4, 7, 2, 6];

        let result = Solution::minimum_time(n, relations, time);
        assert_eq!(result, 13);
    }
    
    #[test]
    fn test_case_3() {
        let n = 3;
        let relations = vec![vec![2, 3]];
        let time = vec![3, 1, 1];

        let result = Solution::minimum_time(n, relations, time);
        assert_eq!(result, 3);
    }
}
