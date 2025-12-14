//! # {{NAME}}
//!
//! - Platform: BOJ
//! - Number: {{NUM}}
//! - Difficulty: {{DIFF}}
//! - Tags: {{TAGS}}
//! - URL: https://www.acmicpc.net/problem/{{NUM}}

use std::io::{self, BufRead, BufWriter, Write};

fn main() {
    let stdin = io::stdin();
    let stdout = io::stdout();
    let mut out = BufWriter::new(stdout.lock());

    let mut lines = stdin.lock().lines();

    // TODO: implement solution

    out.flush().unwrap();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example() {
        todo!()
    }
}
