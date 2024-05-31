#pragma once

struct Queue {
  int front, rear, len, cap;
  int *arr;

  Queue();
  void resize(int new_cap);
  void clear();
  void resize_clear(int new_cap);

  inline void add(int val) {
    arr[rear] = val;
    rear++;
    len++;
  }

  inline int remove() {
    int val = arr[front];
    front++;
    len--;
    return val;
  }
};
