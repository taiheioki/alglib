use std::iter::FusedIterator;

use crate::iter::IntRangeIter;

/// An auxiliary iterator used in [`MapNum`](../struct.MapNum.html).
#[derive(Clone, Debug, Eq, PartialEq)]
pub struct MapNumIter<B> {
    range_iter: IntRangeIter<usize>,
    backward: B,
}

impl<D, B> MapNumIter<B>
where
    B: Fn(usize) -> Option<D>,
{
    /// Creates a new `MapNumIter`. The returned iterator is equivalent to `NumRange::new(0, len).map(|i| backward(i).unwrap())`.
    ///
    /// # Requirements
    /// `backward(n)` must be non-none for all `n < len`.
    #[inline]
    pub fn new(len: usize, backward: B) -> Self {
        MapNumIter {
            range_iter: IntRangeIter::new(0, len),
            backward,
        }
    }

    #[inline]
    fn apply(&self, i: Option<usize>) -> Option<D> {
        i.map(|i| {
            (self.backward)(i).unwrap_or_else(|| {
                panic!(
                    "The `MapNum` object has length {}, but `self.backward({})` returned `None`",
                    self.range_iter.end(),
                    i
                )
            })
        })
    }
}

impl<D, B> Iterator for MapNumIter<B>
where
    B: Fn(usize) -> Option<D>,
{
    type Item = D;

    /// Advances the iterator and returns the next value.
    #[inline]
    fn next(&mut self) -> Option<D> {
        let i = self.range_iter.next();
        self.apply(i)
    }

    /// Returns the exact bounds on the remaining length of the iterator.
    #[inline]
    fn size_hint(&self) -> (usize, Option<usize>) {
        self.range_iter.size_hint()
    }

    /// Returns the `n`th element of the iterator.
    #[inline]
    fn nth(&mut self, n: usize) -> Option<D> {
        let i = self.range_iter.nth(n);
        self.apply(i)
    }

    /// Consumes the iterator, returning the last element.
    #[inline]
    fn last(mut self) -> Option<D> {
        self.next_back()
    }
}

impl<D, B> DoubleEndedIterator for MapNumIter<B>
where
    B: Fn(usize) -> Option<D>,
{
    /// Removes and returns an element from the end of the iterator.
    #[inline]
    fn next_back(&mut self) -> Option<D> {
        let i = self.range_iter.next_back();
        self.apply(i)
    }

    /// Returns the `n`th element from the end of the iterator.
    #[inline]
    fn nth_back(&mut self, n: usize) -> Option<D> {
        let i = self.range_iter.nth_back(n);
        self.apply(i)
    }
}

impl<D, B> ExactSizeIterator for MapNumIter<B>
where
    B: Fn(usize) -> Option<D>,
{
    /// Returns the exact length of the iterator.
    #[inline]
    fn len(&self) -> usize {
        self.range_iter.len()
    }
}

impl<T, B> FusedIterator for MapNumIter<B> where B: Fn(usize) -> Option<T> {}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn grid_2d() {
        let backward = |i| Some(i).filter(|&i| i < 9).map(|i| (i / 3, i % 3));
        let mut iter = MapNumIter::new(9, backward);
        assert_eq!(iter.next(), Some((0, 0)));
        assert_eq!(iter.next(), Some((0, 1)));
        assert_eq!(iter.len(), 7);
        assert_eq!(iter.next(), Some((0, 2)));
        assert_eq!(iter.next(), Some((1, 0)));
        assert_eq!(iter.nth(2), Some((2, 0)));
        assert_eq!(iter.next_back(), Some((2, 2)));
        assert_eq!(iter.last(), Some((2, 1)));
    }

    #[test]
    fn range() {
        let backward = |i| Some(i).filter(|&i| i < 100);
        let mut iter = MapNumIter::new(100, backward);
        let mut range = IntRangeIter::new(0, 100);
        assert_eq!(iter.next(), range.next());
        assert_eq!(iter.len(), range.len());
        assert_eq!(iter.nth(97), range.nth(97));
        assert_eq!(iter.next_back(), range.next_back());
        assert_eq!(iter.len(), range.len());
        assert_eq!(iter.next(), range.next());
        assert_eq!(iter.next(), range.next());
    }
}
