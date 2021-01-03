use std::convert::TryInto;

use num_traits::{
    ops::checked::{CheckedAdd, CheckedSub},
    One, Zero,
};

use crate::{iter::RangeIter, OrderedSet};

/// The set of integers between `0` and `len-1` ({0,...,len-1}`).
#[derive(Clone, Debug, Eq, Hash, PartialEq)]
pub struct Range<Idx> {
    len: Idx,
}

impl<Idx> Range<Idx>
where
    Idx: Clone + TryInto<usize>,
{
    /// Creates a new `Range` on `{0,...,len-1}`.
    ///
    /// # Time Complexity
    /// `O(1)`
    ///
    /// # Panics
    /// Panics if `len` cannot be converted into `usize`.
    #[inline]
    pub fn new(len: Idx) -> Self {
        len.clone()
            .try_into()
            .ok()
            .expect("The argument `len` cannot be converted into `usize`.");
        Range { len }
    }
}

impl<Idx> OrderedSet for Range<Idx>
where
    Idx: CheckedAdd + CheckedSub + Clone + One + Ord + TryInto<usize> + Zero,
    usize: TryInto<Idx>,
{
    type Element = Idx;
    type Iter = RangeIter<Idx>;

    /// Returns an iterator that enumerates the domain elements in the ascending order of numbering.
    ///
    /// # Time Complexity
    /// `O(1)`
    #[inline]
    fn iter(&self) -> RangeIter<Idx> {
        RangeIter::new(Idx::zero(), self.len.clone())
    }

    /// Returns the numbering of the specified element, or `None` if the domain does not contain it.
    ///
    /// # Time Complexity
    /// `O(1)`
    #[inline]
    fn index_of(&self, x: Idx) -> Option<usize> {
        Some(x)
            .filter(|x| Idx::zero() <= *x && *x < self.len)
            .map(|x| x.try_into().ok().unwrap())
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test() {
        let range = Range::new(10);
        assert_eq!(range.index_of(-1), None);
        assert_eq!(range.index_of(0), Some(0));
        assert_eq!(range.index_of(3), Some(3));
        assert_eq!(range.index_of(9), Some(9));
        assert_eq!(range.index_of(10), None);
        assert_eq!(
            range.iter().collect::<Vec<_>>(),
            (0..10).collect::<Vec<_>>()
        );
        assert_eq!(range.len(), 10);
    }
}
