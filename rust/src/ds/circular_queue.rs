pub struct CircularQueue {
    inner: Vec<i32>,
    length: usize,
    capacity: usize,
    rear: usize,
    front: usize,
}

impl CircularQueue {
    pub fn new(capacity: usize) -> Self {
        Self {
            inner: vec![0; capacity],
            length: 0,
            capacity: capacity,
            rear: 0,
            front: 0
        }
    }

    pub fn enqueue(&mut self, val: i32) -> Result<(), &'static str> {
        if self.is_full() {
            return Err("")
        }

        self.inner[self.rear] = val;
        self.rear = (self.rear + 1) % self.capacity;
        self.length += 1;
        Ok(())
    }

    pub fn dequeue(&mut self) -> Result<i32, &'static str> {
        if self.is_empty() {
            return Err("")
        }

        let front = self.front;
        self.front = (front + 1)% self.capacity;
        self.length -= 1;
        Ok(self.inner[front])
    }

    pub fn front(&self) -> Result<i32, &'static str> {
        if self.is_empty() {
            return Err("")
        }

        let front = self.front;

        Ok(self.inner[front])
    }

    pub fn is_empty(&self) -> bool {

        self.length == 0
    }

    pub fn is_full(&self) -> bool {
        self.length == self.capacity
    }

    pub fn size(&self) -> usize {
        self.length
    }

    pub fn max_size(&self) -> usize {
        self.capacity
    }
}


// clockwise
#[cfg(test)]
mod tests {
    use crate::Solution;

    use super::CircularQueue;

    #[test]
    fn circular_queue_basic() {
        let mut q = CircularQueue::new(3);
        assert!(q.is_empty());
        assert_eq!(q.max_size(), 3);

        q.enqueue(10).unwrap();
        q.enqueue(20).unwrap();
        q.enqueue(30).unwrap();
        assert!(q.is_full());
        assert_eq!(q.front().unwrap(), 10);

        assert_eq!(q.dequeue().unwrap(), 10);
        assert_eq!(q.dequeue().unwrap(), 20);
        assert!(!q.is_full());
        assert!(!q.is_empty());

        q.enqueue(40).unwrap(); // 래핑 확인
        q.enqueue(50).unwrap();
        assert!(q.is_full());
        assert_eq!(q.front().unwrap(), 30);
        assert_eq!(q.dequeue().unwrap(), 30);
        assert_eq!(q.dequeue().unwrap(), 40);
        assert_eq!(q.dequeue().unwrap(), 50);
        assert!(q.is_empty());
    }
}
