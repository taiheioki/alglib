use std::convert::TryInto;

use num_traits::{
    ops::checked::{CheckedAdd, CheckedSub},
    One, Zero,
};

use crate::{iter::IntRangeIter, Set};

/// The set of integers between `0` and `len-1`.
#[derive(Clone, Debug, Eq, Hash, PartialEq)]
pub struct IntRange<Idx = usize> {
    len: Idx,
}

impl<Idx> IntRange<Idx>
where
    Idx: Clone + TryInto<usize>,
{
    /// Creates a new [`IntRange`] on `{0,...,len-1}`.
    ///
    /// # Panics
    /// Panics if `len` cannot be converted into `usize`.
    #[inline]
    pub fn new(len: Idx) -> Self {
        assert!(
            len.clone().try_into().is_ok(),
            "The argument `len` cannot be converted into `usize`."
        );
        IntRange { len }
    }
}

impl<Idx> Set for IntRange<Idx>
where
    Idx: CheckedAdd + CheckedSub + Clone + One + Ord + TryInto<usize> + Zero,
    usize: TryInto<Idx>,
{
    type Element = Idx;
    type Iterator = IntRangeIter<Idx>;

    #[inline]
    fn iter(&self) -> IntRangeIter<Idx> {
        IntRangeIter::new(Idx::zero(), self.len.clone())
    }

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
        let range = IntRange::new(10);
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
