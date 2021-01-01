use crate::iter::NumRange;
use crate::Numbering;
use num_traits::ops::checked::{CheckedAdd, CheckedSub};
use num_traits::{One, Zero};
use std::convert::TryInto;

/// The trivial numbering on the nonnegative integers given by the identity function.
#[derive(Clone, Debug, Eq, PartialEq)]
pub struct IdNum<D> {
    len: D,
}

impl<D> IdNum<D>
where
    D: Clone + TryInto<usize>,
{
    /// Creates a new `IdenticalNumbering` on `{0,...,len-1}`.
    ///
    /// # Time Complexity
    /// `O(1)`
    ///
    /// # Panics
    /// Panics if `len` cannot be converted into `usize`.
    #[inline]
    pub fn new(len: D) -> Self {
        len.clone()
            .try_into()
            .ok()
            .expect("The argument `size` cannot be converted into `usize`.");
        IdNum { len }
    }
}

impl<D> Numbering for IdNum<D>
where
    D: CheckedAdd + CheckedSub + Clone + One + Ord + TryInto<usize> + Zero,
    usize: TryInto<D>,
{
    type Domain = D;
    type DomainIter = NumRange<D>;

    /// Returns the numbering of the specified element, or `None` if the domain does not contain it.
    ///
    /// # Time Complexity
    /// `O(1)`
    #[inline]
    fn get(&self, x: D) -> Option<usize> {
        Some(x)
            .filter(|x| self.contains(x.clone()))
            .map(|x| x.try_into().ok().unwrap())
    }

    /// Returns an iterator that enumerates the domain elements in the ascending order of numbering.
    ///
    /// # Time Complexity
    /// `O(1)`
    #[inline]
    fn domain(&self) -> NumRange<D> {
        NumRange::new(D::zero(), self.len.clone())
    }

    /// Returns the cardinality of the domain.
    ///
    /// # Time Complexity
    /// `O(1)`
    #[inline]
    fn len(&self) -> usize {
        self.len.clone().try_into().ok().unwrap()
    }

    /// Returns `true` if the domain contains the specified element.
    ///
    /// # Time Complexity
    /// `O(1)`
    #[inline]
    fn contains(&self, x: D) -> bool {
        D::zero() <= x && x < self.len
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test() {
        let num = IdNum::new(10);
        assert_eq!(num.get(-1), None);
        assert_eq!(num.get(0), Some(0));
        assert_eq!(num.get(3), Some(3));
        assert_eq!(num.get(9), Some(9));
        assert_eq!(num.get(10), None);

        assert_eq!(
            num.domain().collect::<Vec<_>>(),
            (0..10).collect::<Vec<_>>()
        );

        assert_eq!(num.len(), 10);
    }
}
