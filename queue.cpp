#include "queue.h"

Queue::Queue(int cap, int *arr)
    : front(0), rear(0), len(0), cap(cap), arr(arr) {}

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

void Queue::add(int val) {
  arr[rear] = val;
  rear++;
  if (rear == cap) {
    rear = 0;
  }
  len++;
}

int Queue::remove() {
  int val = arr[front];
  front++;
  if (front == cap) {
    front = 0;
  }
  len--;
  return val;
}
