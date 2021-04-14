use alglib_set::{Map, Set, VecMap};

use crate::{DiGraph, Graph};

#[derive(Clone, Copy, Debug, Hash, Eq, PartialEq)]
pub struct Edge<V> {
    id: usize,
    tail: V,
    head: V,
}

pub struct ListGraph<V: Set> {
    edges: Vec<Edge<V::Element>>,
    outgoing_edges: VecMap<V, Vec<usize>>,
}

impl<V: Set> ListGraph<V> {
    #[inline]
    pub fn edgeless(vertices: V) -> Self {
        Self {
            edges: vec![],
            outgoing_edges: VecMap::new_by_default(vertices),
        }
    }
}

impl<'a, V: Set> Graph for &'a ListGraph<V> {
    type Vertex = V::Element;
    type Vertices = V;

    type Edge = &'a Edge<Self::Vertex>;
    type Edges = &'a Vec<Edge<V::Element>>;

    #[inline]
    fn vertices(self) -> Self::Vertices {
        self.outgoing_edges.domain()
    }

    #[inline]
    fn edges(self) -> Self::Edges {
        &self.edges
    }

    #[inline]
    fn ends(self, edge: Self::Edge) -> [Self::Vertex; 2] {
        [edge.tail, edge.head]
    }
}

impl<'a, V: Set> DiGraph for &'a ListGraph<V> {
    #[inline]
    fn tail(self, edge: Self::Edge) -> Self::Vertex {
        edge.tail
    }

    #[inline]
    fn head(self, edge: Self::Edge) -> Self::Vertex {
        edge.head
    }
}

#[derive(Clone, Copy, Debug, Hash, Eq, PartialEq)]
pub struct OutEdges<'a, V: Set> {
    edges: &'a Vec<Edge<V::Element>>,
    outgoing_edges: &'a Vec<usize>,
}

impl<'a, V: Set> Set for OutEdges<'a, V>
where
    V::Element: Copy,
{
    type Element = (Edge<V::Element>, V::Element);
    type Iterator = OutEdgesIterator<'a, V>;

    #[inline]
    fn iter(self) -> Self::Iterator {
        OutEdgesIterator {
            edges: self.edges,
            iterator: self.outgoing_edges.iter(),
        }
    }
}

pub struct OutEdgesIterator<'a, V: Set> {
    edges: &'a Vec<Edge<V::Element>>,
    iterator: std::slice::Iter<'a, usize>,
}

impl<'a, V: Set> Iterator for OutEdgesIterator<'a, V> {
    type Item = (Edge<V::Element>, V::Element);

    #[inline]
    fn next(&mut self) -> Option<Self::Item> {
        self.iterator
            .next()
            .map(|&id| (self.edges[id], self.edges[id].head))
    }

    #[inline]
    fn size_hint(&self) -> (usize, Option<usize>) {
        self.iterator.size_hint()
    }
}

impl<'a, V: Set> ExactSizeIterator for OutEdgesIterator<'a, V> {}

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
