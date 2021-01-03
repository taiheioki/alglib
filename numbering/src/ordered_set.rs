/// A trait for a finite set indexed from `0` to `len-1`, where `len` is the cardinality of the set.
pub trait OrderedSet {
    /// The type of the set elements.
    type Element: Eq;

    /// The type of an iterator that enumerates the set elements in ascending order of their indices.
    type Iter: ExactSizeIterator<Item = Self::Element>;

    /// Returns an iterator that enumerates the set elements in ascending order of their indices.
    fn iter(&self) -> Self::Iter;

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
