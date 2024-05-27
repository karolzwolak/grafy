#include "graph.h"
#include "iostream"

void parse_graph(Graph &graph_out) {
  int vertex_len;
  std::cin >> vertex_len;
  graph_out.resize(vertex_len);

  for (int i = 0; i < vertex_len; i++) {
    int edge_len;
    std::cin >> edge_len;
    graph_out.vertex_adj_arr[i].resize(edge_len);

    for (int j = 0; j < edge_len; j++) {
      int edge_to;
      std::cin >> edge_to;
      graph_out.vertex_adj_arr[i].adj[j] = edge_to - 1;
    }
  }
}

void print_graph(const Graph &graph) {
  for (int i = 0; i < graph.vertex_len; i++) {
    std::cout << i << ": ";
    for (int j = 0; j < graph.vertex_adj_arr[i].len; j++) {
      std::cout << graph.vertex_adj_arr[i].adj[j] << " ";
    }
    std::cout << std::endl;
  }
}

// void solve_graph(Graph &graph) {}

int main() {
  int test_cases;
  std::cin >> test_cases;

  for (int i = 0; i < test_cases; i++) {
    Graph graph;
    parse_graph(graph);
    print_graph(graph);
    // solve_graph(graph);
  }
  return 0;
}
