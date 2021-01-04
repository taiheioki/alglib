use std::iter::{once, Once};

#[derive(Clone, Debug, Eq, Hash, PartialEq)]
pub struct Singleton<T> {
    element: T,
}

impl<T> Singleton<T> {
    #[inline]
    pub fn new(element: T) -> Self {
        Self { element }
    }
}

impl<T> IntoIterator for Singleton<T> {
    type Item = T;
    type IntoIter = Once<T>;

    #[inline]
    fn into_iter(self) -> Self::IntoIter {
        once(self.element)
    }
}

impl<'a, T> IntoIterator for &'a Singleton<T> {
    type Item = &'a T;
    type IntoIter = Once<&'a T>;

    #[inline]
    fn into_iter(self) -> Self::IntoIter {
        once(&self.element)
    }
}

#[cfg(test)]
mod tests {
    use crate::OrderedSet;

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
