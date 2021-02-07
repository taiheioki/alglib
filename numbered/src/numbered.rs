use std::slice::Iter;

/// A trait for a finite set indexed from `0` to `N-1`, where `N` is the cardinality of the set.
pub trait Numbered {
    /// The type of the set elements.
    type Element: Eq;

    /// The type of an iterator that enumerates the set elements in ascending order of their indices.
    type Iterator: ExactSizeIterator<Item = Self::Element>;

    /// Returns an iterator that enumerates the set elements in ascending order of their indices.
    fn iter(&self) -> Self::Iterator;

    /// Returns the `n`th element of the iterator.
    #[inline]
    fn nth(&self, n: usize) -> Option<Self::Element> {
        self.iter().nth(n)
    }

    /// Returns the index of the specified element, or `None` if the set does not contain it.
    #[inline]
    fn index_of(&self, x: Self::Element) -> Option<usize> {
        self.iter().position(|y| x == y)
    }

    /// Returns `true` if the set contains the specified element.
    #[inline]
    fn contains(&self, x: Self::Element) -> bool {
        self.index_of(x).is_some()
    }

    /// Returns the cardinality of the set.
    #[inline]
    fn len(&self) -> usize {
        self.iter().len()
    }

    /// Returns `true` if the set is empty.
    #[inline]
    fn is_empty(&self) -> bool {
        self.len() == 0
    }
}

impl<'a, S, T> Numbered for S
where
    S: Clone + IntoIterator<IntoIter = Iter<'a, T>>,
    T: Eq + 'a,
{
    type Element = &'a T;
    type Iterator = Iter<'a, T>;

    #[inline]
    fn iter(&self) -> Self::Iterator {
        self.clone().into_iter()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn array() {
        let vec = &[2, 3, 5, 7, 11];
        assert_eq!(vec.nth(0), Some(&2));
    }

    #[test]
    fn vec_ref() {
        let vec = &vec![2, 3, 5, 7, 11];
        assert_eq!(vec.nth(0), Some(&2));
    }
}
