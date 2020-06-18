---
title: トポロジカルソート
bookCollapseSection: true
weight: 1
---

# トポロジカルソート
## 定義
有向グラフ $G = (V, E)$ の頂点の順序 $v\_1, \\dotsc, v\_n$ が「各 $(v\_i, v\_j) \in E$ に対し $i < j$」という条件を満たすとき，この順序は**位相的** (topological) であるという．
$G$ が位相的順序をもつことと，$G$ が DAG であることは等価である．

また，$v\_1, \\dotsc, v\_n$ が上の条件の代わりに，各 $i < j$ に対し「$v\_j$ が $v\_i$ へ到達可能ならば，$v\_i$ も $v\_j$ へ到達可能である」という条件を満たすとき，この順序は **pre-topological** であるという&nbsp;{{< cite 1 "Schrijver2003" >}}．
任意の有向グラフが pre-topological な順序をもち，特に DAG に対しては，順序が位相的であることと pre-topological であることは同値である．

{{< hint info >}}
「位相的」よりも「トポロジカル」とカタカナ表記することの方が多い気がします．
pre-topological はどう和訳するんでしょう？
「プリトポロジカル」「前トポロジカル」「前順序的」あたりが妥当かと思いますが，文献が見当たりません．
{{< /hint >}}

## 問題設定
与えられた有向グラフ $G = (V, E)$ が DAG であるか判定し，DAG ならば位相的順序を 1 つ求めたい．
可能なら $G$ が DAG でないときも，pre-topological な順序を出力したい．

## アルゴリズム

| アルゴリズム | 計算量 | 備考 |
| ---------- | ----- | --- |
| [Kahn (1962)](kahn1962) | $\\Order(\|V\|+\|E\|)$ | DAG の判定 & 位相的順序の計算のみ |
| [Tarjan (1976)](tarjan1976) | $\\Order(\|V\|+\|E\|)$ | pre-topological な順序も出力できる |

## 参考文献
{{< references >}}
{#Schrijver2003} A. Schrijver. *Combinatorial Optimization*, volume 24 of Algorithms and Combinatorics. Springer, Berlin, 2003.
{{< /references >}}
