/// A trait for a bijection between the domain of `n` elements and `{0,...,n-1}`.
pub trait Numbering {
    /// The type of the domain elements.
    type Domain: Eq;

    /// The type of an iterator over the domain.
    type DomainIter: ExactSizeIterator<Item = Self::Domain>;

    /// Returns the numbering of the specified element, or `None` if the domain does not contain it.
    fn get(&self, x: Self::Domain) -> Option<usize>;

    /// Returns an iterator that enumerates the domain elements in the ascending order of numbering.
    fn domain(&self) -> Self::DomainIter;

    /// Returns the cardinality of the domain.
    #[inline]
    fn len(&self) -> usize {
        self.domain().len()
    }

    /// Returns `true` if the domain contains no elements.
    #[inline]
    fn is_empty(&self) -> bool {
        self.domain().len() == 0
    }

    /// Returns `true` if the domain contains the specified element.
    #[inline]
    fn contains(&self, x: Self::Domain) -> bool {
        self.get(x).is_some()
    }
}
