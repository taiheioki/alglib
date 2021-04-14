use alglib_set::Set;

pub trait Graph: Copy {
    type Vertex;
    type Vertices: Set<Element = Self::Vertex>;

    type Edge;
    type Edges: Set<Element = Self::Edge>;

    fn vertices(self) -> Self::Vertices;

    #[inline]
    fn num_vertices(self) -> usize {
        self.vertices().len()
    }

    fn edges(self) -> Self::Edges;

    #[inline]
    fn num_edges(self) -> usize {
        self.edges().len()
    }

    fn ends(self, edge: Self::Edge) -> [Self::Vertex; 2];
}

pub trait UnGraph: Graph {}

pub trait DiGraph: Graph {
    fn tail(self, edge: Self::Edge) -> Self::Vertex;
    fn head(self, edge: Self::Edge) -> Self::Vertex;
}

pub trait InEdges: DiGraph {
    type InEdges: Set<Element = (Self::Edge, Self::Vertex)>;

    fn in_edges(self, vertex: Self::Vertex) -> Self::InEdges;

    #[inline]
    fn in_degree(self, vertex: Self::Vertex) -> usize {
        self.in_edges(vertex).len()
    }
}

pub trait OutEdges: DiGraph {
    type OutEdges: Set<Element = (Self::Edge, Self::Vertex)>;

    fn out_edges(self, vertex: Self::Vertex) -> Self::OutEdges;

    #[inline]
    fn out_degree(self, vertex: Self::Vertex) -> usize {
        self.out_edges(vertex).len()
    }
}
