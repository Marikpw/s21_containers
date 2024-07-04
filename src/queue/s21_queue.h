#ifndef QUEUE_H
#define QUEUE_H

#include "../list/s21_list.h"

namespace s21 {
template <class T, class Container = List<T>>
class Queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Queue();
  Queue(std::initializer_list<value_type> const &items);
  Queue(const Queue &q);
  Queue(Queue &&q);
  ~Queue();

  Queue operator=(Queue &&q);

  const_reference front();
  const_reference back();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(Queue &other);

  template <class... Args>
  void insert_many_back(Args &&...args);

 private:
  Container baseClass_;
};
}  // namespace s21

#include "s21_queue.cc"

#endif