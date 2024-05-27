#include "graph.h"
#include "iostream"

void parse_graph(Graph &graph_out) {
  int vertex_len;
  std::cin >> vertex_len;
  graph_out.resize_clear(vertex_len);

  for (int i = 0; i < vertex_len; i++) {
    int edge_len;
    std::cin >> edge_len;
    graph_out.vertex_adj_arr[i].resize_clear(edge_len);

    for (int j = 0; j < edge_len; j++) {
      int edge_to;
      std::cin >> edge_to;
      graph_out.vertex_adj_arr[i].adj[j] = edge_to - 1;
    }
  }
}

void print_graph(const Graph &graph) {
  for (int i = 0; i < graph.len; i++) {
    std::cout << i << ": ";
    for (int j = 0; j < graph.vertex_adj_arr[i].len; j++) {
      std::cout << graph.vertex_adj_arr[i].adj[j] << " ";
    }
    std::cout << "\n";
  }
}

void solve_degree_sequence(Graph &graph) {
  graph.sort_vertex_by_degree_descending();
  for (int i = 0; i < graph.len; i++) {
    int vertex = graph.sorted_vertex_arr[i];
    std::cout << graph.vertex_adj_arr[vertex].len << " ";
  }
  std::cout << "\n";
}

void solve_graph(Graph &graph) {
  solve_degree_sequence(graph);
  for (int i = 0; i < 9; i++) {
    std::cout << "?\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int test_cases;
  std::cin >> test_cases;

  Graph graph;
  for (int i = 0; i < test_cases; i++) {
    parse_graph(graph);
    // print_graph(graph);
    solve_graph(graph);
  }
  return 0;
}
