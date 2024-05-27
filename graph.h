#pragma once

#include <random>

struct VertexAdj {
  int len, cap;
  int *adj;

  VertexAdj();

  void resize_clear(int);
};

struct Graph {
  int len, cap;
  VertexAdj *vertex_adj_arr;
  // the sum of the order of the adjacent vertices of each vertex
  // it is lazily calculated, -1 means it is not calculated
  // and used to determine ties when sorting vertices by degree
  int *_v_adj_order_sum_arr;
  // the sorted vertex array by degree
  int *sorted_vertex_arr;
  bool is_sorted;
  std::default_random_engine gen;

  Graph();
  void resize_clear(int);
  int vertex_adj_order_sum(int);

  void sort_vertex_by_degree_descending();
  void quicksort_by_degree(int, int);
  bool vertex_prior_other(int, int);
  int partition_by_degree(int, int);
  int choose_pivot(int, int);
  void swap_vertex(int, int);

  int dfs_with_max_dist(int start_v, int *component_elems,
                        int &component_len_out, int *stack, bool *visited,
                        int *dist_start);
  void single_component_vertices_eccentricity(int start_v, int *eccentrity_out,
                                              int *component_elems, int *stack,
                                              bool *visited_start,
                                              bool *visited_u, bool *visited_v,
                                              int *dist_start, int *dist_u,
                                              int *dist_v);
  int vertices_eccentricity_and_n_components(int *eccentricity_out);
};
