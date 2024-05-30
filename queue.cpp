#include "queue.h"

Queue::Queue() : front(0), rear(0), len(0), cap(STACK_QUEUE_SIZE) {}

void Queue::resize(int new_cap) {
  if (cap >= new_cap) {
    return;
  }

  cap = new_cap;
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
