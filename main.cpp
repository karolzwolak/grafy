#include "graph.h"
#include <iostream>

void print_graph(const Graph &graph) {
  std::cout << "Graph:\n";
  for (int i = 0; i < graph.len; i++) {
    std::cout << i << ": ";
    for (int j = 0; j < graph.len_arr[i]; j++) {
      std::cout << graph.adj[i][j] << " ";
    }
    std::cout << "\n";
  }
}

void print_degree_sequence(Graph &graph) {
  for (int i = graph.len - 1; i >= 0; i--) {
    int vertex = graph.sorted_vertex_arr[i];
    std::cout << graph.len_arr[vertex] << " ";
  }
  std::cout << "\n";
}

void print_ecentricities(Graph &graph) {
  for (int i = 0; i < graph.len; i++) {
    std::cout << graph.ecc[i] << " ";
  }
  std::cout << "\n";
}

void solve_graph(Graph &graph) {
  graph.calculate_properties();
  // 1
  print_degree_sequence(graph);

  // 2
  std::cout << graph.component_count << "\n";

  // 3
  if (graph.is_bipartile) {
    std::cout << "T\n";
  } else {
    std::cout << "F\n";
  }
  // 4
  print_ecentricities(graph);
  // 5
  std::cout << "?\n";
  // 6
  std::cout << "?\n";
  // 7
  std::cout << "?\n";
  // 8
  std::cout << "?\n";
  // 9
  std::cout << "?\n";
  // 10
  std::cout << graph.complement_edges << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int test_cases;
  std::cin >> test_cases;

  Graph graph;
  for (int i = 0; i < test_cases; i++) {
    graph.parse_from_stdin();
    // print_graph(graph);
    solve_graph(graph);
  }
  return 0;
}
