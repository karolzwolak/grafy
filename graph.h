#pragma once

struct VertexAdj {
  int len, cap;
  int *adj;

  VertexAdj();

  void resize_clear(int);
};

struct Graph {
  int len, cap;
  VertexAdj *vertex_adj_arr;

  Graph();
  void resize_clear(int);
};
