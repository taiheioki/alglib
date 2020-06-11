#ifndef ALGLIB_TREE_HPP_
#define ALGLIB_TREE_HPP_

#include <algorithm>
#include <vector>

#include "alglib/graph/graph.hpp"

class TreeNode
{
public:
    enum
    {
        Root    = -1,
        Invalid = -2,
    };

    int parent = Invalid;
    std::vector<int> children;
};

class Tree : public std::vector<TreeNode>
{
public:
    int root;

    Tree() = default;

    Tree(const int n, const int r) : std::vector<TreeNode>(n), root(r)
    {
        (*this)[r].parent = TreeNode::Root;
    }

    // Build the path (array of vertices) from the root to v.
    // If there is no such a path, return an empty array.
    std::vector<int> path_to(int v) const
    {
        std::vector<int> P;
        while(v != TreeNode::Root) {
            P.push_back(v);
            v = (*this)[v].parent;
            if(v == TreeNode::Invalid)
                return {};
        }
        std::reverse(P.begin(), P.end());
        return P;
    }
};

#endif
