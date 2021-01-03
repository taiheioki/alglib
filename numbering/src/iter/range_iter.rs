use std::{convert::TryInto, iter::FusedIterator, ops::Sub};

use num_traits::{
    ops::checked::{CheckedAdd, CheckedSub},
    One,
};

/// An iterator over the half-open range [start, end).
#[derive(Clone, Debug, Eq, PartialEq)]
pub struct RangeIter<T> {
    start: T,
    end: T,
}

impl<T> RangeIter<T>
where
    T: Clone,
{
    /// Returns the left endpoint of the range (inclusive).
    ///
    /// # Time Complexity
    /// `O(1)`
    #[inline]
    pub fn start(&self) -> T {
        self.start.clone()
    }

    /// Returns the right endpoint of the range (exclusive).
    ///
    /// # Time Complexity
    /// `O(1)`
    #[inline]
    pub fn end(&self) -> T {
        self.end.clone()
    }
}

impl<T> RangeIter<T>
where
    T: CheckedSub + TryInto<usize>,
{
    /// Creates a new `NumRange` from `start` (inclusive) to `end` (exclusive).
    ///
    /// # Time Complexity
    /// `O(1)`
    ///
    /// # Panics
    /// Panics if `end - start` cannot be converted into `usize`.
    #[inline]
    pub fn new(start: T, end: T) -> Self {
        end.checked_sub(&start)
            .and_then(|l| l.try_into().ok())
            .expect("The difference `end - start` cannot be converted into `usize`.");
        Self { start, end }
    }
}

impl<T> Iterator for RangeIter<T>
where
    T: CheckedAdd + CheckedSub + Clone + One + Ord + Sub<Output = T> + TryInto<usize>,
    usize: TryInto<T>,
{
    type Item = T;

    /// Advances the iterator and returns the next value.
    ///
    /// # Time Complexity
    /// `O(1)`
    #[inline]
    fn next(&mut self) -> Option<T> {
        if self.start < self.end {
            let result = self.start.clone();
            self.start = result.clone() + T::one();
            Some(result)
        } else {
            None
        }
    }

    /// Returns the exact bounds on the remaining length of the iterator.
    ///
    /// # Time Complexity
    /// `O(1)`
    #[inline]
    fn size_hint(&self) -> (usize, Option<usize>) {
        (self.len(), Some(self.len()))
    }

    /// Returns the `n`th element of the iterator.
    ///
    /// # Time Complexity
    /// `O(1)`
    #[inline]
    fn nth(&mut self, n: usize) -> Option<T> {
        if let Some(s) = n
            .try_into()
            .ok()
            .and_then(|n| self.start.checked_add(&n))
            .filter(|s| *s < self.end)
        {
            self.start = s.clone() + T::one();
            Some(s)
        } else {
            self.start = self.end.clone();
            None
        }
    }

    /// Consumes the iterator, returning the last element.
    ///
    /// # Time Complexity
    /// `O(1)`
    #[inline]
    fn last(mut self) -> Option<T> {
        self.next_back()
    }

    /// Returns the minimum element of an iterator.
    ///
    /// # Time Complexity
    /// `O(1)`
    #[inline]
    fn min(mut self) -> Option<T> {
        self.next()
    }

    /// Returns the maximum element of an iterator.
    ///
    /// # Time Complexity
    /// `O(1)`
    #[inline]
    fn max(mut self) -> Option<T> {
        self.next_back()
    }
}

impl<T> DoubleEndedIterator for RangeIter<T>
where
    T: CheckedAdd + CheckedSub + Clone + One + Ord + Sub<Output = T> + TryInto<usize>,
    usize: TryInto<T>,
{
    /// Removes and returns an element from the end of the iterator.
    ///
    /// # Time Complexity
    /// `O(1)`
    #[inline]
    fn next_back(&mut self) -> Option<T> {
        if self.start < self.end {
            self.end = self.end.clone() - T::one();
            Some(self.end.clone())
        } else {
            None
        }
    }

    /// Returns the `n`th element from the end of the iterator.
    ///
    /// # Time Complexity
    /// `O(1)`
    #[inline]
    fn nth_back(&mut self, n: usize) -> Option<T> {
        if let Some(e) = n
            .try_into()
            .ok()
            .and_then(|n| self.end.checked_sub(&n))
            .filter(|e| self.start < *e)
        {
            self.end = e - T::one();
            Some(self.end.clone())
        } else {
            self.end = self.start.clone();
            None
        }
    }
}

