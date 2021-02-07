use std::iter::{once, Once};

use crate::Set;

/// A singleton (set of cardinality one).
#[derive(Clone, Debug, Eq, Hash, PartialEq)]
pub struct Singleton<E> {
    element: E,
}

impl<E> Singleton<E> {
    /// Creates a new [`Singleton`].
    #[inline]
    pub fn new(element: E) -> Self {
        Self { element }
    }
}

impl<E> IntoIterator for Singleton<E> {
    type Item = E;
    type IntoIter = Once<E>;

    #[inline]
    fn into_iter(self) -> Self::IntoIter {
        once(self.element)
    }
}

impl<E> Set for Singleton<E>
where
    E: Clone + Eq,
{
    type Element = E;
    type Iterator = Once<E>;

    #[inline]
    fn iter(&self) -> Self::Iterator {
        once(self.element.clone())
    }
}

impl<'a, E> IntoIterator for &'a Singleton<E> {
    type Item = &'a E;
    type IntoIter = Once<&'a E>;

    #[inline]
    fn into_iter(self) -> Self::IntoIter {
        once(&self.element)
    }
}

impl<'a, E> Set for &'a Singleton<E>
where
    E: Eq,
{
    type Element = &'a E;
    type Iterator = Once<&'a E>;

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

    fn check_first<S: Set>(set: &S, x: S::Element) {
        assert_eq!(set.index_of(x), Some(0));
    }

    #[test]
    fn singleton_ref() {
        let singleton = Singleton::new(1usize);
        check_first(&singleton, 1usize);

        let singleton_ref = &singleton;
        check_first(&singleton_ref, &1usize);
    }
}
