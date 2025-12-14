use std::collections::HashMap;

struct Solution;

impl Solution {
    pub fn smallest_sufficient_team(req_skills: Vec<String>, people: Vec<Vec<String>>) -> Vec<i32> {
        // init
        let mut map = HashMap::new();
        let mut i:u8 = 0;
        for x in req_skills.iter() {
            map.insert(x, i);
            i += 1;
        }

        let len = people.len();
        let mut vec = Vec::new();
        let mut dp = vec![vec![-1; len + 1]; 1usize << 16];
        let mut i = 0i32;
        let mut j = 0;
        for person in people.iter() {
            for skill in person.iter() {
                i |= 1 << map.get(skill).unwrap();
            }

            dp[i as usize][1] = 1 << j;
            vec.push(i as usize);

            j += 1;
            i = 0;
        }

        let expected = (1 << req_skills.len()) - 1;
        let mut iteration = 2;
        let mut ans_vec = Vec::new();
        while iteration <= len {
            let mut temp = Vec::new();
            // permutation of vector
            for i in 0..vec.len() {
                for j in i + 1..vec.len() {
                    let (lhs, rhs, people_count) = (vec[i], vec[j], iteration - 1);
                    let bit = lhs | rhs;
                    let value = dp[lhs][people_count] | dp[rhs][people_count];
                    if bit == expected {
                        ans_vec.push(value);
                    }

                    let bit_size = Self::bit_count(value) as usize;
                    if (bit_size == iteration && dp[bit][bit_size] == -1) {
                        dp[bit][bit_size] = value;
                        temp.push(bit);
                    }
                }
            }

            if !ans_vec.is_empty() {
                let mut max = 1000;
                let mut ans = Vec::new();
                for v in ans_vec {
                    let vec = Self::bit_to_vec(v);
                    if vec.len() < max {
                        max = vec.len();
                        ans = vec;
                    }
                }

                return ans;
            }

            ans_vec.clear();
            vec.clear();
            vec.append(&mut temp);
            iteration += 1;
        }

        // Panic on invalid case.
        panic!("Error case occurred.");
    }

    pub fn bit_count(mut i: i64) -> i32 {
        let mut ret = 0;
        while i != 0 {
            if (i % 2 == 1) {
                ret += 1;
            }
            i /= 2
        }

        ret
    }

    pub fn bit_to_vec(mut i: i64) -> Vec<i32> {
        let mut ret = Vec::new();
        let mut counter = 0;
        while i != 0 {
            if (i % 2 == 1) {
                ret.push(counter);
            }
            counter += 1;
            i /= 2
        }

        ret
    }
}

#[cfg(test)]
mod test {
    use crate::Solution;

    #[test]
    fn example() {
        let req_skills = vec!["gvp","jgpzzicdvgxlfix","kqcrfwerywbwi","jzukdzrfgvdbrunw","k"]
            .iter().map(|&s| String::from(s)).collect();
        let people = vec![vec![],vec![],vec![],vec![],vec!["jgpzzicdvgxlfix"],vec!["jgpzzicdvgxlfix","k"],vec!["jgpzzicdvgxlfix","kqcrfwerywbwi"],vec!["gvp"],vec!["jzukdzrfgvdbrunw"],vec!["gvp","kqcrfwerywbwi"]]
            .iter().map(|v| v.iter().map(|&s| String::from(s)).collect()).collect();

        let result = Solution::smallest_sufficient_team(req_skills, people);
        let expected = vec![5, 8, 9];

        assert_eq!(result, expected);
    }

    #[test]
    fn bit_to_vec() {
        let mut i = 5i64;
        let result = Solution::bit_to_vec(i);
        let expected = vec![0, 2];
    }
}