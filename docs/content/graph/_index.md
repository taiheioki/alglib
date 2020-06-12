---
title: グラフ
bookFlatSection: true
weight: 2
---

# グラフ
## 概要
**グラフ** (graph) とは，頂点 (vertex) 集合 $V$ と各頂点間の接続を表す辺 (edge) 集合 $E$ によって構成される構造 $G = (V, E)$ である．

* 辺に向きがついていない**無向グラフ** (undirected graph)：$u,v \\in V$ を接続する辺 $e \\in E$ は（順序のついていない）二元集合 $e = \\{u, v\\}$ として表現される．
  $u$, $v$ を $e$ の**端点** (end/endpoint) とよぶ．
* 辺に向きがついている**有向グラフ** (directed graph)：$u$ から出て $v$ に入る辺 $e \\in E$ は順序対 $e = (u, v)$ として表される．
  $u$, $v$ をそれぞれ $e$ の**始点** (tail)，**終点** (head) とよぶ．

いずれの場合も $G$ が並行辺 (parallel edges) や自己ループ (self loop) をもつ場合は注意が必要である．
頂点や辺はそれぞれ節点 (node)，枝 (branch) ともよばれる．グラフが有向の場合，辺は特に有向辺 (directed edge) やアーク (arc) ともいう．

## 関連問題
* [路](path) (path)
  * [単一始点最短路](path/single-source) (single source shortest path)
  * 全点対間最短路 (all-pairs shortest paths)
* [連結性](connectivity) (connectivity)
  * [トポロジカルソート](topological-sort) (topological sort)
  * [強連結成分分解](scc) (strongly connected component decomposition)
  * [Euler 向き付け](euler-orientation) (Euler orientation)

## データ構造
グラフの表現方法は

## ソースコード
{{< code file="graph/graph.hpp" id="graph" >}}
