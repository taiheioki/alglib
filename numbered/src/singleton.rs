use std::iter::{once, Once};

use crate::Numbered;

/// A singleton (set of cardinality one).
#[derive(Clone, Debug, Eq, Hash, PartialEq)]
pub struct Singleton<T> {
    element: T,
}

impl<T> Singleton<T> {
    /// Creates a new [`Singleton`].
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

impl<T> Numbered for Singleton<T>
where
    T: Clone + Eq,
{
    type Element = T;
    type Iterator = Once<T>;

    #[inline]
    fn iter(&self) -> Self::Iterator {
        once(self.element.clone())
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

impl<'a, T: Eq> Numbered for &'a Singleton<T> {
    type Element = &'a T;
    type Iterator = Once<&'a T>;

    #[inline]
    fn iter(&self) -> Self::Iterator {
        once(&self.element)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn singleton() {
        let singleton = Singleton::new('a');
        assert_eq!(singleton.index_of('a'), Some(0));
        assert_eq!(singleton.index_of('b'), None);
        assert_eq!(singleton.nth(0), Some('a'));
        assert_eq!(singleton.nth(1), None);
        assert_eq!(singleton.iter().collect::<Vec<_>>(), vec!['a']);
        assert_eq!(singleton.len(), 1);
        assert_eq!(singleton.contains('a'), true);
    }

    fn check_first<N: Numbered>(numbered: &N, x: <N as Numbered>::Element) {
        assert_eq!(numbered.index_of(x), Some(0));
    }

    #[test]
    fn singleton_ref() {
        let singleton = Singleton::new(1usize);
        check_first(&singleton, 1usize);

        let singleton_ref = &singleton;
        check_first(&singleton_ref, &1usize);
    }
}
