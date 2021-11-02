#ifndef _NETWORK_H__
#define _NETWORK_H__

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <assert.h>
#include <set>
using namespace std;

class enetwork
{
    map<string, map<string, int>> M;
    struct edge
    {
        string a, b;
        int cost;
        bool operator<(const edge &e) const
        {
            return e.cost < this->cost;
        };
    };

public:
    enetwork(){};
    enetwork(map<string, map<string, int>> e) : M(e){};
    int add_node(string node)
    {
        if (M.find(node) == M.end())
        {
            map<string, int> null_node;
            M[node] = null_node;
            return 0;
        }
        else
        {
            cout << "Node name already exists." << endl;
            return 1;
        };
    };
    int add_single_edge(string node_a, string node_b, int cost)
    {
        assert(cost > 0);
        assert(M.find(node_a) != M.end() && M.find(node_b) != M.end());
        M[node_a][node_b] = cost;
        return 0;
    };
    int add_edge(string node_a, string node_b, int cost)
    {
        assert(cost > 0);
        add_single_edge(node_a, node_b, cost);
        add_single_edge(node_b, node_a, cost);
        return 0;
    };
    // int find_edge(string node_a, string node_b)
    // {
    //     assert(M.find(node_a) != M.end() && M[node_a].find(node_b) != M[node_a].end());
    //     return M[node_a][node_b];
    // };
    int print_edges()
    {
        cout << "[GRAPH]" << endl;
        for (auto &v : M)
        {
            cout << "[" << v.first << "] : ";
            for (auto &u : v.second)
            {
                cout << " " << u.first << ":" << u.second << " ";
            };
            cout << endl;
        };
        return 0;
    };
    int run_prim(string start_node)
    {
        assert(M.find(start_node) != M.end());
        set<string> in_tree;
        vector<edge> ans;
        in_tree.insert(start_node);
        while (in_tree.size() < M.size())
        {
            priority_queue<edge> q;
            for (auto node : in_tree)
            {
                for (auto node2 : M[node])
                {
                    if (in_tree.find(node2.first) == in_tree.end())
                    {
                        edge tmp_e;
                        tmp_e.a = node;
                        tmp_e.b = node2.first;
                        tmp_e.cost = node2.second;
                        q.push(tmp_e);
                    };
                };
            };
            // cout << " " << q.top().b << ":" << q.top().cost << " ";
            in_tree.insert(q.top().b);
            ans.push_back(q.top());
            // cout << endl;
        };
        cout << "[Prim Result]" << endl;
        for (auto e : ans)
        {
            cout << e.a << "---(" << e.cost << ")-->" << e.b << endl;
        };
        cout << endl;
        return 0;
    };
};

#endif
