#pragma once

#include "queue.h"
#include <random>

int max(int, int);
int min(int, int);

struct VertexAdj {
  int len, cap;
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
  int *eccentrities;

  int *dist_start;
  int *component_elems;
  int component_count;

  int *dist_ref;
  int *ecc_low;
  int *ecc_upp;

  int *stack;

  int *bipartile_group;
  bool is_bipartile;

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
  void quicksort_by_degree(int, int);
  bool vertex_prior_other(int, int);
  int partition_by_degree(int, int);
  void swap_vertex(int, int);

  int bfs_from_ref_and_comp_len(int ref_v);
  void bfs_eccentrity_with_comp_len(int start_v, int comp_len);

  bool dfs_check_bipartite(int start_v);
  void check_bipartile();

  void single_comp_eccentrity(int ref_v);
  void vertices_eccentricity_and_component_count();
};
