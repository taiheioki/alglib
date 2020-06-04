---
title: 素朴行列乗算
type: docs
weight: 1
---

# 素朴行列乗算
## 概要
定義に従った素朴な[行列積](../)計算．


## 計算量

$\\mathrm{O}(nmp)$ 回の $R$ 上の演算

## ソースコード
```cpp
template<typename R>
Matrix<R> operator* (const Matrix<R>& A, const Matrix<R>& B)
{
    assert(A.cols() == B.rows());
    Matrix<R> C(A.rows(), B.cols());
    
    for(int i=0; i<A.rows(); ++i){
        for(int k=0; k<A.cols(); ++k){
            for(int j=0; j<B.cols(); ++j){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    return C;
}
```
{{< hint info >}}
ループの順序は $i$ → $j$ → $k$ よりも $i$ → $k$ → $j$ の方が $B$ に対するメモリアクセスが連続するため高速になる．
{{< /hint >}}

## 検証
