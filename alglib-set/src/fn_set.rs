use crate::{iter::FnSetIter, Set};

/// The ordered set represented by a forward lookup map (index -> element) and the reverse lookup map (element -> index).
#[derive(Clone, Copy, Debug, Eq, PartialEq)]
pub struct FnSet<F, R> {
    len: usize,
    forward_lookup: F,
    reverse_lookup: R,
}

impl<E, F, R> FnSet<F, R>
where
    E: Eq,
    F: Fn(usize) -> Option<E>,
    R: Fn(E) -> Option<usize>,
{
    /// Creates a new [`FnSet`] with forward and reverse lookup maps.
    /// The cardinality of the domain is determined as the first `n` such that `forward_lookup(n)` is `None`.
    ///
    /// # Requirements
    /// `forward_lookup` and `reverse_lookup` must be the inverse of each other.
    /// That is, they must satisfy the following properties:
    /// * if `forward_lookup(n).is_some()`, then `reverse_lookup(forward_lookup(n).unwrap()) == Some(n)` for all `n: usize`.
    /// * if `reverse_lookup(x).is_some()`, then `forward_lookup(reverse_lookup(x).unwrap()) == Some(x)` for all `x: E`.
    ///
    /// # Panics
    /// Panics if `forward_lookup(n)` doesn't return `None` for any `n: usize`.
    #[inline]
    pub fn new(forward_lookup: F, reverse_lookup: R) -> Self {
        Self::with_len(
            (0..=usize::MAX)
                .find(|&n| forward_lookup(n).is_none())
                .expect("`forward_lookup(n)` doesn't return `None` for any `n: usize`"),
            forward_lookup,
            reverse_lookup,
        )
    }

    /// Creates a new [`FnSet`] with the cardinality of the domain besides forward and backward maps.
    ///
    /// # Requirements
    /// In addition to the requirements in [`new`](Self::new), the arguments must satisfy the following:
    /// `forward_lookup(n)` is non-none if and only if `n < len` for all `n: usize`.
    #[inline]
    pub fn with_len(len: usize, forward_lookup: F, reverse_lookup: R) -> Self {
        assert!(forward_lookup(len).is_none());
        FnSet {
            len,
            forward_lookup,
            reverse_lookup,
        }
    }
}

impl<E, F, R> IntoIterator for FnSet<F, R>
where
    E: Eq,
    F: Fn(usize) -> Option<E>,
    R: Fn(E) -> Option<usize>,
{
    type Item = E;
    type IntoIter = FnSetIter<F>;

    #[inline]
    fn into_iter(self) -> Self::IntoIter {
        FnSetIter::new(self.len, self.forward_lookup)
    }
}

impl<E, F, R> Set for FnSet<F, R>
where
    E: Copy + Eq,
    F: Fn(usize) -> Option<E> + Copy,
    R: Fn(E) -> Option<usize> + Copy,
{
    type Element = E;
    type Iterator = FnSetIter<F>;

    #[inline]
    fn iter(self) -> Self::Iterator {
        FnSetIter::new(self.len, self.forward_lookup)
    }

    #[inline]
    fn index_of(self, element: E) -> Option<usize> {
        (self.reverse_lookup)(element)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn unit() {
        let forward = |i: usize| Some(i).filter(|&i| i == 0).and(Some(()));
        let reverse = |()| Some(0);
        let set = FnSet::new(forward, reverse);
        assert_eq!(set.len(), 1);
        assert_eq!(set.index_of(()), Some(0));
        assert_eq!(set.iter().collect::<Vec<_>>(), vec![()]);
    }

    #[test]
    fn ref_str() {
        let domain = vec!["zero", "one", "two", "three"];
        let forward = |i: usize| domain.get(i).cloned();
        let reverse = |s: &str| domain.iter().position(|t| *t == s);

        let set = FnSet::new(forward, reverse);
        assert_eq!(set.len(), 4);
        assert_eq!(set.index_of("two"), Some(2));
        assert_eq!(set.index_of("four"), None);
        assert_eq!(set.iter().collect::<Vec<_>>(), domain);
    }

    #[test]
    fn ref_string() {
        let domain: Vec<_> = vec!["zero", "one", "two", "three"]
            .iter()
            .map(|s| s.to_string())
            .collect();
        let forward = |i: usize| domain.get(i);
        let reverse = |s: &String| domain.iter().position(|t| t == s);

        let set = FnSet::new(forward, reverse);
        assert_eq!(set.len(), 4);
        assert_eq!(set.index_of(&domain[1]), Some(1));

        let four = "four".to_string();
        assert_eq!(set.index_of(&four), None);

        assert_eq!(
            set.iter().collect::<Vec<_>>(),
            domain.iter().collect::<Vec<_>>()
        );
    }
}
