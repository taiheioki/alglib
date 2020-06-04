---
title: 線形代数
type: docs
weight: 1
---

# 線形代数

## 概要
環 $R$ 上の $n$ 次元**ベクトル** (vector) とは，$R$ の要素を $n$ 個並べたものである．$R$ 上の $n$ 次元ベクトル全体 $R^n$ は自然に定義される加法とスカラー倍によって $R$ 上の自由加群を成す．$R$ が体のとき，これは特に**ベクトル空間** (vector space) とよばれる．

また，$R$ 上の $n \\times m$ **行列** (matrix) とは，$R$ の要素を $n \\times m$ の矩形状に並べたものである．$R$ 上の $n \\times m$ 行列全体 $R^{n \\times m}$ も同様に自然に定義される加法とスカラー倍によって $R$ 上の自由加群を成す．加えて，行列には加法と両立する乗法が定義される（[行列積](matrix-multiplication)を参照）．

{{< hint info >}}
ここでいうベクトルは厳密には数ベクトル (numeric vector) を指す．
{{< /hint >}}

## 関連問題
* [行列積](matrix-multiplication) (matrix multiplication)
* [行列式](determinant) (determinant)

## ソースコード
以下の実装は

{{< code file="linalg/matrix.hpp" start=9 end=21 >}}
