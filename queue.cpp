#include "queue.h"

Queue::Queue() : front(0), rear(0), len(0), cap(0), arr(nullptr) {}

void Queue::resize_clear(int new_cap) {
  front = 0;
  rear = 0;
  len = 0;
  if (cap >= new_cap) {
    return;
  }

  if (arr != nullptr) {
    delete[] arr;
  }
  cap = new_cap;
  arr = new int[cap];
}

void Queue::add(int val) {
  arr[rear] = val;
  rear = (rear + 1) % cap;
  len++;
}

int Queue::remove() {
  int val = arr[front];
  front = (front + 1) % cap;
  len--;
  return val;
}
