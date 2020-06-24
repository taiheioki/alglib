---
title: Tarjan (1972)
weight: 1
---

# Tarjan (1972)
## 概要
{{< link "." >}}を行うアルゴリズム．

有向グラフ $G$ の各強連結成分 $C$ は $G$ の DFS 森 $F$ における連結部分グラフとなるので，この部分グラフ $F\[C\]$ の根（$F$ の $C$ を含む木の根に最も近い $C$ の頂点）を見つけたい．
各頂点 $v \\in V$ に対し，$\\mathrm{index}(v)$ を $v$ の行きがけ順，$\\mathrm{lowlink}(v)$ を $v$ 自身または「$v$ と同じ強連結成分に属する頂点であって，$v$ の $F$ 上のある子孫から $F$ に含まれない辺をちょうど 1 本使って到達できるもの」の index の最小値と定義すると，$v$ が $v$ を含む強連結成分 $C$ の根であることと $\\mathrm{index}(v) = \\mathrm{lowlink}(v)$ であることが等価となる．

上の観察に基づき，深さ優先探索によって index, lowlink の値を葉から確定させていき，$v$ が根であることが確定した時点で 「$v$ の子孫であり，既に発見された強連結成分に含まれていない頂点」の集合を 1 つの強連結成分として出力する．
出力される強連結成分の順序は位相的順序の逆となる．

## 計算量
$\\Order(\|V\|+\|E\|)$

## ソースコード
* 依存：{{< github "graph/graph.hpp" >}}

「各頂点の子孫であって，既に発見された強連結成分に含まれていない頂点」のリストはスタックを用いることで効率的に管理することができる．

{{< code file="graph/scc.hpp" id="tarjan1972" >}}

## 検証
[Strongly Connected Components - Library Checker](https://judge.yosupo.jp/problem/scc)

## 参考文献
{{< references >}}
{#Tarjan1972} R. E. Tarjan. Depth-first search and linear graph algorithms. *SIAM Journal on Computing*, 1(2):146--160, 1972.
{{< /references >}}
