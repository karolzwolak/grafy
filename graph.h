#pragma once

#include "queue.h"
#include <random>

int max(int, int);
int min(int, int);

void swap_vertex(int *, int, int);

struct VertexAdj {
  int len, cap, last_smaller_id;
  int *adj;

  VertexAdj();

  void resize_clear(int);
};

struct Graph {
  int len, cap;
  VertexAdj *vertex_adj_arr;
  // the sorted vertex array by degree
  int *sorted_vertex_arr;
  bool is_sorted;
  int *ecc;

  int *dist_start;
  int *component_elems;
  int component_count;

  int *dist_ref;
  int *ecc_low;
  int *ecc_upp;

  int *stack;

  int *bipartile_group;
  bool is_bipartile;

  long long cycle4_count;
  int *local_count;

  int edge_count;
  long long complement_edges;

  Queue queue;

  Graph();

  void parse_from_stdin();
  void resize_clear(int);

  void resize(int);
  void clear();

  void calculate_properties();

  void sort_vertex_by_degree_descending();

  void sort_all_adj_list_by_degree_descending();

  void move_smaller_adj_degrees_to_end(int);
  void sort_adj_by_degree_descending(int);

  inline void quicksort_by_degree(int *arr, int left, int right) {
    if (left >= right) {
      return;
    }
    int pivot = partition_by_degree(arr, left, right);

    quicksort_by_degree(arr, left, pivot - 1);
    quicksort_by_degree(arr, pivot + 1, right);
  }

  inline int partition_by_degree(int *arr, int left, int right) {
    int mid = (left + right) / 2;
    if (vertex_prior_other(arr[mid], arr[left])) {
      swap_vertex(arr, left, mid);
    }
    if (vertex_prior_other(arr[right], arr[left])) {
      swap_vertex(arr, left, right);
    }
    if (vertex_prior_other(arr[mid], arr[right])) {
      swap_vertex(arr, mid, right);
    }
    int pivot = right;

    int pivot_v = arr[pivot];
    int pivot_deg = vertex_adj_arr[pivot_v].len;

    int i = left;

    for (int j = left; j < right; j++) {
      int j_v = arr[j];
      int j_deg = vertex_adj_arr[j_v].len;

      if (j_deg > pivot_deg || (j_deg == pivot_deg && j_v < pivot_v)) {
        swap_vertex(arr, i, j);
        i++;
      }
    }
    swap_vertex(arr, i, pivot);
    return i;
  }

  inline bool vertex_prior_other(int u, int v) {
    if (u == v) {
      return true;
    }
    int u_deg = vertex_adj_arr[u].len;
    int v_deg = vertex_adj_arr[v].len;

    return u_deg > v_deg || (u_deg == v_deg && u < v);
  }

  int bfs_from_ref_and_comp_len(int ref_v);
  void bfs_eccentricity_with_comp_len(int start_v, int comp_len);

  bool dfs_check_bipartite(int start_v);
  void check_bipartile();

  void single_comp_ifecc(int ref_v);
  void vertices_eccentricity_and_component_count();

  int count_cycle4_from_v(int start_v);
  void count_cycle4();
};
