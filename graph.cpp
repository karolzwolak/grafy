#include "graph.h"
#include "queue.h"

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
    : len(0), cap(0), vertex_adj_arr(nullptr), sorted_vertex_arr(nullptr),
      is_sorted(false), eccentrities(nullptr), dist_start(nullptr),
      component_elems(nullptr), vertex_leader(nullptr), component_count(0),
      queue(Queue()) {}
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
    delete[] sorted_vertex_arr;

    delete[] eccentrities;
    delete[] dist_start;
    delete[] component_elems;
    delete[] vertex_leader;
  }
  sorted_vertex_arr = new int[cap];

  eccentrities = new int[cap];
  dist_start = new int[cap];
  component_elems = new int[cap];
  vertex_leader = new int[cap];

  vertex_adj_arr = new_vertex_adj_arr;
}

void Graph::clear() {
  is_sorted = false;
  component_count = 0;

  for (int i = 0; i < len; i++) {
    sorted_vertex_arr[i] = i;

    eccentrities[i] = 0;
    dist_start[i] = -1;
    vertex_leader[i] = -1;
  }
}
void Graph::resize_clear(int new_cap) {
  resize(new_cap);
  clear();
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
  if (u_i == v_i) {
    return true;
  }
  int u = sorted_vertex_arr[u_i];
  int v = sorted_vertex_arr[v_i];
  int u_deg = vertex_adj_arr[u].len;
  int v_deg = vertex_adj_arr[v].len;

  return u_deg < v_deg || (u_deg == v_deg && u < v);
}

int Graph::partition_by_degree(int left, int right) {
  int mid = (left + right) / 2;
  if (vertex_prior_other(mid, left)) {
    swap_vertex(left, mid);
  }
  if (vertex_prior_other(right, left)) {
    swap_vertex(left, right);
  }
  if (vertex_prior_other(mid, right)) {
    swap_vertex(mid, right);
  }
  int pivot = right;

  int pivot_v = sorted_vertex_arr[pivot];
  int pivot_deg = vertex_adj_arr[pivot_v].len;

  int i = left;

  for (int j = left; j < right; j++) {
    int j_v = sorted_vertex_arr[j];
    int j_deg = vertex_adj_arr[j_v].len;

    if (j_deg < pivot_deg || (j_deg == pivot_deg && j_v < pivot_v)) {
      swap_vertex(i, j);
      i++;
    }
  }
  swap_vertex(i, pivot);
  return i;
}

void Graph::swap_vertex(int i, int j) {
  int tmp = sorted_vertex_arr[i];
  sorted_vertex_arr[i] = sorted_vertex_arr[j];
  sorted_vertex_arr[j] = tmp;
}

int Graph::bfs_eccentrity_and_comp_len(int start_v) {
  int max_dist = 0;

  component_elems[0] = start_v;
  int component_len = 1;

  dist_start[start_v] = 0;
  queue.add(start_v);

  if (vertex_leader[start_v] == -1) {
    component_count++;
  }
  vertex_leader[start_v] = start_v;

  while (queue.len > 0 && component_len < len) {
    int v = queue.remove();

    int next_dist = dist_start[v] + 1;
    for (int i = 0; i < vertex_adj_arr[v].len; i++) {
      int u = vertex_adj_arr[v].adj[i];
      if (dist_start[u] != -1) {
        continue;
      }
      component_elems[component_len++] = u;

      queue.add(u);
      dist_start[u] = next_dist;
      vertex_leader[u] = start_v;
      max_dist = next_dist;
    }
  }
  queue.clear();
  eccentrities[start_v] = max_dist;

  return component_len;
}

// void Graph::bfs_eccentrity_with_comp_len(int start_v, int comp_len) {
//   int max_dist = 0;
//   int unique = 1;

//   dist_start[start_v] = 0;
//   queue.add(start_v);

//   while (queue.len > 0 && unique < comp_len) {
//     int v = queue.remove();

//     int next_dist = dist_start[v] + 1;
//     for (int i = 0; i < vertex_adj_arr[v].len; i++) {
//       int u = vertex_adj_arr[v].adj[i];
//       if (dist_start[u] != -1) {
//         continue;
//       }

//       unique++;
//       queue.add(u);
//       dist_start[u] = next_dist;
//       max_dist = next_dist;
//     }
//   }
//   queue.clear();
//   eccentrities[start_v] = max_dist;
// }

void Graph::vertices_eccentricity_and_component_count() {
  for (int i = 0; i < len; i++) {
    int component_len = bfs_eccentrity_and_comp_len(i);
    for (int j = 0; j < component_len; j++) {
      dist_start[component_elems[j]] = -1;
    }
  }
}

void Graph::calculate_properties() {
  vertices_eccentricity_and_component_count();
  sort_vertex_by_degree_descending();
}
