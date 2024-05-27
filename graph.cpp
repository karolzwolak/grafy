#include "graph.h"
#include <random>

VertexAdj::VertexAdj() : len(0), cap(0), adj(nullptr) {}

void VertexAdj::resize_clear(int new_cap) {
  len = new_cap;
  if (new_cap <= cap) {
    return;
  }
  cap = new_cap;
  if (adj != nullptr) {
    delete[] adj;
  }
  adj = new int[cap];
}

Graph::Graph()
    : len(0), cap(0), vertex_adj_arr(nullptr), _v_adj_order_sum_arr(nullptr),
      sorted_vertex_arr(nullptr), is_sorted(false) {
  std::random_device rd;
  gen = std::default_random_engine(rd());
}

void Graph::resize_clear(int new_cap) {
  is_sorted = false;
  len = new_cap;
  if (new_cap <= cap) {
    return;
  }
  cap = new_cap;
  if (vertex_adj_arr != nullptr) {
    delete[] vertex_adj_arr;
  }
  vertex_adj_arr = new VertexAdj[cap];
  _v_adj_order_sum_arr = new int[cap];
  sorted_vertex_arr = new int[cap];

  for (int i = 0; i < cap; i++) {
    _v_adj_order_sum_arr[i] = -1;
    sorted_vertex_arr[i] = i;
  }
}

int Graph::vertex_adj_order_sum(int v) {
  if (_v_adj_order_sum_arr[v] != -1) {
    return _v_adj_order_sum_arr[v];
  }
  int sum = 0;
  for (int i = 0; i < vertex_adj_arr[v].len; i++) {
    sum += vertex_adj_arr[v].adj[i];
  }
  _v_adj_order_sum_arr[v] = sum;
  return sum;
}

void Graph::sort_vertex_by_degree_descending() {
  if (is_sorted) {
    return;
  }
  quicksort_by_degree(0, len - 1);
  is_sorted = true;
}
void Graph::quicksort_by_degree(int left, int right) {
  if (left >= right) {
    return;
  }
  int pivot = partition_by_degree(left, right);

  quicksort_by_degree(left, pivot - 1);
  quicksort_by_degree(pivot + 1, pivot);
}

bool Graph::vertex_prior_other(int u_i, int v_i) {
  int u = sorted_vertex_arr[u_i];
  int v = sorted_vertex_arr[v_i];
  int u_deg = vertex_adj_arr[u].len;
  int v_deg = vertex_adj_arr[v].len;

  return u_deg > v_deg ||
         (u_deg == v_deg && vertex_adj_order_sum(u) >= vertex_adj_order_sum(v));
}

int Graph::partition_by_degree(int left, int right) {
  int pivot = choose_pivot(left, right);
  swap_vertex(pivot, right);
  pivot = right;

  int i = left;
  for (int j = left; j < right; j++) {
    if (vertex_prior_other(i, pivot)) {
      swap_vertex(i, j);
      i++;
    }
  }
  swap_vertex(i, pivot);
  return i;
}

int Graph::choose_pivot(int left, int right) {
  auto dis = std::uniform_int_distribution<int>(left, right);
  return dis(gen);
}

void Graph::swap_vertex(int i, int j) {
  int tmp = sorted_vertex_arr[i];
  sorted_vertex_arr[i] = sorted_vertex_arr[j];
  sorted_vertex_arr[j] = tmp;
}
