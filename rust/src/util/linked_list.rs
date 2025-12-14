use std::marker::PhantomData;
use std::ptr::null_mut;

struct Node {
    val: i32,
    next: *mut Node,
    prev: *mut Node,
}

struct LinkedList {
    head: *mut Node,
    tail: *mut Node,
    len: usize,
    marker: PhantomData<Box<Node>>,
}

impl Node {
    fn new(val: i32) -> Self {
        Node {
            val,
            next: null_mut(),
            prev: null_mut(),
        }
    }

    fn into_element(self) -> i32 {
        self.val
    }
}

impl LinkedList {
    pub fn new() -> Self {
        LinkedList {
            head: null_mut(),
            tail: null_mut(),
            len: 0,
            marker: PhantomData,
        }
    }

    pub fn append(&mut self, val: i32) {
        let mut node = Node::new(val);
        node.prev = self.tail;
        let raw_node = Box::into_raw(Box::new(node));

        if self.tail == null_mut() {
            self.head = raw_node;
        } else {
            unsafe { (*self.tail).next = raw_node; }
        }

        self.tail = raw_node;
        self.len += 1;
    }

    pub fn remove(&mut self, val: i32) {
        let mut curr = self.head;

        while !curr.is_null() {
            unsafe {
                if (*curr).val == val {
                    let prev = (*curr).prev;
                    let next = (*curr).next;

                    if !prev.is_null() {
                        (*prev).next = next;
                    } else {
                        self.head = next;
                    }

                    if !next.is_null() {
                        (*next).prev = prev;
                    } else {
                        self.tail = prev;
                    }

                    drop(Box::from_raw(curr));

                    self.len -= 1;
                    return;
                }
                curr = (*curr).next;
            }
        }
    }

    pub fn is_empty(&self) -> bool {
        self.len == 0
    }

    pub fn len(&self) -> usize {
        self.len
    }

    fn pop_front(&mut self) -> Option<Node> {
        if self.head.is_null() {
            return None
        }

        let node = unsafe { Box::from_raw(self.head) };
        self.head = node.next;

        if self.head.is_null() {
            self.tail = null_mut();
        } else {
            unsafe { (*self.head).prev = null_mut() };
        }

        self.len -= 1;
        Some(*node)
    }

    pub fn print(&self) {

    }
}

impl Drop for LinkedList {
    fn drop(&mut self) {
        while self.pop_front().is_some() {}
    }
}
