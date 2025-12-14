# PS (Problem Solving)

알고리즘 문제 풀이 저장소입니다.

## 사용 언어

- Rust (주력)
- C++
- Python

## 디렉토리 구조

```
PS/
├── rust/               # Rust 풀이
│   ├── src/
│   │   ├── bin/        # WIP (작업 중인 문제)
│   │   ├── leetcode/   # 완성된 LeetCode 문제
│   │   ├── boj/        # 백준 문제
│   │   └── util/       # 자료구조 및 유틸리티
│   ├── scripts/        # fetch-leet.sh, done.sh
│   ├── templates/      # 문제 템플릿
│   └── Makefile
├── cpp/                # C++ 풀이
│   ├── boj/            # 백준
│   ├── codeforces/     # Codeforces
│   ├── leetcode/       # LeetCode
│   ├── algospot/       # Algospot
│   └── misc/           # 기타
└── python/             # Python 풀이
    ├── boj/            # 백준
    └── programmers/    # 프로그래머스
```

## Rust 워크플로우

### LeetCode 문제 풀이

```bash
cd rust

# 1. 문제 가져오기 (src/bin/에 생성됨)
make fetch-leet SLUG=two-sum
# 또는 번호로
make fetch-leet-num NUM=1

# 2. 코드 작성 & 테스트
cargo run --bin leet_1_two_sum
cargo test --bin leet_1_two_sum

# 3. 완성 후 등록 (src/leetcode/로 이동)
make done NAME=two_sum

# WIP 목록 확인
make wip
```

**참고:** Tags는 `done` 시점에 LeetCode API에서 가져와 헤더에 추가됩니다 (힌트 방지).

### 수동 템플릿 생성

```bash
# LeetCode (직접 leetcode/에 생성)
make new-leet NUM=42 NAME="trapping-rain-water" DIFF=Hard TAGS="Stack,DP"

# BOJ
make new-boj NUM=1234 NAME="problem-name" DIFF=Gold3 TAGS="DP,Graph"

# 도움말
make help
```

## 주석 포맷 표준

### Rust (LeetCode)
```rust
//! # Problem Name
//!
//! - Platform: LeetCode
//! - Number: 123
//! - Difficulty: Easy/Medium/Hard
//! - Tags: Array, HashMap
//! - URL: https://leetcode.com/problems/slug/
```

### Rust (BOJ)
```rust
//! # Problem Name
//!
//! - Platform: BOJ
//! - Number: 1234
//! - Difficulty: Gold3
//! - Tags: DP, Graph
//! - URL: https://www.acmicpc.net/problem/1234
```

## 난이도 기준

| 플랫폼 | 표기 |
|--------|------|
| LeetCode | Easy / Medium / Hard |
| BOJ | Bronze5-1, Silver5-1, Gold5-1, Platinum5-1, Diamond5-1, Ruby5-1 |
| Codeforces | *800 ~ *3500 |
| Programmers | Lv.1 ~ Lv.5 |

## 알고리즘 태그

```
# 자료구조
Array, LinkedList, Stack, Queue, Deque, Heap, HashMap, HashSet,
Tree, BST, Trie, SegmentTree, FenwickTree, UnionFind

# 알고리즘
BinarySearch, TwoPointers, SlidingWindow, Sorting,
DFS, BFS, Backtracking, Greedy, DP, Memoization,
DivideAndConquer, Graph, ShortestPath, TopologicalSort,
String, Math, BitManipulation, Simulation
```

## 이전 풀이

[SimpleProject/algorithm_pr](https://github.com/lkic1625/SimpleProject/tree/master/algorithm_pr)
