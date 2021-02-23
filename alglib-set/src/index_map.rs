use std::hash::{BuildHasher, Hash};

use indexmap::{map::Keys, set::Iter, IndexMap, IndexSet};

use crate::{Map, Set};

impl<'a, E, S: BuildHasher> Set for &'a IndexSet<E, S>
where
    E: Eq + Hash,
{
    type Element = &'a E;
    type Iterator = Iter<'a, E>;

    #[inline]
    fn iter(self) -> Self::Iterator {
        IndexSet::iter(self)
    }

    #[inline]
    fn index(self, n: usize) -> Option<&'a E> {
        IndexSet::get_index(self, n)
    }

    #[inline]
    fn index_of(self, x: &E) -> Option<usize> {
        self.get_index_of(x)
    }

    #[inline]
    fn contains(self, x: &E) -> bool {
        IndexSet::contains(self, x)
    }

    #[inline]
    fn len(self) -> usize {
        IndexSet::len(self)
    }

    #[inline]
    fn is_empty(self) -> bool {
        IndexSet::is_empty(self)
    }
}

impl<'a, E, T, S: BuildHasher> Set for &'a IndexMap<E, T, S>
where
    E: Eq + Hash,
{
    type Element = &'a E;
    type Iterator = Keys<'a, E, T>;

    #[inline]
    fn iter(self) -> Self::Iterator {
        self.keys()
    }

    #[inline]
    fn index(self, n: usize) -> Option<&'a E> {
        IndexMap::get_index(self, n).map(|(key, _)| key)
    }

    #[inline]
    fn index_of(self, x: &E) -> Option<usize> {
        self.get_index_of(x)
    }

    #[inline]
    fn contains(self, x: &E) -> bool {
        self.contains_key(x)
    }

    #[inline]
    fn len(self) -> usize {
        IndexMap::len(self)
    }

    #[inline]
    fn is_empty(self) -> bool {
        IndexMap::is_empty(self)
    }
}

impl<'a, E, T, S: BuildHasher> Map for &'a IndexMap<E, T, S>
where
    E: Eq + Hash,
{
    type Domain = Self;
    type Input = &'a E;
    type Output = &'a T;

    #[inline]
    fn domain(&self) -> Self::Domain {
        self
    }

    #[inline]
    fn get_index(&self, n: usize) -> Option<&'a T> {
        IndexMap::get_index(self, n).map(|(_, value)| value)
    }

    #[inline]
    fn get(&self, x: Self::Input) -> Option<&'a T> {
        IndexMap::get(self, x)
    }
}

#[cfg(test)]
mod tests {
    use indexmap::{indexmap, indexset};

    use super::*;

    #[test]
    fn index_set() {
        let set = indexset! {
            "dog",
            "cat",
            "human",
        };

        assert_eq!((&set).len(), 3);
        assert_eq!((&set).index(0), Some(&"dog"));
        assert_eq!((&set).index_of(&"cat"), Some(1));
        assert_eq!((&set).contains(&"human"), true);
    }

    #[test]
    fn index_map() {
        let map = indexmap! {
            "naruse" => "jun",
            "sakagami" => "takumi",
            "nito" => "natsuki",
            "tasaki" => "daiki",
        };

        assert_eq!(Map::get(&&map, &"naruse"), Some(&"jun"));
        assert_eq!(Map::get_index(&&map, 2), Some(&"natsuki"));
        assert_eq!(Map::get_index(&&map, 4), None);
    }
}
