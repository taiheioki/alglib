---
title: 行列積
bookCollapseSection: true
weight: 1
---

# 行列積

## 問題設定
$A = (A\_{i,k})$ と $B = (B\_{k,j})$ をそれぞれ環 $R$ 上の $n \\times p, p \\times m$ 行列としたとき，$A$ と $B$ の**行列積** (matrix multiplication) $C = AB$ は $R$ 上の $n \\times m$ 行列であり，その $(i,j)$ 成分は
$$
    C\_{i,j} := \\sum\_{k=1}^p A\_{i,k} B\_{k,j}
$$
と定義される．

## アルゴリズム
計算量は $R$ 上の演算回数 (arithmetic complexity) で評価．

| アルゴリズム | 計算量 | 備考 |
| ---------- | ----- | --- |
| [素朴行列乗算](naive) | $\\order(nmp)$ | 実用的には最速 |
