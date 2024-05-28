#include "graph.h"
#include "queue.h"
#include <cstdlib>
#include <ctime>

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
      sorted_vertex_arr(nullptr), is_sorted(false), eccentrities(nullptr),
      dist_start(nullptr), component_elems(nullptr), component_count(0),
      queue(Queue()) {

  srand(time(NULL));
}
void Graph::resize(int new_cap) {
  len = new_cap;
  queue.resize_clear(new_cap);
  if (new_cap <= cap) {
    return;
  }
  int old_cap = cap;
  cap = new_cap;
  VertexAdj *new_vertex_adj_arr = new VertexAdj[cap];

  if (vertex_adj_arr != nullptr) {
    for (int i = 0; i < old_cap; i++) {
      new_vertex_adj_arr[i] = vertex_adj_arr[i];
    }
    for (int i = old_cap; i < cap; i++) {
      new_vertex_adj_arr[i] = VertexAdj();
    }
    delete[] vertex_adj_arr;
    delete[] _v_adj_order_sum_arr;

    delete[] sorted_vertex_arr;
    delete[] eccentrities;

    delete[] dist_start;
    delete[] component_elems;
  }
  _v_adj_order_sum_arr = new int[cap];
  sorted_vertex_arr = new int[cap];

  eccentrities = new int[cap];
  dist_start = new int[cap];

  component_elems = new int[cap];

  vertex_adj_arr = new_vertex_adj_arr;
}

void Graph::clear() {
  is_sorted = false;
  component_count = 0;

  for (int i = 0; i < len; i++) {
    _v_adj_order_sum_arr[i] = -1;
    sorted_vertex_arr[i] = i;

    eccentrities[i] = 0;
    dist_start[i] = -1;
  }
}
void Graph::resize_clear(int new_cap) {
  resize(new_cap);
  clear();
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

int Graph::choose_pivot(int left, int right) {
  return rand() % (right - left + 1) + left;
}

void Graph::swap_vertex(int i, int j) {
  int tmp = sorted_vertex_arr[i];
  sorted_vertex_arr[i] = sorted_vertex_arr[j];
  sorted_vertex_arr[j] = tmp;
}

int Graph::bfs_eccentrity_and_comp_len(int start_v) {
  int next_dist = 0;

  component_elems[0] = start_v;
  int component_len = 1;

  dist_start[start_v] = 0;
  queue.add(start_v);

  while (queue.len > 0 && component_len < len) {
    int v = queue.remove();

    next_dist = dist_start[v] + 1;
    for (int i = 0; i < vertex_adj_arr[v].len; i++) {
      int u = vertex_adj_arr[v].adj[i];
      if (dist_start[u] != -1) {
        continue;
      }
      component_elems[component_len++] = u;

      queue.add(u);
      dist_start[u] = next_dist;
    }
  }
  queue.clear();
  eccentrities[start_v] = next_dist;

  return component_len;
}

void Graph::bfs_eccentrity_with_comp_len(int start_v, int comp_len) {
  int next_dist = 0;
  int unique = 1;

  dist_start[start_v] = 0;
  queue.add(start_v);

  while (queue.len > 0 && unique < comp_len) {
    int v = queue.remove();

    next_dist = dist_start[v] + 1;
    for (int i = 0; i < vertex_adj_arr[v].len; i++) {
      int u = vertex_adj_arr[v].adj[i];
      if (dist_start[u] != -1) {
        continue;
      }

      unique++;
      queue.add(u);
      dist_start[u] = next_dist;
    }
  }
  queue.clear();
  eccentrities[start_v] = next_dist;
}

void Graph::single_comp_eccentrity(int start_v) {
  int component_len = bfs_eccentrity_and_comp_len(start_v);

  // i = 1 to skip start_v
  for (int i = 1; i < component_len; i++) {
    int v = component_elems[i];
    for (int j = 0; j < component_len; j++) {
      dist_start[component_elems[j]] = -1;
    }
    bfs_eccentrity_with_comp_len(v, component_len);
  }
}

void Graph::vertices_eccentricity_and_component_count() {
  for (int i = 0; i < len; i++) {
    // eccentrity of 0 means the component has not been visited
    // or the component has only one vertex
    if (eccentrities[i] != 0) {
      continue;
    }
    single_comp_eccentrity(i);
  }
}
