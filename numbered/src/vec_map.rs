use std::ops::{Index, IndexMut};

use crate::{Map, Set};

/// An ordered map implementation represented as [`Vec`].
#[derive(Clone, Debug, Eq, PartialEq)]
pub struct VecMap<D, T> {
    domain: D,
    image: Vec<T>,
}

impl<D: Set, T> VecMap<D, T> {
    /// Creates a new [`VecMap`].
    ///
    /// # Panics
    /// Panics if `domain.len() != image.len()`.
    #[inline]
    pub fn new(domain: D, image: Vec<T>) -> Self {
        assert!(domain.len() == image.len());
        Self { domain, image }
    }

    /// Returns a mutable reference to the image of a given element, or `None` if the domain does not contain it.
    #[inline]
    pub fn get_mut(&mut self, element: D::Element) -> Option<&mut T> {
        self.image.get_mut(self.domain.index_of(element)?)
    }

    /// Returns a mutable reference to the image of the `n`th element in the domain, or `None` if the domain does not contain it.
    #[inline]
    pub fn get_mut_nth(&mut self, n: usize) -> Option<&mut T> {
        self.image.get_mut(n)
    }
}

impl<D: Set, T> VecMap<D, T>
where
    T: Clone,
{
    /// Fills the image elements with clones of `value`.
    #[inline]
    pub fn fill(&mut self, value: T) {
        for i in 0..self.image.len() {
            self.image[i].clone_from(&value);
        }
    }
}

impl<D: Set, T> Index<D::Element> for VecMap<D, T> {
    type Output = T;

    #[inline]
    fn index(&self, index: D::Element) -> &T {
        self.image.index(self.domain.index_of(index).unwrap())
    }
}

impl<D: Set, T> IndexMut<D::Element> for VecMap<D, T> {
    #[inline]
    fn index_mut(&mut self, index: D::Element) -> &mut T {
        self.image.index_mut(self.domain.index_of(index).unwrap())
    }
}

impl<D: Set, T> Map for VecMap<D, T>
where
    D: Clone,
    T: Clone,
{
    type Domain = D;
    type Input = D::Element;
    type Output = T;

    #[inline]
    fn domain(&self) -> D {
        self.domain.clone()
    }

    #[inline]
    fn get_index(&self, index: usize) -> Option<T> {
        self.image.get(index).cloned()
    }
}

#[cfg(test)]
mod tests {
    use crate::IntRange;

    use super::*;

    #[test]
    fn test1() {
        let domain = IntRange::new(5);
        let output = domain.iter().map(|x| 2 * x).collect();
        let mut map = VecMap::new(domain, output);
        assert_eq!(map[0], 0);
        assert_eq!(map.get(10), None);
        map[0] = 3;
        assert_eq!(map[0], 3);
    }

    #[test]
    fn test2() {
        let vec = vec![0, 2, 4, 6, 8];
        let mut map = VecMap::new(&vec, vec!['a', 'b', 'c', 'd', 'e']);
        assert_eq!(map[&4], 'c');
        assert_eq!(map.get(&6), Some('d'));
        assert_eq!(map.get_index(6), None);
        map[&8] = 'f';
        assert_eq!(map[&8], 'f');
    }
}
