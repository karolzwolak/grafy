#pragma once

struct Queue {
  int front, rear, len, cap;
  int *arr;

  Queue();
  void resize(int new_cap);
  void clear();
  void resize_clear(int new_cap);

  void add(int item);
  int remove();
};
