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

  int *greedy_color;
  int *lf_color;

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

  void quicksort_by_degree(int *, int, int);

  inline bool vertex_prior_other(int u, int v) {
    if (u == v) {
      return true;
    }
    int u_deg = vertex_adj_arr[u].len;
    int v_deg = vertex_adj_arr[v].len;

    return u_deg > v_deg || (u_deg == v_deg && u < v);
  }
  int partition_by_degree(int *, int, int);

  int bfs_from_ref_and_comp_len(int ref_v);
  void bfs_eccentricity_with_comp_len(int start_v, int comp_len);

  bool dfs_check_bipartite(int start_v);
  void check_bipartile();

  void single_comp_ifecc(int ref_v);
  void vertices_eccentricity_and_component_count();

  void apply_greedy_coloring(int v, int *color_arr);
  void apply_all_greedy_colorings();

  int count_cycle4_from_v(int start_v);
  void count_cycle4();
};
