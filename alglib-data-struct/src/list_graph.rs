use alglib_set::{Set, Singleton, VecMap};

use crate::{Edge, Graph};

pub struct ListGraph<V: Set> {
    vertices: V,
    edges: Vec<PairEdge<V::Element>>,
    inedge_indices: VecMap<V, Vec<usize>>,
}

impl<V: Set> ListGraph<V> {
    #[inline]
    pub fn edgeless(vertices: V) -> Self {
        Self {
            vertices,
            edges: vec![],
            inedge_indices: VecMap::new_by_default(vertices),
        }
    }
}

impl<'a, V: Set> Graph for &'a ListGraph<V>
where
    V: Clone,
    V::Element: Clone,
{
    type Vertex = V::Element;
    type Vertices = V;

    type Edge = PairEdge<Self::Vertex>;
    type Edges = Singleton<Self::Edge>;

    #[inline]
    fn vertices(&self) -> Self::Vertices {
        self.vertices.clone()
    }

    #[inline]
    fn edges(&self) -> Self::Edges {
        todo!()
    }
}

#[derive(Clone, Debug, Hash, Eq, PartialEq)]
pub struct PairEdge<V> {
    tail: V,
    head: V,
}

impl<V> Edge for PairEdge<V>
where
    V: Clone + Eq,
{
    type Vertex = V;

    #[inline]
    fn tail(&self) -> V {
        self.tail.clone()
    }

    #[inline]
    fn head(&self) -> V {
        self.head.clone()
    }
}

#[cfg(test)]
mod tests {
    use alglib_set::IntRange;

    use super::*;

    #[test]
    fn test() {
        let mut graph = ListGraph::edgeless(IntRange::new(5));
        // graph.add_edge(0, 1);
    }
}
