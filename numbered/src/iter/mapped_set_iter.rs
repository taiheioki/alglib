use std::iter::FusedIterator;

use crate::iter::IntRangeIter;

/// An auxiliary iterator used in [`MappedSet`](crate::MappedSet).
#[derive(Clone, Copy, Debug, Eq, PartialEq)]
pub struct MappedSetIter<B> {
    range_iter: IntRangeIter<usize>,
    backward: B,
}

impl<D, B> MappedSetIter<B>
where
    B: Fn(usize) -> Option<D>,
{
    /// Creates a new [`MappedSetIter`]. The returned iterator is equivalent to `IntRangeIter::new(0, len).map(|i| backward(i).unwrap())`.
    ///
    /// # Requirements
    /// `backward(n)` must be non-none for all `n < len`.
    #[inline]
    pub fn new(len: usize, backward: B) -> Self {
        MappedSetIter {
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

impl<D, B> Iterator for MappedSetIter<B>
where
    B: Fn(usize) -> Option<D>,
{
    type Item = D;

    #[inline]
    fn next(&mut self) -> Option<D> {
        let i = self.range_iter.next();
        self.apply(i)
    }

    #[inline]
    fn size_hint(&self) -> (usize, Option<usize>) {
        self.range_iter.size_hint()
    }

    #[inline]
    fn nth(&mut self, n: usize) -> Option<D> {
        let i = self.range_iter.nth(n);
        self.apply(i)
    }

    #[inline]
    fn last(mut self) -> Option<D> {
        self.next_back()
    }
}

impl<D, B> DoubleEndedIterator for MappedSetIter<B>
where
    B: Fn(usize) -> Option<D>,
{
    #[inline]
    fn next_back(&mut self) -> Option<D> {
        let i = self.range_iter.next_back();
        self.apply(i)
    }

    #[inline]
    fn nth_back(&mut self, n: usize) -> Option<D> {
        let i = self.range_iter.nth_back(n);
        self.apply(i)
    }
}

impl<D, B> ExactSizeIterator for MappedSetIter<B>
where
    B: Fn(usize) -> Option<D>,
{
    #[inline]
    fn len(&self) -> usize {
        self.range_iter.len()
    }
}

impl<T, B> FusedIterator for MappedSetIter<B> where B: Fn(usize) -> Option<T> {}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn grid_2d() {
        let backward = |i| Some(i).filter(|&i| i < 9).map(|i| (i / 3, i % 3));
        let mut iter = MappedSetIter::new(9, backward);
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
        let mut iter = MappedSetIter::new(100, backward);
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
