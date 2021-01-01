/// A trait for a bijection between the domain of `n` elements and `{0,...,n-1}`.
pub trait Numbering {
    /// The type of the domain elements.
    ///
    /// # Future Plan
    /// After stabilization of [Generic Associated Type](https://github.com/rust-lang/rfcs/blob/master/text/1598-generic_associated_types.md),
    /// we are planning to change `Domain` into `type Domain<'a>: Eq`.
    type Domain: Eq;

    /// The type of an iterator over the domain.
    ///
    /// # Future Plan
    /// After stabilization of [Generic Associated Type](https://github.com/rust-lang/rfcs/blob/master/text/1598-generic_associated_types.md),
    /// we are planning to change `DomainIter` into `type DomainIter<'a>: ExactSizeIterator<Item = Self::Domain<'a>>`.
    type DomainIter: ExactSizeIterator<Item = Self::Domain>;

    /// Returns the numbering of the specified element, or `None` if the domain does not contain it.
    ///
    /// # Future Plan
    /// After stabilization of [Generic Associated Type](https://github.com/rust-lang/rfcs/blob/master/text/1598-generic_associated_types.md),
    /// we are planning to change `get` into `fn get<'a>(&self, x: Self::Domain<'a>) -> Option<usize>`.
    fn get(&self, x: Self::Domain) -> Option<usize>;

    /// Returns an iterator that enumerates the domain elements in the ascending order of numbering.
    ///
    /// # Future Plan
    /// After stabilization of [Generic Associated Type](https://github.com/rust-lang/rfcs/blob/master/text/1598-generic_associated_types.md),
    /// we are planning to change `domain` into `fn domain(&self) -> Self::DomainIter<'_>`.
    fn domain(&self) -> Self::DomainIter;

    /// Returns the cardinality of the domain.
    #[inline]
    fn len(&self) -> usize {
        self.domain().len()
    }

    /// Returns `true` if the domain contains the specified element.
    ///
    /// # Future Plan
    /// After stabilization of [Generic Associated Type](https://github.com/rust-lang/rfcs/blob/master/text/1598-generic_associated_types.md),
    /// we are planning to change `contains` into `fn contains<'a>(&self, x: Self::Domain<'a>) -> bool`.
    #[inline]
    fn contains(&self, x: Self::Domain) -> bool {
        self.get(x).is_some()
    }
}
