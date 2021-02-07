use std::ops::Index;

use crate::{IntRange, Set};

pub trait Map: Index<<Self as Map>::Input, Output = <Self as Map>::Output> {
    type Input: Eq + std::fmt::Debug;
    type Output;
    type Domain: Set<Element = Self::Input>;

    fn domain(&self) -> Self::Domain;

    fn get_by_index(&self, index: usize) -> Option<&<Self as Map>::Output>;

    #[inline]
    fn get(&self, x: Self::Input) -> Option<&<Self as Map>::Output> {
        self.get_by_index(self.domain().index_of(x)?)
    }
}

impl<T> Map for [T] {
    type Input = usize;
    type Output = T;
    type Domain = IntRange;

    #[inline]
    fn domain(&self) -> IntRange {
        IntRange::new(self.len())
    }

    #[inline]
    fn get_by_index(&self, index: usize) -> Option<&T> {
        <[_]>::get(self, index)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn array() {
        let map = [2, 3, 5, 7, 11];
        assert_eq!(map.get(2), Some(&5));
        assert_eq!(map.get_by_index(10), None);
        assert_eq!(map.domain().iter().collect::<Vec<_>>(), vec![0, 1, 2, 3, 4])
    }

    #[test]
    fn vec() {
        let map = vec![2, 3, 5, 7, 11];
        assert_eq!(map.get(2), Some(&5));
        assert_eq!(map.get_by_index(10), None);
        assert_eq!(map.domain().iter().collect::<Vec<_>>(), vec![0, 1, 2, 3, 4])
    }
}
