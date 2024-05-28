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
  // the sum of the order of the adjacent vertices of each vertex
  // it is lazily calculated, -1 means it is not calculated
  // and used to determine ties when sorting vertices by degree
  int *_v_adj_order_sum_arr;
  // the sorted vertex array by degree
  int *sorted_vertex_arr;
  bool is_sorted;

  Queue queue;

  Graph();
  void resize_clear(int);
  int vertex_adj_order_sum(int);

  void sort_vertex_by_degree_descending();
  void quicksort_by_degree(int, int);
  bool vertex_prior_other(int, int);
  int partition_by_degree(int, int);
  int choose_pivot(int, int);
  void swap_vertex(int, int);

  int bfs_with_max_dist(int start_v, int *component_elems,
                        int &component_len_out, int *dist_start);
  void single_component_vertices_eccentricity(int start_v, int *component_elems,
                                              int *eccentrity_out,
                                              int *dist_start);
  int vertices_eccentricity_and_n_components(int *eccentricity_out);
};
