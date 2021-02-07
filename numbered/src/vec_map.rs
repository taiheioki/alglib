use std::ops::{Index, IndexMut};

use crate::{Map, Set};

pub struct VecMap<D, T> {
    domain: D,
    data: Vec<T>,
}

impl<D: Set, T> VecMap<D, T> {
    #[inline]
    pub fn new(domain: D, data: Vec<T>) -> Self {
        assert!(domain.len() == data.len());
        Self { domain, data }
    }
}

impl<D: Set, T> Index<<D as Set>::Element> for VecMap<D, T> {
    type Output = T;

    #[inline]
    fn index(&self, index: D::Element) -> &T {
        self.data.index(self.domain.index_of(index).unwrap())
    }
}

impl<D: Set, T> IndexMut<<D as Set>::Element> for VecMap<D, T> {
    #[inline]
    fn index_mut(&mut self, index: D::Element) -> &mut T {
        self.data.index_mut(self.domain.index_of(index).unwrap())
    }
}

impl<D: Set, T> Map for VecMap<D, T>
where
    D: Clone,
{
    type Domain = D;
    type Input = D::Element;
    type Output = T;

    #[inline]
    fn domain(&self) -> D {
        self.domain.clone()
    }

    #[inline]
    fn get_by_index(&self, index: usize) -> Option<&T> {
        self.data.get(index)
    }
}

#[cfg(test)]
mod tests {
    use crate::IntRange;

    use super::*;

    #[test]
    fn test1() {
        let domain = IntRange::new(5);
        let data = domain.iter().map(|x| 2 * x).collect();
        let mut map = VecMap::new(domain, data);
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
        assert_eq!(map.get(&6), Some(&'d'));
        assert_eq!(map.get_by_index(6), None);
        map[&8] = 'f';
        assert_eq!(map[&8], 'f');
    }
}
