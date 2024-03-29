
/* http://melpon.org/wandbox/permlink/paCC61fxm2muS5lc */

//=======================================================================
// Copyright 2001 Jeremy G. Siek, Andrew Lumsdaine, Lie-Quan Lee,
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#include "max_plus.hpp"
#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>


using namespace boost;

template <typename Graph, typename ParentMap> struct edge_writer {
  edge_writer(const Graph &g, const ParentMap &p) : m_g(g), m_parent(p) {}

  template <typename Edge>
  void operator()(std::ostream &out, const Edge &e) const {
    out << "[label=\"" << get(edge_weight, m_g, e) << "\"";
    typename graph_traits<Graph>::vertex_descriptor u = source(e, m_g),
                                                    v = target(e, m_g);
    if (m_parent[v] == u)
      out << ", color=\"black\"";
    else
      out << ", color=\"grey\"";
    out << "]";
  }
  const Graph &m_g;
  ParentMap m_parent;
};
template <typename Graph, typename Parent>
edge_writer<Graph, Parent> make_edge_writer(const Graph &g, const Parent &p) {
  return edge_writer<Graph, Parent>(g, p);
}

struct EdgeProperties {
  fun::maxPlus<int> weight;
};

int main() {
  enum { u, v, x, y, z, N };
  char name[] = {'u', 'v', 'x', 'y', 'z'};
  typedef std::pair<int, int> E;
  const int n_edges = 10;
  E edge_array[] = {E(u, y), E(u, x), E(u, v), E(v, u), E(x, y),
                    E(x, v), E(y, v), E(y, z), E(z, u), E(z, x)};
  fun::maxPlus<int> weight[n_edges] = {-4, 8, 5, -2, 9, -3, 7, 2, 6, 7};

  typedef adjacency_list<vecS, vecS, directedS, no_property, EdgeProperties>
      Graph;
  Graph g(edge_array, edge_array + n_edges, N);

  graph_traits<Graph>::edge_iterator ei, ei_end;
  property_map<Graph, fun::maxPlus<int> EdgeProperties::*>::type weight_pmap =
      get(&EdgeProperties::weight, g);
  int i = 0;
  for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei, ++i)
    weight_pmap[*ei] = weight[i];

  std::vector<fun::maxPlus<int>> distance(N,
                                          (std::numeric_limits<short>::max)());
  std::vector<std::size_t> parent(N);
  for (i = 0; i < N; ++i)
    parent[i] = i;
  distance[z] = 0;

  bool r = bellman_ford_shortest_paths(g, int(N),
                                       weight_map(weight_pmap)
                                           .distance_map(&distance[0])
                                           .predecessor_map(&parent[0]));

  if (r)
    for (i = 0; i < N; ++i)
      std::cout << name[i] << ": " << std::setw(3) << distance[i] << " "
                << name[parent[i]] << std::endl;
  else
    std::cout << "negative cycle" << std::endl;
  std::cout << '\n';

  // std::ofstream dot_file("figs/bellman-eg.dot");
  auto &dot_file = std::cout;

  dot_file << "digraph D {\n"
           << "  rankdir=LR\n"
           << "  size=\"5,3\"\n"
           << "  ratio=\"fill\"\n"
           << "  edge[style=\"bold\"]\n"
           << "  node[shape=\"circle\"]\n";

  {
    for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
      graph_traits<Graph>::edge_descriptor e = *ei;
      graph_traits<Graph>::vertex_descriptor u = source(e, g), v = target(e, g);
      // VC++ doesn't like the 3-argument get function, so here
      // we workaround by using 2-nested get()'s.
      dot_file << "  " << name[u] << " -> " << name[v] << "[label=\""
               << get(get(&EdgeProperties::weight, g), e) << "\"";
      if (parent[v] == u)
        dot_file << ", color=\"black\"";
      else
        dot_file << ", color=\"grey\"";
      dot_file << "]\n";
    }
  }
  dot_file << "}\n";
  return EXIT_SUCCESS;
}

