use std::cmp::Ordering;
use std::collections::HashMap;

struct TimeMap {
    inner: HashMap<String, Vec<Item<String>>>
}

struct Item<V> {
    value: V,
    timebase: i32
}

impl <V> Item<V> {
    pub fn new(value: V, timebase: i32) -> Item<V> {
        Self {
            value,
            timebase
        }
    }
}

impl<V> Eq for Item<V> {}

impl<V> PartialEq<Self> for Item<V> {
    fn eq(&self, other: &Self) -> bool {
        self.timebase.eq(&self.timebase)
    }
}

impl<V> PartialOrd<Self> for Item<V> {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        self.timebase.partial_cmp(&other.timebase)
    }
}

impl <V> Ord for Item<V> {
    fn cmp(&self, other: &Self) -> Ordering {
        self.timebase.cmp(&other.timebase)
    }
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl TimeMap {

    fn new() -> Self {
        Self {
            inner: HashMap::new()
        }
    }

    fn set(&mut self, key: String, value: String, timestamp: i32) {
        let vec = self.inner.entry(key).or_default();
        let item = Item::new(value, timestamp);
        let pos = vec.binary_search(&item).unwrap_or_else(|pos| pos);
        vec.insert(pos, item);
    }

    fn get(&self, key: String, timestamp: i32) -> String {
        let vec = self.inner.get(&key);
        if vec.is_none() {
            return String::default();
        }

        let vec = vec.unwrap();
        let item = Item::new(String::default(), timestamp);
        let pos = vec.binary_search(&item).unwrap_or_else(|pos| pos);

        match vec.get(pos) {
            None => {
                match vec.get(pos - 1) {
                    None => {String::default()}
                    Some(item) => {item.value.clone()}
                }
            }
            Some(item) => {
                if item.timebase > timestamp {
                    return match vec.get(pos - 1) {
                        None => {String::default()}
                        Some(item) => {item.value.clone()}
                    };
                }

                item.value.clone()
            }
        }
    }
}