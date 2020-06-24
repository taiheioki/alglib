---
title: Tarjan (1976)
weight: 2
---

# Tarjan (1976)
## 概要
{{< link "." >}}を行うアルゴリズム．

任意の頂点 $v \\in V$ から深さ優先探索を行い，到達した頂点を帰りがけ順に並べると，それは $v$ から到達可能な頂点集合の pre-topological な順序の逆順となっている．
したがって，$G$ の任意の頂点に到達可能なスーパーノード $r$ を追加し，$r$ から深さ優先探索を行うことで，全体の pre-topological な順序を求めることができる．

探索において逆辺が見つかることと，$G$ が DAG でないことは同値である．

## 計算量
$\\Order(\|V\|+\|E\|)$

## ソースコード
`graph/graph.hpp` に依存．
`graph/scc.hpp` で使用．

スーパーノードは実際には追加せず，各頂点を根とした深さ優先探索を（同じフラグを使いまわしながら）順次行う．
逆辺検出のため，フラグは「未探索」の他に「探索中」と「探索終了」を区別して使用する．

{{< code file="graph/topological_sort.hpp" id="tarjan1976" >}}

## 検証
[AOJ GRL_4_A: Cycle Detection for a Directed Graph](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_A)（位相的順序の検証を追加）

## 参考文献
{{< references >}}
{#Kahn1962} A. B. Kahn. Topological sorting of large networks. *Communications of the ACM*, 5(11):558--562, 1962.
{{< /references >}}
