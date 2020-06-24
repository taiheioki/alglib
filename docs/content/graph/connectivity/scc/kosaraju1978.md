---
title: Kosaraju (1978)
weight: 2
---

# Kosaraju (1978)
## 概要
{{< link "." >}}を行うアルゴリズム．

最初に前処理として，{{< link "../topological-sort/tarjan1976" >}}により，頂点を {{< link "../topological-sort" "pre-topological" >}} な順序に並び替える．
この順序において先頭の頂点に{{< link "../../path" "到達可能" >}}な頂点集合を $C\_1$ とすると，$C\_1$ は $G$ の強連結成分であって，強連結成分の族上の DAG の{{< link "../topological-sort" "位相的" >}}順序において先頭に来ることができる．
$G$ から $C\_1$ を取り除き，同様の操作を繰り返すが，前述の pre-topological 順序を $V \\setminus C\_1$ に制限した順序は新たな $G$ においても pre-topological であるため，トポロジカルソートを 2 度適用する必要はない．

Data Structures and Algorithms&nbsp;{{< cite 1 "Aho1981" >}}によると R. Kosaraju が 1978 年に提案したアルゴリズムのようだが未出版である．
Sharir&nbsp;{{< cite 2 "Sharir1981" >}} も同様のアルゴリズムを与えている．

## 計算量
$\\Order(\|V\|+\|E\|)$

## ソースコード
* 依存：{{< github "graph/graph.hpp" >}}, {{< github "graph/topological_sort.hpp" >}}

{{< code file="graph/scc.hpp" id="kosaraju1978" >}}

## 検証
[Strongly Connected Components - Library Checker](https://judge.yosupo.jp/problem/scc)

## 参考文献
{{< references >}}
{#Aho1981} A. V. Aho, J. E. Hopcroft, and J. D. Ullman. *Data Structures and Algorithms*. Addison-Wesley, Reading, MA, 1983.
{#Sharir1981} M. Sharir. A strong-connectivity algorithm and its applications in data flow analysis. *Computers & Mathematics with Applications*, 7(1):67--72, 1981.
{{< /references >}}
