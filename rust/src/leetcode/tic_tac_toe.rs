struct Player {
    rows :Vec<i128>,
    cols: Vec<i128>,
    left_diagonal: i128,
    right_diagonal: i128,
    n: i32,
    win_condition: i128,
    idx: i32
}

struct TicTacToe {
    p1: Player,
    p2: Player,
}

impl Player {
    fn new(n: i32, idx: i32) -> Self {
        Player {
            rows: vec![0; n as usize],
            cols: vec![0; n as usize],
            left_diagonal: 0,
            right_diagonal: 0,
            n,
            win_condition: (1 << n) - 1,
            idx
        }
    }

    fn make_a_move(&mut self, row: i32, col: i32) -> i32 {
        self.rows[row as usize] |= 1 << col;
        if self.rows[row as usize] == self.win_condition {
            return self.idx
        }
        self.cols[col as usize] |= 1 << row;
        if self.cols[col as usize] == self.win_condition {
            return self.idx
        }

        if row == col {
            self.left_diagonal |= 1 << row;
            if self.left_diagonal == self.win_condition {
                return self.idx
            }
        }

        if row + col == self.n - 1 {
            self.right_diagonal |= 1 << col;
            if self.right_diagonal == self.win_condition {
                return self.idx
            }
        }

        0
    }
}


/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl TicTacToe {

    fn new(n: i32) -> Self {
        TicTacToe {
            p1: Player::new(n, 1),
            p2: Player::new(n, 2)
        }
    }

    fn make_a_move(&mut self, row: i32, col: i32, player: i32) -> i32 {
        if player == 1 {
            self.p1.make_a_move(row, col)
        } else {
            self.p2.make_a_move(row, col)
        }
    }
}

/**
 * Your TicTacToe object will be instantiated and called as such:
 * let obj = TicTacToe::new(n);
 * let ret_1: i32 = obj.move(row, col, player);
 */