#include "graph.h"

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

Graph::Graph() : len(0), cap(0), vertex_adj_arr(nullptr) {}

void Graph::resize_clear(int new_cap) {
  len = new_cap;
  if (new_cap <= cap) {
    return;
  }
  cap = new_cap;
  if (vertex_adj_arr != nullptr) {
    delete[] vertex_adj_arr;
  }
  vertex_adj_arr = new VertexAdj[cap];
}
