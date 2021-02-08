use crate::{Map, Set};

/// The ordered map represented by a [`Fn`] object (typically closures).
///
/// The image of a domain element `x` with index `n` under the map is determined by `function(n, x)`.
#[derive(Clone, Copy, Debug, Eq, PartialEq)]
pub struct FnMap<D, F> {
    domain: D,
    function: F,
}

impl<D, F> FnMap<D, F> {
    /// Creates a new [`FnMap`] with domain and function.
    #[inline]
    pub fn new(domain: D, function: F) -> Self {
        Self { domain, function }
    }
}

impl<D: Set, F, T> Map for FnMap<D, F>
where
    D: Clone,
    D::Element: Clone,
    F: Fn(usize, D::Element) -> T,
{
    type Domain = D;
    type Input = D::Element;
    type Output = T;

    #[inline]
    fn domain(&self) -> D {
        self.domain.clone()
    }

    #[inline]
    fn get(&self, x: D::Element) -> Option<T> {
        Some((self.function)(self.domain.index_of(x.clone())?, x))
    }

    #[inline]
    fn get_nth(&self, n: usize) -> Option<T> {
        Some((self.function)(n, self.domain.nth(n)?))
    }
}

#[cfg(test)]
mod test {
    use crate::FnSet;

    use super::*;

    #[test]
    fn test() {
        let map = FnMap::new(
            FnSet::new(
                |n| if n < 81 { Some((n / 9, n % 9)) } else { None },
                |(i, j)| {
                    if i < 9 && j < 9 {
                        Some(i * 9 + j)
                    } else {
                        None
                    }
                },
            ),
            |_, (i, j)| i * i + j * j,
        );

        assert_eq!(map.get((5, 5)), Some(50));
        assert_eq!(map.get((1, 10)), None);
        assert_eq!(map.get_nth(80), Some(128));
        assert_eq!(map.get_nth(81), None);
    }
}
