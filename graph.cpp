#include "graph.h"

VertexAdj::VertexAdj() : len(0), adj(nullptr) {}

void VertexAdj::resize(int len) {
  this->len = len;
  adj = new int[len];
}

Graph::Graph() : vertex_len(0), vertex_adj_arr(nullptr) {}

void Graph::resize(int vertex_len) {
  this->vertex_len = vertex_len;
  vertex_adj_arr = new VertexAdj[vertex_len];
}
