#ifndef _S21_SET_H_
#define _S21_SET_H_

#include <utility>

#include "../s21_containers.h"
#include "../tree/AVLTree.h"

namespace s21 {
template <class Key>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = typename AVLTree<Key, Key>::iterator;
  using const_iterator = typename AVLTree<Key, Key>::const_iterator;
  using tree_type = AVLTree<key_type, value_type>;

  set() : tree_(new tree_type{}) {}

  set(std::initializer_list<value_type> const &items) : tree_(new tree_type{}) {
    for (const auto &element : items) {
      tree_->insert(element, element);
    }
  }

  set(const set &s) : tree_(new tree_type(*s.tree_)){};

  set(set &&s) : tree_(s.tree_) { s.tree_ = nullptr; }

  ~set() {
    delete tree_;
    tree_ = nullptr;
  }

  set &operator=(set &&s) {
    if (this != &s) {
      delete tree_;
      tree_ = s.tree_;
      s.tree_ = nullptr;
    }
    return *this;
  }

  set &operator=(const set &s) {
    if (this != &s) {
      *tree_ = *s.tree_;
    }
    return *this;
  }

  const_iterator begin() const noexcept { return tree_->begin(); }
  iterator begin() noexcept { return tree_->begin(); }

  const_iterator end() const noexcept { return tree_->end(); };
  iterator end() noexcept { return tree_->end(); };

  [[nodiscard]] bool empty() const noexcept { return tree_->empty(); };

  [[nodiscard]] size_type size() const noexcept { return tree_->size(); };

  [[nodiscard]] size_type max_size() const noexcept {
    return tree_->size_max();
  }

  void clear() noexcept { tree_->clear(); };

  std::pair<iterator, bool> insert(const value_type &value) {
    auto result = tree_->insert(value);
    return {iterator(result.first), result.second};
  }

  void erase(iterator pos) noexcept { tree_->erase(pos); }

  void swap(set &other) noexcept { tree_->swap(*other.tree_); };

  void merge(set &other) { tree_->merge(*other.tree_); };

  iterator find(const Key &key) noexcept { return tree_->find(key); }
  const_iterator find(const Key &key) const noexcept {
    return tree_->find(key);
  }

  [[nodiscard]] bool contains(const Key &key) { return tree_->contains(key); }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> vec;
    vec.reserve(sizeof...(args));
    (vec.emplace_back(insert(std::forward<Args>(args))), ...);
    return vec;
  }

 private:
  AVLTree<Key, Key> *tree_;
};

}  // namespace s21

#endif  // _S21_SET_H_
