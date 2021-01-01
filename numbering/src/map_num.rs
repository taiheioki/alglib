use crate::iter::MapNumIter;
use crate::Numbering;

/// The numbering designated by the forward map (domain -> number) and the backward map (number -> domain).
#[derive(Clone, Debug, Eq, PartialEq)]
pub struct MapNum<F, B> {
    len: usize,
    forward: F,
    backward: B,
}

impl<D, F, B> MapNum<F, B>
where
    F: Fn(D) -> Option<usize>,
    B: Fn(usize) -> Option<D>,
{
    /// Creates a new `MapNum` with forward and backward maps.
    /// The cardinality of the domain is determined as the first `n` such that `backward(n)` is `None`.
    ///
    /// # Requirements
    /// `forward` and `backward` must be the inverse of each other.
    /// That is, they must satisfy the following properties:
    /// * if `forward(x).is_some()`, then `backward(forward(x).unwrap()) == Some(x)` for all `x: D`.
    /// * if `backward(n).is_some()`, then `forward(backward(n).unwrap()) == Some(n)` for all `n: usize`.
    ///
    /// # Time Complexity
    /// `O(n)`, where `n` is the cardinality of the domain.
    ///
    /// # Panics
    /// Panics if `forward(n)` doesn't return `None` for any `n: usize`.
    #[inline]
    pub fn new(forward: F, backward: B) -> Self {
        let len = (0..=usize::MAX)
            .find(|&n| {
                if let Some(x) = backward(n) {
                    debug_assert!(
                        forward(x) == Some(n),
                        "`forward` isn't the inverse of `backward`."
                    );
                    false
                } else {
                    true
                }
            })
            .expect("`forward(n)` doesn't returns `None` for any `n: usize`");

        Self::with_len(len, forward, backward)
    }

    /// Creates a new `MapNum` with the cardinality of the domain besides forward and backward maps.
    ///
    /// # Requirements
    /// In addition to the requirements in [new](struct.MapNum.html#method.new), the arguments must satisfy the following:
    /// `backward(n)` is non-none if and only if `n < len` for all `n: usize`.
    ///
    /// # Time Complexity
    /// `O(1)`
    #[inline]
    pub fn with_len(len: usize, forward: F, backward: B) -> Self {
        debug_assert!(backward(len).is_none());
        MapNum {
            len,
            forward,
            backward,
        }
    }
}

impl<D, F, B> Numbering for MapNum<F, B>
where
    D: Eq,
    F: Fn(D) -> Option<usize>,
    B: Fn(usize) -> Option<D> + Clone,
{
    type Domain = D;
    type DomainIter = MapNumIter<B>;

    /// Returns the numbering of the specified element, or `None` if the domain does not contain it.
    ///
    /// # Time Complexity
    /// `O(1)`
    #[inline]
    fn get(&self, x: D) -> Option<usize> {
        (self.forward)(x)
    }

    /// Returns an iterator that enumerates the domain elements in the ascending order of numbering.
    ///
    /// # Time Complexity
    /// `O(1)`
    #[inline]
    fn domain(&self) -> Self::DomainIter {
        Self::DomainIter::new(self.len, self.backward.clone())
    }

    /// Returns the cardinality of the domain.
    ///
    /// # Time Complexity
    /// `O(1)`
    #[inline]
    fn len(&self) -> usize {
        self.len
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn unit() {
        let forward = |()| Some(0);
        let backward = |i: usize| Some(i).filter(|&i| i == 0).and(Some(()));
        let num = MapNum::new(forward, backward);
        assert_eq!(num.len(), 1);
        assert_eq!(num.get(()), Some(0));
        assert_eq!(num.domain().collect::<Vec<_>>(), vec![()]);
    }

    #[test]
    fn ref_str() {
        let domain = vec!["zero", "one", "two", "three"];
        let forward = |s: &str| domain.iter().position(|&t| t == s);
        let backward = |i: usize| domain.get(i).map(|&s| s);

        let num = MapNum::new(forward, backward);
        assert_eq!(num.len(), 4);
        assert_eq!(num.get("two"), Some(2));
        assert_eq!(num.get("four"), None);
        assert_eq!(num.domain().collect::<Vec<_>>(), domain);
    }

    #[test]
    fn ref_string() {
        let domain: Vec<_> = vec!["zero", "one", "two", "three"]
            .iter()
            .map(|s| s.to_string())
            .collect();
        let forward = |s: &String| domain.iter().position(|t| t == s);
        let backward = |i: usize| domain.get(i);

        let num = MapNum::new(forward, backward);
        assert_eq!(num.len(), 4);
        assert_eq!(num.get(&domain[1]), Some(1));

        let four = "four".to_string();
        assert_eq!(num.get(&four), None);

        assert_eq!(
            num.domain().collect::<Vec<_>>(),
            domain.iter().collect::<Vec<_>>()
        );
    }

    #[test]
    fn string() {
        let domain: Vec<_> = vec!["zero", "one", "two", "three"]
            .iter()
            .map(|s| s.to_string())
            .collect();
        let forward = |s: String| domain.iter().position(|t| *t == s);
        let backward = |i: usize| domain.get(i).map(|s| (*s).clone());

        let num = MapNum::new(forward, backward);
        assert_eq!(num.len(), 4);
        assert_eq!(num.get(domain[1].clone()), Some(1));
        assert_eq!(num.get("four".to_string()), None);

        assert_eq!(num.domain().map(|s| s.clone()).collect::<Vec<_>>(), domain);
    }
}
