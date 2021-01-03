use std::iter::{once, Once};

use crate::Numbering;

#[derive(Clone, Debug, Eq, Hash, PartialEq)]
struct UnitNum {}

impl Numbering for UnitNum {
    type Domain = ();
    type DomainIter = Once<()>;

    #[inline]
    fn get(&self, _: ()) -> Option<usize> {
        Some(0)
    }

    #[inline]
    fn domain(&self) -> Self::DomainIter {
        once(())
    }

    #[inline]
    fn contains(&self, _: ()) -> bool {
        true
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test() {
        let num = UnitNum {};
        assert_eq!(num.get(()), Some(0));
        assert_eq!(num.domain().collect::<Vec<_>>(), vec![()]);
        assert_eq!(num.len(), 1);
        assert_eq!(num.contains(()), true);
    }
}
