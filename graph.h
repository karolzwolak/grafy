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
  int *eccentrities;

  int *dist_start;
  int *component_elems;
  int component_count;

  Queue queue;

  Graph();
  void resize_clear(int);

  void resize(int);
  void clear();

  int vertex_adj_order_sum(int);

  void sort_vertex_by_degree_descending();
  void quicksort_by_degree(int, int);
  bool vertex_prior_other(int, int);
  int partition_by_degree(int, int);
  int choose_pivot(int, int);
  void swap_vertex(int, int);

  int bfs_eccentrity_and_comp_len(int start_v);
  void bfs_eccentrity_with_comp_len(int start_v, int comp_len);

  void single_comp_eccentrity(int start_v);
  void vertices_eccentricity_and_component_count();
};
