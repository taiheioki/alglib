---
title: 強連結成分分解
bookCollapseSection: true
weight: 2
---

# 強連結成分分解

## 定義
有向グラフ $G = (V, E)$ の{{< link ".." "強連結成分" >}}の族を $\\mathcal{C} = \\set{C\_1, \\dotsc, C\_k}$ とする．
$\\mathcal{C}$ 上の有向辺集合を
$$
  F \\defeq \\set{(C\_i, C\_j) \mid \\text{$C\_i$ is reachable to $C_j$}}
$$
と定めると，強連結性の定義より，$(\\mathcal{C}, F)$ は DAG となる．

## 問題設定
与えられた有向グラフ $G = (V, E)$ の強連結成分 $C\_1, \\ldots, C\_k$ をすべて求めたい．
特に $C\_1, \\ldots, C\_k$ は上で定義した DAG における{{< link "../topological-sort" "位相的" >}}順序としたい．

## アルゴリズム

| アルゴリズム | 計算量 | 備考 |
| ---------- | ----- | --- |
| {{< link "tarjan1972" >}} | $\\Order(\|V\|+\|E\|)$ | DFS を 1 回行う |
| {{< link "kosaraju1978" >}} | $\\Order(\|V\|+\|E\|)$ | DFS を 2 回行う |
