---
title: 路
weight: 1
---

# 路
## 概要
無向[グラフ](..) $G = (V,E)$ の $s$&ndash;$t$ **路** ($s$&ndash;$t$ path) $P$ とは，相異なる頂点 $s = v\_0, v\_1, \\dotsc, v\_k = t \\in V$ と相異なる辺 $e\_1, \\dotsc, e\_k \\in E$ の交互列 $v\_0, e\_1, v\_1, e\_1, v\_2, \\dotsc, e\_k, v\_k$ であり，各 $i = 1, \\dotsc, k$ に対し，$e\_i = \\set{v\_{i-1}, v_i}$ を満たすもののことをいう．
有向[グラフ](..) $G = (V,E)$ の $s$&ndash;$t$ **有向路** ($s$&ndash;$t$ directed path) $P$ も，上記の条件を $e\_i = \\prn{v\_{i-1}, v_i}$ に変えることで同様に定義される．
（有向）路は，頂点もしくは辺の部分集合であったり，あるいは $G$ の部分グラフとみなされることも多い．

上の定義における $k$ を $P$ の**長さ** (length) という．
$G$ の各辺が辺長 $\\funcdoms{\\ell}{E}{\\setR}$ を持つ場合，$P$ の長さ $\\ell(P)$ は $P$ が含む辺の長さの和として定義される．

## 関連問題
* [単一始点最短路](single-source) (single source shortest path)
* 全点対間最短路 (all-pairs shortest paths)
