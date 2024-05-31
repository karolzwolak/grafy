#include "graph.h"
#include "queue.h"
#include <climits>
#include <iostream>

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
      component_elems(nullptr), component_count(0), dist_ref(nullptr),
      ecc_low(nullptr), ecc_upp(nullptr), stack(nullptr),
      bipartile_group(nullptr), is_bipartile(true), edge_count(0),
      complement_edges(0), queue(Queue()) {}

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

    delete[] dist_ref;
    delete[] ecc_low;
    delete[] ecc_upp;

    delete[] stack;

    delete[] bipartile_group;
  }
  sorted_vertex_arr = new int[cap];

  eccentrities = new int[cap];
  dist_start = new int[cap];
  component_elems = new int[cap];

  dist_ref = new int[cap];
  ecc_low = new int[cap];
  ecc_upp = new int[cap];

  stack = new int[cap];

  bipartile_group = new int[cap];

  vertex_adj_arr = new_vertex_adj_arr;
}

void Graph::clear() {
  is_sorted = false;
  component_count = 0;
  edge_count = 0;
  complement_edges = 0;

  for (int i = 0; i < len; i++) {
    sorted_vertex_arr[i] = i;

    eccentrities[i] = 0;

    dist_ref[i] = -1;
    ecc_low[i] = 0;
    ecc_upp[i] = INT_MAX;

    dist_start[i] = -1;
    bipartile_group[i] = -1;
  }
}
void Graph::resize_clear(int new_cap) {
  resize(new_cap);
  clear();
}

void Graph::parse_from_stdin() {
  int vertex_len;
  std::cin >> vertex_len;
  resize_clear(vertex_len);

  for (int i = 0; i < vertex_len; i++) {
    int edge_len;
    std::cin >> edge_len;

    edge_count += edge_len;
    vertex_adj_arr[i].resize_clear(edge_len);

    for (int j = 0; j < edge_len; j++) {
      int edge_to;
      std::cin >> edge_to;
      vertex_adj_arr[i].adj[j] = edge_to - 1;
    }
  }
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

int Graph::bfs_from_ref_and_comp_len(int ref_v) {
  int max_dist = 0;

  component_elems[0] = ref_v;
  int component_len = 1;

  dist_ref[ref_v] = 0;
  queue.add(ref_v);

  while (queue.len > 0) {
    int v = queue.remove();

    int next_dist = dist_ref[v] + 1;
    for (int i = 0; i < vertex_adj_arr[v].len; i++) {
      int u = vertex_adj_arr[v].adj[i];
      if (dist_ref[u] != -1) {
        continue;
      }
      component_elems[component_len++] = u;

      queue.add(u);
      dist_ref[u] = next_dist;
      max_dist = next_dist;
    }
  }
  eccentrities[ref_v] = max_dist;

  return component_len;
}

void Graph::bfs_eccentrity_with_comp_len(int start_v, int comp_len) {
  int max_dist = 0;
  int unique = 1;

  dist_start[start_v] = 0;
  queue.add(start_v);

  while (queue.len > 0 && unique < comp_len) {
    int v = queue.remove();

    int next_dist = dist_start[v] + 1;
    for (int i = 0; i < vertex_adj_arr[v].len; i++) {
      int u = vertex_adj_arr[v].adj[i];
      if (dist_start[u] != -1) {
        continue;
      }

      unique++;
      queue.add(u);
      dist_start[u] = next_dist;
      max_dist = next_dist;
    }
  }
  queue.clear();
  eccentrities[start_v] = max_dist;
}

void Graph::single_comp_eccentrity(int ref_v) {
  // std::cout << "ref " << ref_v << "\n";
  int component_len = bfs_from_ref_and_comp_len(ref_v);
  component_count++;

  int ecc_computed = 1;

  for (int i = 1; i < component_len; i++) {
    int v = component_elems[i];

    ecc_low[v] = max(dist_ref[v], eccentrities[ref_v] - dist_ref[v]);
    ecc_upp[v] = eccentrities[ref_v] + dist_ref[v];

    if (ecc_low[v] == ecc_upp[v]) {
      eccentrities[v] = ecc_low[v];
      ecc_computed++;
    }
  }

  for (int ffo_id = component_len - 1; ffo_id >= 1; ffo_id--) {
    if (ecc_computed == component_len) {
      break;
    }
    int ffo_v = component_elems[ffo_id];

    if (eccentrities[ffo_v] == 0) {
      ecc_computed++;
    }
    bfs_eccentrity_with_comp_len(ffo_v, component_len);

    dist_start[ref_v] = -1;
    for (int j = 1; j < component_len; j++) {
      int v = component_elems[j];

      if (eccentrities[v] != 0) {
        dist_start[v] = -1;
        continue;
      }

      ecc_low[v] = max(ecc_low[v], dist_start[v]);
      ecc_upp[v] =
          min(ecc_upp[v], max(ecc_low[v], dist_ref[ffo_v] + dist_ref[v]));

      if (ecc_low[v] == ecc_upp[v]) {
        eccentrities[v] = ecc_low[v];
        ecc_computed++;
      }

      dist_start[v] = -1;
    }
  }
  // std::cout << "elem count" << component_len << " bfs count" << bfs_count
  //           << "\n";
}

void Graph::vertices_eccentricity_and_component_count() {
  for (int i = 0; i < len; i++) {
    // pick ref vertex to be the one with highest degree
    int v = sorted_vertex_arr[len - 1 - i];

    // if (eccentrities[v] != 0) {
    if (dist_ref[v] != -1) {
      continue;
    }
    single_comp_eccentrity(v);
  }
}

bool Graph::dfs_check_bipartite(int start_v) {
  int stack_len = 1;
  stack[0] = start_v;

  bipartile_group[start_v] = 0;

  while (stack_len > 0) {
    int v = stack[--stack_len];

    int color = 1 - bipartile_group[v];

    for (int i = 0; i < vertex_adj_arr[v].len; i++) {
      int u = vertex_adj_arr[v].adj[i];

      if (bipartile_group[u] == -1) {
        stack[stack_len++] = u;
        bipartile_group[u] = color;
      } else if (bipartile_group[u] != color) {
        return false;
      }
    }
  }
  return true;
}

void Graph::check_bipartile() {
  is_bipartile = true;
  for (int i = 0; i < len; i++) {
    if (bipartile_group[i] != -1) {
      continue;
    }
    if (!dfs_check_bipartite(i)) {
      is_bipartile = false;
      break;
    }
  }
}

void Graph::calculate_properties() {
  sort_vertex_by_degree_descending();
  vertices_eccentricity_and_component_count();
  check_bipartile();
  long long max_edges = ((long long)len * (len - 1)) / 2;
  complement_edges = max_edges - edge_count / 2;
}
