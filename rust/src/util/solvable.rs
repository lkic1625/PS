pub trait Solvable<O> {

    fn solve(&mut self) -> O;
}