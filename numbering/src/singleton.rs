use std::iter::{once, Once};

use crate::OrderedSet;

#[derive(Clone, Debug, Eq, Hash, PartialEq)]
pub struct Singleton<T> {
    element: T,
}

impl<T> Singleton<T> {
    pub fn new(element: T) -> Self {
        Self { element }
    }
}

impl<T> OrderedSet for Singleton<T>
where
    T: Clone + Eq,
{
    type Element = T;
    type Iter = Once<T>;

    #[inline]
    fn iter(&self) -> Self::Iter {
        once(self.element.clone())
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test() {
        let singleton = Singleton::new('a');
        assert_eq!(singleton.index_of('a'), Some(0));
        assert_eq!(singleton.index_of('b'), None);
        assert_eq!(singleton.nth(0), Some('a'));
        assert_eq!(singleton.nth(1), None);
        assert_eq!(singleton.iter().collect::<Vec<_>>(), vec!['a']);
        assert_eq!(singleton.len(), 1);
        assert_eq!(singleton.contains('a'), true);
    }
}
