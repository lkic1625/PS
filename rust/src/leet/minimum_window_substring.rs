use std::collections::HashMap;

pub fn min_window(s: String, t: String) -> String {
    // t_set
    let s: Vec<char> = s.chars().collect();
    let t: Vec<char> = t.chars().collect();
    let mut t_counter: HashMap<char, usize> = HashMap::new();
    for (ch) in t.iter() {
        *t_counter.entry(*ch).or_insert(0) += 1;
    }

    let mut r = 0;
    let mut iter_counter: HashMap<char, usize> = HashMap::new();
    let mut str = String::new();
    let mut have = t_counter.keys().len();
    while have != 0 && r < s.len() {
        let nth = s[r];
        str.push(nth);
        let nth_counter = iter_counter.entry(nth).or_insert(0);
        *nth_counter += 1;

        if let Some(counter) = t_counter.get(&nth) {
            if  *counter == *nth_counter {
                have -= 1;
            }
        }
        r += 1;
    }

    if have != 0 {
        return String::default();
    }

    let mut l = 0;
    let mut ret = str.clone();
    let mut left = s[l];
    let mut left_size = iter_counter.entry(left).or_insert(0);
    let mut target = t_counter.entry(left).or_insert(0);
    while *left_size > *target && l < r {
        str.remove(0);
        l += 1;
        *left_size -= 1;
        left = s[l];
        left_size = iter_counter.entry(left).or_insert(0);
        target = t_counter.entry(left).or_insert(0);
    }

    if str.len() == t.len() {
        return str;
    }

    if str.len() < ret.len() {
        ret = str.clone();
    }

    while l < r && r < s.len() {
        let nth = s[r];
        str.push(nth);
        *iter_counter.entry(nth).or_insert(0) += 1;

        // Count result and shrink a left pointer
        let mut left = s[l];
        let mut left_size = iter_counter.entry(left).or_insert(0);
        let mut target = t_counter.entry(left).or_insert(0);
        while *left_size > *target && l < r {
            str.remove(0);
            l += 1;
            *left_size -= 1;
            left = s[l];
            left_size = iter_counter.entry(left).or_insert(0);
            target = t_counter.entry(left).or_insert(0);
        }

        if str.len() == t.len() {
            return str;
        }

        if str.len() < ret.len() {
            ret = str.clone();
        }

        r += 1;
    }

    // consider an impossible case
    ret
}
/**


impl Solution {
    pub fn min_window(s: String, t: String) -> String {
        let s_chars: Vec<char> = s.chars().collect();
        let t_chars: Vec<char> = t.chars().collect();

        if t_chars.is_empty() || s_chars.is_empty() {
            return String::new();
        }

        // t 문자 빈도 계산
        let mut t_counter = HashMap::new();
        for &ch in &t_chars {
            *t_counter.entry(ch).or_insert(0) += 1;
        }

        let mut window_counts = HashMap::new();
        let mut have = 0;
        let need = t_counter.len();

        let mut res = (0usize, usize::MAX); // (start_pos, end_pos)
        let mut left = 0;

        for right in 0..s_chars.len() {
            let ch = s_chars[right];
            *window_counts.entry(ch).or_insert(0) += 1;

            if let Some(&count_t) = t_counter.get(&ch) {
                if window_counts[&ch] == count_t {
                    have += 1;
                }
            }

            while have == need {
                // 업데이트 최소 윈도우
                if right - left < res.1 - res.0 {
                    res = (left, right);
                }

                // 슬라이딩 윈도우 왼쪽 축소
                let left_char = s_chars[left];
                *window_counts.get_mut(&left_char).unwrap() -= 1;
                if let Some(&count_t) = t_counter.get(&left_char) {
                    if window_counts[&left_char] < count_t {
                        have -= 1;
                    }
                }
                left += 1;
            }
        }

        if res.1 == usize::MAX {
            String::new()
        } else {
            s_chars[res.0..=res.1].iter().collect()
        }
    }
}
*/