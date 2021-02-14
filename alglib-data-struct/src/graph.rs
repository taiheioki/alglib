use alglib_set::Set;

pub trait Edge {
    type Vertex: Eq;

    fn tail(&self) -> Self::Vertex;
    fn head(&self) -> Self::Vertex;
}

pub trait Graph {
    type Vertex;
    type Vertices: Set<Element = Self::Vertex>;

    type Edge: Edge<Vertex = Self::Vertex>;
    type Edges: Set<Element = Self::Edge>;

    fn vertices(&self) -> Self::Vertices;

    #[inline]
    fn num_vertices(&self) -> usize {
        self.vertices().len()
    }

    fn edges(&self) -> Self::Edges;

    #[inline]
    fn num_edges(&self) -> usize {
        self.edges().len()
    }
}
