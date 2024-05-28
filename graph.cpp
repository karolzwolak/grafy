#include "graph.h"
#include "queue.h"
#include <random>

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

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
      sorted_vertex_arr(nullptr), is_sorted(false) {}

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
  quicksort_by_degree(pivot + 1, right);
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
    if (vertex_prior_other(j, pivot)) {
      swap_vertex(i, j);
      i++;
    }
  }
  swap_vertex(i, pivot);
  return i;
}

int Graph::choose_pivot([[maybe_unused]] int left, int right) {
  return (left + right) / 2;
}

void Graph::swap_vertex(int i, int j) {
  int tmp = sorted_vertex_arr[i];
  sorted_vertex_arr[i] = sorted_vertex_arr[j];
  sorted_vertex_arr[j] = tmp;
}

int Graph::bfs_with_max_dist(int start_v, int *component_elems,
                             int &component_len_out, Queue &queue,
                             int *dist_start) {
  int max_dist = 0;
  int max_dist_v = start_v;

  component_elems[0] = start_v;
  component_len_out = 1;

  dist_start[start_v] = 0;
  queue.add(start_v);

  while (queue.len > 0) {
    int v = queue.remove();

    int next_dist = dist_start[v] + 1;
    for (int i = 0; i < vertex_adj_arr[v].len; i++) {
      int u = vertex_adj_arr[v].adj[i];
      if (dist_start[u] != -1) {
        continue;
      }
      queue.add(u);
      component_elems[component_len_out++] = u;

      dist_start[u] = next_dist;

      if (dist_start[u] > max_dist) {
        max_dist = dist_start[u];
        max_dist_v = u;
      }
    }
  }
  return max_dist_v;
}

void Graph::single_component_vertices_eccentricity(
    int start_v, int *eccentrity_out, int *component_elems, Queue &queue,
    int *dist_start, int *dist_u, int *dist_v) {

  int component_len = 0;
  int u = bfs_with_max_dist(start_v, component_elems, component_len, queue,
                            dist_start);
  int v = bfs_with_max_dist(u, component_elems, component_len, queue, dist_u);
  bfs_with_max_dist(v, component_elems, component_len, queue, dist_v);

  for (int i = 0; i < component_len; i++) {
    int w = component_elems[i];
    int u_dist = dist_u[w];
    int v_dist = dist_v[w];
    eccentrity_out[w] = max(u_dist, v_dist);
  }
}

int Graph::vertices_eccentricity_and_n_components(int *eccentricity_out) {
  int n_components = 0;
  Queue queue;
  queue.resize_clear(len);
  int *component_elems = new int[len];

  int *dist_start = new int[len];
  int *dist_u = new int[len];
  int *dist_v = new int[len];
  for (int i = 0; i < len; i++) {
    dist_start[i] = -1;
    dist_u[i] = -1;
    dist_v[i] = -1;
  }

  for (int i = 0; i < len; i++) {
    if (dist_start[i] != -1) {
      continue;
    }
    n_components++;
    single_component_vertices_eccentricity(i, eccentricity_out, component_elems,
                                           queue, dist_start, dist_u, dist_v);
  }
  delete[] component_elems;
  delete[] dist_start;
  delete[] dist_u;
  delete[] dist_v;

  return n_components;
}
