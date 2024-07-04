#ifndef _S21_MULTISET_H_
#define _S21_MULTISET_H_

#include <iostream>
#include <utility>

#include "../s21_containers.h"
#include "../tree/AVLTree.h"

namespace s21 {

template <typename Key>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using tree_type = AVLTree<Key, int>;
  using const_iterator = typename tree_type::ConstIterator;
  using size_type = size_t;

  class iterator {
   public:
    explicit iterator(typename tree_type::iterator it)
        : it_(it),
          count_(it.get_node() != nullptr ? it.get_node()->value_ : 0) {}
    iterator() {}

    iterator& operator++() {
      if (count_ < it_.get_node()->value_) {
        ++count_;
      } else {
        ++it_;
        count_ = 1;
      }
      return *this;
    }

    iterator operator++(int) {
      iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    const Key& operator*() const { return it_.get_node()->key_; }

    bool operator==(const iterator& other) const { return it_ == other.it_; }

    bool operator!=(const iterator& other) const { return !(*this == other); }

    auto get_node() const { return it_.get_node(); }

    typename tree_type::iterator it() { return it_; }

   private:
    typename tree_type::iterator it_;
    int count_;
  };

  multiset() : tree_(new tree_type{}) {}

  multiset(std::initializer_list<value_type> const& items)
      : tree_(new tree_type{}) {
    for (const auto& item : items) {
      insert(item);
    }
  }

  multiset(const multiset& other) : tree_(new tree_type(*other.tree_)) {}
  multiset(multiset&& other) noexcept
      : tree_(new tree_type(std::move(*other.tree_))) {}

  multiset& operator=(const multiset& other) {
    *tree_ = *other.tree_;
    return *this;
  }

  multiset& operator=(multiset&& other) noexcept {
    *tree_ = std::move(*other.tree_);
    return *this;
  }

  ~multiset() {
    delete tree_;
    tree_ = nullptr;
  }

  iterator begin() noexcept { return iterator(tree_->begin()); }

  const iterator begin() const noexcept { return iterator(tree_->begin()); }

  iterator end() noexcept { return iterator(tree_->end()); }

  const iterator end() const noexcept { return iterator(tree_->end()); }

  [[nodiscard]] bool empty() const noexcept { return tree_->empty(); }

  [[nodiscard]] size_type size() const noexcept {
    size_type counter = 0;
    for (auto iter = begin(); iter != end(); iter++) {
      ++counter;
    }

    return counter;
  }

  [[nodiscard]] size_type max_size() const noexcept {
    return tree_->size_max();
  }

  void clear() noexcept { tree_->clear(); }  // Changed clean() to clear()

  iterator insert(const key_type& key) {
    if (tree_->contains(key)) {
      auto it = find(key);
      it.get_node()->value_++;
      return iterator(it);
    }
    tree_->insert(key, 1);
    return {};
  }

  void erase(iterator pos) {
    if (pos.get_node()->value_ > 1) {
      pos.get_node()->value_--;
    } else {
      tree_->erase(pos.it());
    }
  }

  void swap(multiset& other) noexcept { tree_->swap(*other.tree_); }

  void merge(multiset& other) noexcept {
    for (const auto& elem : other) {
      insert(elem);
    }
  }

  [[nodiscard]] size_type count(const key_type& key) const {
    auto it = tree_->find(key);
    if (it != tree_->end()) {
      return it.get_node()->value_;
    }
    return 0;
  }

  iterator find(const key_type& key) noexcept {
    return iterator(tree_->find(key));
  }

  const iterator find(const key_type& key) const noexcept {
    return iterator(tree_->find(key));
  }

  [[nodiscard]] bool contains(const key_type& key) const noexcept {
    return tree_->contains(key);
  }

  std::pair<typename multiset::iterator, typename multiset::iterator>
  equal_range(const key_type& key) noexcept {
    auto lower = lower_bound(key);
    auto upper = upper_bound(key);
    return std::make_pair(lower, upper);
  }

  std::pair<typename multiset::const_iterator,
            typename multiset::const_iterator>
  equal_range(const key_type& key) const noexcept {
    auto lower = lower_bound(key);
    auto upper = upper_bound(key);
    return std::make_pair(lower, upper);
  }

  typename multiset::iterator lower_bound(const key_type& key) noexcept {
    auto it = tree_->begin();
    while (it != tree_->end() && *it < key) ++it;
    return iterator(it);
  }

  typename multiset::const_iterator lower_bound(const key_type& key) const {
    auto it = tree_->begin();
    while (it != tree_->end() && *it < key) ++it;
    return iterator(it);
  }

  typename multiset::iterator upper_bound(const key_type& key) noexcept {
    auto it = tree_->begin();
    while (it != tree_->end() && *it <= key) ++it;
    return iterator(it);
  }

  typename multiset::const_iterator upper_bound(
      const key_type& key) const noexcept {
    auto it = tree_->begin();
    while (it != tree_->end() && *it <= key) ++it;
    return iterator(it);
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    auto this_copy = *this;
    std::vector<std::pair<iterator, bool>> result;
    ((result.emplace_back(insert(std::forward<Args>(args)), false)), ...);
    std::size_t index = 0;
    ((result[index++].second = (count(args) > this_copy.count(args))), ...);
    return result;
  }

 private:
  tree_type* tree_;
};

}  // namespace s21

#endif  // _S21_MULTISET_H_