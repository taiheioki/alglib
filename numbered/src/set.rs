/// A trait for a finite, ordered set indexed from `0` to `N-1`, where `N` is the cardinality of the set.
pub trait Set {
    /// The type of the set elements.
    type Element: Eq;

    /// The type of an iterator that enumerates the set elements in ascending order of their indices.
    type Iterator: ExactSizeIterator<Item = Self::Element>;

    /// Returns an iterator that enumerates the set elements in ascending order of their indices.
    fn iter(&self) -> Self::Iterator;

    /// Returns the `n`th element of the set, or `None` if out of range.
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

impl<'a, E> Set for &'a [E]
where
    E: Eq + 'a,
{
    type Element = &'a E;
    type Iterator = std::slice::Iter<'a, E>;

    #[inline]
    fn iter(&self) -> Self::Iterator {
        <[_]>::iter(self)
    }
}

impl<'a, E> Set for &'a Vec<E>
where
    E: Eq + 'a,
{
    type Element = &'a E;
    type Iterator = std::slice::Iter<'a, E>;

    #[inline]
    fn iter(&self) -> Self::Iterator {
        <[_]>::iter(self)
    }
}

impl<E> Set for Option<E>
where
    E: Clone + Eq,
{
    type Element = E;
    type Iterator = std::option::IntoIter<E>;

    #[inline]
    fn iter(&self) -> Self::Iterator {
        self.clone().into_iter()
    }
}

impl<'a, E> Set for &'a Option<E>
where
    E: Eq + 'a,
{
    type Element = &'a E;
    type Iterator = std::option::Iter<'a, E>;

    #[inline]
    fn iter(&self) -> Self::Iterator {
        Option::iter(self)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn slice_ref() {
        let set: &[i32] = &[2, 3, 5, 7, 11];
        assert_eq!(set.nth(0), Some(&2));
    }

    #[test]
    fn vec_ref() {
        let set = &vec![2, 3, 5, 7, 11];
        assert_eq!(set.nth(0), Some(&2));
    }

    #[test]
    fn option() {
        let set = Some('a');
        assert_eq!(set.nth(0), Some('a'));
    }

    #[test]
    fn option_ref() {
        let set = &Some('a');
        assert_eq!((&set).nth(0), Some(&'a'));
    }
}
