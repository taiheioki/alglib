---
title: 線形代数
weight: 1
---

# 線形代数

## 概要

環 $R$ 上の $n$ 次元**ベクトル** (vector) とは，$R$ の要素を $n$ 個並べたものである．
また，$R$ 上の $n \\times m$ **行列** (matrix) とは，$R$ の要素を $n \\times m$ の矩形状に並べたものである．
ベクトルや行列には自然な加法およびスカラー倍が定義される（$R$-自由加群を成す）．
加えて，行列には加法と両立する乗法が定義される（[行列積](matrix-multiplication)を参照）．

{{< hint info >}}
ここでいうベクトルは厳密には数ベクトル (numeric vector) を指す．
{{< /hint >}}

## 関連問題

* [行列積](matrix-multiplication) (matrix multiplication)
* [行列式](determinant) (determinant)

## ソースコード

以下の実装は

{{< code file="linalg/matrix.hpp" id="linalg" >}}
