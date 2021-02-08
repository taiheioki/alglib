use crate::{IntRange, Set};

/// A trait for an ordered map from [`Set`](crate::Set).
pub trait Map {
    /// The type of the domain of the map.
    type Domain: Set<Element = Self::Input>;

    /// The type of each element in the domain of the map (= `<Self::Domain as Set>::Element`).
    type Input: Eq;

    /// The type of the image of each element in the domain under the map.
    type Output;

    /// Returns the domain of the map.
    fn domain(&self) -> Self::Domain;

    /// Returns the image of the `n`th element in the domain, or `None` if out of range.
    fn get_nth(&self, n: usize) -> Option<<Self as Map>::Output>;

    /// Returns the image of a given element, or `None` if the domain does not contain it.
    #[inline]
    fn get(&self, x: Self::Input) -> Option<<Self as Map>::Output> {
        self.get_nth(self.domain().index_of(x)?)
    }
}

impl<T> Map for [T]
where
    T: Clone,
{
    type Domain = IntRange;
    type Input = usize;
    type Output = T;

    #[inline]
    fn domain(&self) -> IntRange {
        IntRange::new(self.len())
    }

    #[inline]
    fn get_nth(&self, index: usize) -> Option<T> {
        Self::get(self, index).cloned()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn array() {
        let map = [2, 3, 5, 7, 11];
        assert_eq!(map.get(2), Some(&5));
        assert_eq!(map.get_nth(10), None);
        assert_eq!(map.domain().iter().collect::<Vec<_>>(), vec![0, 1, 2, 3, 4])
    }

    #[test]
    fn vec() {
        let map = vec![2, 3, 5, 7, 11];
        assert_eq!(map.get(2), Some(&5));
        assert_eq!(map.get_nth(10), None);
        assert_eq!(map.domain().iter().collect::<Vec<_>>(), vec![0, 1, 2, 3, 4])
    }
}
