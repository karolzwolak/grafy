#pragma once

struct Queue {
  int front, rear, len, cap;
  int *arr;

  Queue();
  void resize_clear(int new_cap);

  void add(int item);
  int remove();
};
