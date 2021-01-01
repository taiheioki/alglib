use crate::Numbering;
use std::option::IntoIter;

impl Numbering for () {
    type Domain = ();
    type DomainIter = IntoIter<()>;

    #[inline]
    fn get(&self, _: ()) -> Option<usize> {
        Some(0)
    }

    #[inline]
    fn domain(&self) -> Self::DomainIter {
        Some(()).into_iter()
    }

    #[inline]
    fn len(&self) -> usize {
        1
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
        let num = ();
        assert_eq!(num.get(()), Some(0));
        assert_eq!(num.domain().collect::<Vec<_>>(), vec![()]);
        assert_eq!(num.len(), 1);
        assert_eq!(num.contains(()), true);
    }
}
