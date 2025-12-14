// Definition for singly-linked list.
#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

impl ListNode {
    #[inline]
    fn new(val: i32) -> Self {
        ListNode { next: None, val }
    }
}

// You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
// Merge all the linked-lists into one sorted linked-list and return it.
//
// 포인터 사용에 대한 고민을 다시 recap 할 수 있어서 한 번 더 풀어보거나 정리필요.
// https://leetcode.com/problems/merge-two-sorted-lists/ 로 recap 함
struct Solution;

impl Solution {
    pub fn merge_k_lists(mut lists: Vec<Option<Box<ListNode>>>) -> Option<Box<ListNode>> {
        if lists.is_empty() {
            return None;
        }

        while lists.len() != 1 {
            let mut merged = Vec::with_capacity((lists.len() + 1) / 2);
            let mut i = 0;
            while i < lists.len() {
                if i + 1 < lists.len() {
                    merged.push(Self::merge(lists[i].take(), lists[i + 1].take()));
                    i += 2;
                } else {
                    merged.push(lists[i].take());
                    i += 1;
                }
            }
            lists = merged;
        }

        lists.pop().flatten()
    }

    pub fn merge(
        mut lv: Option<Box<ListNode>>,
        mut rv: Option<Box<ListNode>>,
    ) -> Option<Box<ListNode>> {
        let mut dummy = Box::new(ListNode::new(0));
        let mut curr = &mut dummy;

        while let (Some(l), Some(r)) = (lv.as_mut(), rv.as_mut()) {
            if l.val < r.val {
                let next = l.next.take();
                curr.next = lv;
                lv = next;
            } else {
                let next = r.next.take();
                curr.next = rv;
                rv = next;
            }
            curr = curr.next.as_mut().unwrap();
        }

        curr.next = lv.or(rv);
        dummy.next
    }
}
