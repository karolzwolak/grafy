#include "queue.h"

Queue::Queue() : front(0), rear(0), len(0), cap(0), arr(nullptr) {}

void Queue::resize(int new_cap) {
  if (cap >= new_cap) {
    return;
  }

  if (arr != nullptr) {
    delete[] arr;
  }
  cap = new_cap;
  arr = new int[cap];
}

void Queue::clear() {
  front = 0;
  rear = 0;
  len = 0;
}

void Queue::resize_clear(int new_cap) {
  resize(new_cap);
  clear();
}
