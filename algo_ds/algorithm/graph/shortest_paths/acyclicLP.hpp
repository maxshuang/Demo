#pragma once
#include <limits>
#include <cmath>
#include "directed_graph/digraph.hpp"
#include "directed_graph/topological.hpp"

// It doesn't assume that the edge weights need to be non-negative.
// The AcyclicLP is rooted in the idea that: for an acyclic graph, we can get its topological sort in O(E+V)
// Then, we can get the SPT following the topological sort because it defines the global order
// Time Complexity: O(E+V), Space Complexity: O(V)

// Variants:
// 1. Single-source longest paths in edge-weighted DAGs.

class AcyclicLP
{
public:
    AcyclicLP(const Digraph &g, int s) : src_(s), edge_to_(g.V()), dist_to_(g.V(), -std::numeric_limits<double>::infinity())
    {
        dist_to_[s] = 0.0;
        Topological tp(g);
        if (!tp.IsDAG())
            return;
        relax_all(g, tp.Order());
    }

    double DistTo(int v) const
    {
        if (HasPathTo(v))
            return dist_to_[v];
        else
            return std::numeric_limits<double>::infinity();
    }

    bool HasPathTo(int v) const { return !std::isinf(-dist_to_[v]); }

    std::vector<Edge> PathTo(int v) const
    {
        std::vector<Edge> res;
        while (v != src_)
        {
            res.push_back(edge_to_[v]);
            v = edge_to_[v].Src();
        }
        return res;
    }

private:
    void relax_all(const Digraph &g, const std::vector<int> &vs)
    {
        int st = 0;
        // skip precedence vertice to src_
        for (; st < (int)vs.size(); ++st)
        {
            if (vs[st] == src_)
                break;
        }
        for (; st < (int)vs.size(); ++st)
        {
            auto pair = g.Adj(vs[st]);
            std::for_each(pair.first, pair.second, [&](const Edge &e)
                          { relax(e); });
        }
    }

    void relax(const Edge &e)
    {
        double dist = dist_to_[e.Src()] + e.Weight();
        if (dist_to_[e.Dest()] < dist)
        {
            dist_to_[e.Dest()] = dist;
            edge_to_[e.Dest()] = e;
        }
    }

private:
    int src_;
    std::vector<Edge> edge_to_;
    std::vector<double> dist_to_;
};