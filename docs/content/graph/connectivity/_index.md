---
title: 連結性
weight: 2
---

# 連結性
## 概要
無向[グラフ](..) $G = (V,E)$ の頂点 $u,v \\in V$ に対し，関係 $\\sim$ を「$u \\sim v \\defiff$ $u$ は $v$ へ $G$ 上[到達可能](../path)である」として定めると，$\\sim$ は $V$ 上の同値関係をなす．
この同値関係による同値類（による $G$ の誘導部分グラフ）を $G$ の**連結成分** (connected component) とよぶ．
同様に，$G$ が有向グラフの場合，関係 $\\sim$ を「$u \\sim v \\defiff$ $u, v$ はそれぞれ $v, u$ へ $G$ 上到達可能である」として定めると，$\\sim$ は $V$ 上の同値関係をなし，この同値関係による同値類（による誘導部分グラフ）を $G$ の**強連結成分** (strongly connected component; SCC) とよぶ．

グラフ $G$ 全体が（強）連結成分である場合，$G$ は （**強**）**連結** ((strongly) connected) であるという．

## 関連問題
* [トポロジカルソート](topological-sort) (topological sort)
* [強連結成分分解](scc) (strongly connected component decomposition)
* [Euler 向き付け](euler-orientation) (Euler orientation)
