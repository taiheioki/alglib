---
title: 幅優先探索
type: docs
weight: 1
---

# 幅優先探索
## 概要
各辺が単位長の有向グラフ $G$ における[単一始点最短路](..)問題を解く．始点 $s$ から到達可能な頂点を近い順にキューに追加していくシンプルなアルゴリズム．

英語では Breadth First Search (BFS) といい，よく BFS と略される．Schrijver ABC [*] によると初出は

## 計算量
$\\mathrm{O}(\|V\|+\|E\|)$

## ソースコード
`graph/graph.hpp` に依存．

{{< code file="graph/bfs.hpp" start=13 end=55 >}}

## 検証

## 参考文献
