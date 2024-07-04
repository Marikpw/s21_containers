#ifndef STACK_H
#define STACK_H

#include "../list/s21_list.h"

namespace s21 {
template <class T, class Container = s21::List<T>>
class Stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Stack();
  Stack(std::initializer_list<value_type> const &items);
  Stack(const Stack &s);
  Stack(Stack &&s);
  ~Stack();

  Stack operator=(Stack &&s);

  const_reference top();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(Stack &other);

  template <class... Args>
  void insert_many_front(Args &&...args);

 private:
  Container baseClass_;
};
}  // namespace s21

#include "s21_stack.cc"

#endif