#pragma once

struct VertexAdj {
  int len;
  int *adj;

  VertexAdj();

  void resize(int);
};

struct Graph {
  int vertex_len;
  VertexAdj *vertex_adj_arr;

  Graph();
  void resize(int);
};