impl<T> ExactSizeIterator for RangeIter<T>
where
    T: CheckedAdd + CheckedSub + Clone + One + Ord + Sub<Output = T> + TryInto<usize>,
    usize: TryInto<T>,
{
    /// Returns the exact length of the iterator.
    ///
    /// # Time Complexity
    /// `O(1)`
    #[inline]
    fn len(&self) -> usize {
        (self.end.clone() - self.start.clone())
            .try_into()
            .ok()
            .unwrap()
    }
}

impl<T> FusedIterator for RangeIter<T>
where
    T: CheckedAdd + CheckedSub + Clone + One + Ord + Sub<Output = T> + TryInto<usize>,
    usize: TryInto<T>,
{
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn next() {
        let mut num = RangeIter::new(0, 0u128);
        assert_eq!(num.next(), None);

        let mut num = RangeIter::new(0, 3i128);
        assert_eq!(num.next(), Some(0));
        assert_eq!(num.next(), Some(1));
        assert_eq!(num.next(), Some(2));
        assert_eq!(num.next(), None);
        assert_eq!(num.next(), None);
    }

    #[test]
    fn nth() {
        let mut num = RangeIter::new(0, 3);
        assert_eq!(num.nth(1), Some(1));
        assert_eq!(num.nth(1), None);

        let mut num = RangeIter::new(0, std::i8::MAX);
        assert_eq!(num.nth((i8::MAX - 1) as usize), Some(i8::MAX - 1));
        assert_eq!(num.next(), None);

        let mut num = RangeIter::new(0, u8::MAX);
        assert_eq!(num.nth(u8::MAX as usize), None);

        let mut num = RangeIter::new(0, i16::MAX);
        assert_eq!(num.nth((i16::MAX as usize) + 1), None);
        assert_eq!(num.next(), None);

        let mut num = RangeIter::new(u16::MAX - 1, u16::MAX);
        assert_eq!(num.nth(100), None);
    }

    #[test]
    fn next_back() {
        let mut num = RangeIter::new(0, 0isize);
        assert_eq!(num.next_back(), None);

        let mut num = RangeIter::new(5u64, 10u64);
        assert_eq!(num.next_back(), Some(9));
        assert_eq!(num.next(), Some(5));
        assert_eq!(num.next_back(), Some(8));
        assert_eq!(num.next(), Some(6));
        assert_eq!(num.next_back(), Some(7));
        assert_eq!(num.next(), None);
        assert_eq!(num.next_back(), None);
    }

    #[test]
    fn nth_back() {
        let mut num = RangeIter::new(2, 10i32);
        assert_eq!(num.nth_back(1), Some(8));
        assert_eq!(num.nth_back(3), Some(4));
        assert_eq!(num.nth_back(1), Some(2));
        assert_eq!(num.nth_back(1), None);
        assert_eq!(num.next(), None);

        let mut num = RangeIter::new(0, 10i8);
        assert_eq!(num.nth_back(usize::MAX), None);
        assert_eq!(num.next(), None);

        let mut num = RangeIter::new(0, 10u8);
        assert_eq!(num.nth_back(20), None);
        assert_eq!(num.next(), None);
    }

    #[test]
    fn len() {
        let mut num = RangeIter::new(10u32, 20u32);
        assert_eq!(num.len(), 10);
        num.next();
        assert_eq!(num.len(), 9);
        num.next_back();
        assert_eq!(num.len(), 8);
        num.nth(100);
        assert_eq!(num.len(), 0);
    }

    #[test]
    #[should_panic]
    fn negative_length() {
        RangeIter::new(10, 5);
    }

    #[test]
    #[should_panic]
    fn exceed_usize_range() {
        RangeIter::new(0, u128::MAX);
    }
}
