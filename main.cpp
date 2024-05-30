#include "graph.h"
#include <iostream>

#define STACK_QUEUE_SIZE 1'000'000

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
  std::cout << "Graph:\n";
  for (int i = 0; i < graph.len; i++) {
    std::cout << i << ": ";
    for (int j = 0; j < graph.vertex_adj_arr[i].len; j++) {
      std::cout << graph.vertex_adj_arr[i].adj[j] << " ";
    }
    std::cout << "\n";
  }
}

void print_degree_sequence(Graph &graph) {
  for (int i = graph.len - 1; i >= 0; i--) {
    int vertex = graph.sorted_vertex_arr[i];
    std::cout << graph.vertex_adj_arr[vertex].len << " ";
  }
  std::cout << "\n";
}

void print_ecentricities(Graph &graph) {
  for (int i = 0; i < graph.len; i++) {
    std::cout << graph.eccentrities[i] << " ";
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
  std::cout << "?\n";
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
  std::cout << "?\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int test_cases;
  std::cin >> test_cases;

  int queue_arr[STACK_QUEUE_SIZE];
  Queue q(STACK_QUEUE_SIZE, queue_arr);

  Graph graph(q);
  for (int i = 0; i < test_cases; i++) {
    parse_graph(graph);
    // print_graph(graph);
    solve_graph(graph);
  }
  return 0;
}
