---
title: 幅優先探索
weight: 1
---

# 幅優先探索
## 概要
各辺が単位長の無向または有向グラフ $G$ における[単一始点最短路](..)問題を解く．始点 $s$ から到達可能な頂点を近い順にキューに追加していくシンプルなアルゴリズム．

英語では Breadth First Search (BFS) といい，よく BFS と略される．Schrijver ABC {{< cite 3 "Schrijver2003">}} によると初出は Berge {{< cite 1 "Berge1958b" >}}, Moore {{< cite 2 "Moore1959" >}} らしい．

## 計算量
$\\mathrm{O}(\|V\|+\|E\|)$

## ソースコード
`graph/graph.hpp`，`graph/tree.hpp` に依存．

{{< code file="graph/bfs.hpp" id="graph/bfs" >}}

## 検証
[AOJ ALDS1_11_C: Breadth First Search](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_11_C)

## 参考文献
{{< references >}}
{#Berge1958b} C. Berge. *Théorie des graphes et ses applications*, volume 2 of Collection universitaire de mathématiques. Dunod, Paris, 1958.
{#Moore1959} E. F. Moore. The shortest path through a maze. In *Proceeding of the International Symposium on the Theory of Switching (Part II)*, Harvard University Press, Cambridge, pp.&nbsp;285&ndash;292, 1959.
{#Schrijver2003} A. Schrijver. *Combinatorial Optimization*, volume 24 of Algorithms and Combinatorics. Springer, Berlin, 2003.
{{< /references >}}
