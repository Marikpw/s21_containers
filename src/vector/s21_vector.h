#ifndef VECTOR_H
#define VECTOR_H

#include "../array/s21_array.h"

namespace s21 {
template <class T>
class Vector : public Array<T> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Vector();
  Vector(size_type n);
  Vector(std::initializer_list<value_type> const &items);
  Vector(const Vector &v);
  Vector(Vector &&v);
  ~Vector();

  Vector operator=(Vector &&v);

  size_type max_size();
  size_type capacity();
  void reserve(size_type size);
  void shrink_to_fit();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(Vector &other);

  template <class... Args>
  iterator insert_many(iterator pos, Args &&...args);
  template <class... Args>
  void insert_many_back(Args &&...args);

 private:
  size_type capacity_;
};
}  // namespace s21

#include "s21_vector.cc"

#endif