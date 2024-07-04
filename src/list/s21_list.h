#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <limits>

namespace s21 {
template <class T>
class List {
 private:
  class ListIterator;
  class ListConstIterator;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

 private:
  class Node {
   public:
    value_type data_;
    Node *prev_, *next_;

    Node(value_type data_ = value_type(), Node *prev_ = nullptr,
         Node *next_ = nullptr);
  };
  class ListIterator {
   public:
    Node *iter_;
    bool isSup_;

    ListIterator(Node *iter_ = nullptr, bool isSup_ = 0);

    bool operator==(const iterator &other);
    bool operator!=(const iterator &other);
    reference operator*();
    iterator operator++();
    iterator operator+(int value);
    iterator operator--();
    iterator operator-(int value);
  };
  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator(const iterator &iterator = nullptr);
  };

  Node *head_, *tail_, *sup_;
  size_type size_;

 public:
  List();
  List(size_type n);
  List(std::initializer_list<value_type> const &items);
  List(const List &l);
  List(List &&l);
  ~List();

  List operator=(List &&l);

  const_reference front();
  const_reference back();

  iterator begin() const;
  iterator end() const;

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(List &other);
  void merge(List &other);
  void splice(const_iterator pos, List &other);
  void reverse();
  void unique();
  void sort();

  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <class... Args>
  void insert_many_back(Args &&...args);
  template <class... Args>
  void insert_many_front(Args &&...args);

  void initList();
  void initHeadAndTail(value_type data);
};
}  // namespace s21

#include "s21_list.cc"

#endif