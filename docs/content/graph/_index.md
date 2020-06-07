---
title: グラフ
bookFlatSection: true
weight: 2
---

# グラフ
## 概要
**グラフ** (graph) とは，（有限の）頂点 (vertex) 集合 $V$ と各頂点間の接続を表す辺 (edge) 集合 $E$ によって構成される構造 $G = (V, E)$ である．グラフ理論では単にグラフというと，辺に向きがついていない**無向グラフ** (undirected graph) を指す．この場合，$u,v \\in V$ を接続する辺 $e \\in E$ は（順序のついていない）二元集合 $e = \\{u, v\\}$ として表現される．一方，辺に向きがついているグラフは**有向グラフ** (directed graph) とよばれ，$u$ から出て $v$ に入る辺 $e \\in E$ は順序対 $e = (u, v)$ として表される．いずれの場合も $G$ が並行辺 (parallel edges) をもつ場合は注意が必要である．

頂点や辺はそれぞれ節点 (node)，枝 (branch) ともよばれる．グラフが有向の場合，辺は特に有向辺 (directed edge) やアーク (arc) ともいう．

## 関連問題
* [路](path) (path)
  * [単一始点最短路](path/single-source) (single source shortest path)
  * 全点対間最短路 (all-pairs shortest paths)

## データ表現
グラフの

## ソースコード
{{< code file="graph/graph.hpp" id="graph" >}}
