#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <limits>

namespace s21 {
template <class T, size_t N = 0>
class Array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Array();
  Array(std::initializer_list<value_type> const &items);
  Array(const Array &a);
  Array(Array &&a);
  ~Array();

  Array operator=(Array &&a);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();
  iterator begin() const;
  iterator end() const;

  bool empty();
  size_type size() const;
  size_type max_size();

  void swap(Array &other);
  void fill(const_reference value);

  template <typename Arr>
  void copy(Arr &copyArr);
  void clear();

 protected:
  iterator arr_;
  size_type size_;
};
}  // namespace s21

#include "s21_array.cc"

#endif