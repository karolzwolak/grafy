#pragma once

#define STACK_QUEUE_SIZE 1'000'000

struct Queue {
  int front, rear, len, cap;
  int arr[STACK_QUEUE_SIZE];

  Queue();
  void resize(int new_cap);
  void clear();
  void resize_clear(int new_cap);

  void add(int item);
  int remove();
};