//=======================================================================
// Copyright 2001 Jeremy G. Siek, Andrew Lumsdaine, Lie-Quan Lee,
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

//#include "max_plus.hpp"

using namespace boost;

template <typename Graph, typename ParentMap> struct edge_writer {
  edge_writer(const Graph &g, const ParentMap &p) : m_g(g), m_parent(p) {}

  template <typename Edge>
  void operator()(std::ostream &out, const Edge &e) const {
    out << "[label=\"" << get(edge_weight, m_g, e) << "\"";
    typename graph_traits<Graph>::vertex_descriptor u = source(e, m_g),
                                                    v = target(e, m_g);
    if (m_parent[v] == u)
      out << ", color=\"black\"";
    else
      out << ", color=\"grey\"";
    out << "]";
  }
  const Graph &m_g;
  ParentMap m_parent;
};
template <typename Graph, typename Parent>
edge_writer<Graph, Parent> make_edge_writer(const Graph &g, const Parent &p) {
  return edge_writer<Graph, Parent>(g, p);
}

struct EdgeProperties {
  int weight;
};

int main() {
  enum { u, v, x, y, z, N };
  char name[] = {'u', 'v', 'x', 'y', 'z'};
  typedef std::pair<int, int> E;
  const int n_edges = 10;
  E edge_array[] = {E(u, y), E(u, x), E(u, v), E(v, u), E(x, y),
                    E(x, v), E(y, v), E(y, z), E(z, u), E(z, x)};
  int weight[n_edges] = {-4, 8, 5, -2, 9, -3, 7, 2, 6, 7};

  typedef adjacency_list<vecS, vecS, directedS, no_property, EdgeProperties>
      Graph;
  Graph g(edge_array, edge_array + n_edges, N);

  graph_traits<Graph>::edge_iterator ei, ei_end;
  property_map<Graph, int EdgeProperties::*>::type weight_pmap =
      get(&EdgeProperties::weight, g);
  int i = 0;
  for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei, ++i)
    weight_pmap[*ei] = weight[i];

  std::vector<int> distance(N, (std::numeric_limits<short>::max)());
  std::vector<std::size_t> parent(N);
  for (i = 0; i < N; ++i)
    parent[i] = i;
  distance[z] = 0;

  bool r = bellman_ford_shortest_paths(g, int(N),
                                       weight_map(weight_pmap)
                                           .distance_map(&distance[0])
                                           .predecessor_map(&parent[0]));

  if (r)
    for (i = 0; i < N; ++i)
      std::cout << name[i] << ": " << std::setw(3) << distance[i] << " "
                << name[parent[i]] << std::endl;
  else
    std::cout << "negative cycle" << std::endl;
  std::cout << '\n';

  // std::ofstream dot_file("figs/bellman-eg.dot");
  auto &dot_file = std::cout;

  dot_file << "digraph D {\n"
           << "  rankdir=LR\n"
           << "  size=\"5,3\"\n"
           << "  ratio=\"fill\"\n"
           << "  edge[style=\"bold\"]\n"
           << "  node[shape=\"circle\"]\n";

  {
    for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
      graph_traits<Graph>::edge_descriptor e = *ei;
      graph_traits<Graph>::vertex_descriptor u = source(e, g), v = target(e, g);
      // VC++ doesn't like the 3-argument get function, so here
      // we workaround by using 2-nested get()'s.
      dot_file << "  " << name[u] << " -> " << name[v] << "[label=\""
               << get(get(&EdgeProperties::weight, g), e) << "\"";
      if (parent[v] == u)
        dot_file << ", color=\"black\"";
      else
        dot_file << ", color=\"grey\"";
      dot_file << "]\n";
    }
  }
  dot_file << "}\n";
  return EXIT_SUCCESS;
}
