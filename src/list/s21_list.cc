#include "s21_list.h"

namespace s21 {

/**
 * @brief Базовый конструктор, инициализирующий список.
 */
template <class value_type>
List<value_type>::List()
    : head_(nullptr), tail_(nullptr), sup_(nullptr), size_(0) {
  initList();
}

/**
 * @brief Параметризированный конструктор, инициализирующий список размером n.
 *
 * @param n размер списка
 */
template <class value_type>
List<value_type>::List(size_type n)
    : head_(nullptr), tail_(nullptr), sup_(nullptr), size_(0) {
  for (int i = 0; i < (int)n; i++) push_back(value_type());
}

/**
 * @brief Конструктор, инициализирующий список, используя std::initializer_list.
 *
 * @param items initializer_list
 */
template <class value_type>
List<value_type>::List(std::initializer_list<value_type> const &items)
    : head_(nullptr), tail_(nullptr), sup_(nullptr), size_(0) {
  for (auto item : items) push_back(item);
}

/**
 * @brief Конструктор копирования
 *
 * @param l копируемый список
 */
template <class value_type>
List<value_type>::List(const List &l)
    : head_(nullptr), tail_(nullptr), sup_(nullptr), size_(0) {
  for (auto item : l) push_back(item);
}

/**
 * @brief Конструктор переноса
 *
 * @param l переносимый список
 */
template <class value_type>
List<value_type>::List(List &&l)
    : head_(nullptr), tail_(nullptr), sup_(nullptr), size_(0) {
  for (auto item : l) push_back(item);
  l.clear();
}

/**
 * @brief Деструктор
 */
template <class value_type>
List<value_type>::~List() {
  clear();
}

/**
 * @brief Оператор присваивания.
 *
 * @param l копируемый список
 *
 * @return скопированный объект
 */
template <class value_type>
List<value_type> List<value_type>::operator=(List &&l) {
  clear();
  for (auto item : l) push_back(item);
  l.clear();
  return *this;
}

/**
 * @brief Возвращение значения первого элемента списка.
 *
 * @return значение первого элемента
 */
template <class value_type>
typename List<value_type>::const_reference List<value_type>::front() {
  return head_->data_;
}

/**
 * @brief Возвращение значения последнего элемента списка.
 *
 * @return значение последнего элемента.
 */
template <class value_type>
typename List<value_type>::const_reference List<value_type>::back() {
  return tail_->data_;
}

/**
 * @brief Возвращение итератора первого элемента списка.
 *
 * @return итератор первого элемента.
 */
template <class value_type>
typename List<value_type>::iterator List<value_type>::begin() const {
  return ListIterator(head_);
}

/**
 * @brief Возвращение итератора последнего элемента списка.
 *
 * @return итератор последнего элемента.
 */
template <class value_type>
typename List<value_type>::iterator List<value_type>::end() const {
  return ListIterator(sup_, 1);
}

/**
 * @brief Проверка пустой ли список.
 *
 * @return bool value
 *
 * @note true - список пустой
 * @note false - список непустой
 */
template <class value_type>
bool List<value_type>::empty() {
  return size_ ? 0 : 1;
}

/**
 * @return Количество элементов списка.
 */
template <class value_type>
typename List<value_type>::size_type List<value_type>::size() {
  return size_;
}

/**
 * @return Максимально возможное количество элементов списка.
 */
template <class value_type>
typename List<value_type>::size_type List<value_type>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(Node) / 2;
}

/**
 * @brief Удаление всех элементов.
 */
template <class value_type>
void List<value_type>::clear() {
  while (size_) pop_back();
  if (sup_) delete sup_;
  sup_ = head_ = tail_ = nullptr;
}

/**
 * @brief Вставка элемента со значением value на позицию, на которую указывает
 * итератор pos.
 *
 * @return итератор на добавленный элемент
 */
template <class value_type>
typename List<value_type>::iterator List<value_type>::insert(
    iterator pos, const_reference value) {
  Node *tmp = new Node(value, pos.iter_->prev_, pos.iter_);
  tmp->prev_->next_ = tmp->next_->prev_ = tmp;
  if (pos == begin())
    head_ = tmp;
  else if (pos == end())
    tail_ = tmp;
  size_++;
  return ListIterator(tmp);
}

/**
 * @brief Удаление элемента, на который указывает итератор pos.
 */
template <class value_type>
void List<value_type>::erase(iterator pos) {
  if (pos == begin()) {
    head_ = pos.iter_->next_;
    pos.iter_->prev_->next_ = pos.iter_->next_;
    pos.iter_->next_->prev_ = pos.iter_->prev_;
  } else if (pos == end()) {
    pos = pos.iter_->prev_;
    tail_ = sup_->prev_ = pos.iter_->prev_;
    pos.iter_->prev_->next_ = sup_;
  } else {
    pos.iter_->prev_->next_ = pos.iter_->next_;
    pos.iter_->next_->prev_ = pos.iter_->prev_;
  }
  delete pos.iter_;
  size_--;
}

/**
 * @brief Добавление элемента со значением value в конец списка.
 */
template <class value_type>
void List<value_type>::push_back(const_reference value) {
  if (!head_)
    initHeadAndTail(value);
  else {
    tail_->next_ = new Node(value, tail_, sup_);
    tail_ = tail_->next_;
    sup_->prev_ = tail_;
    sup_->data_ = value;
  }
  size_++;
}

/**
 * @brief Удаление последнего элемента.
 */
template <class value_type>
void List<value_type>::pop_back() {
  if (tail_) {
    Node *tmp = tail_;
    tail_ = sup_->prev_ = tail_->prev_;
    tail_->next_ = sup_;
    delete tmp;
    size_--;
  }
}

/**
 * @brief Добавление элемента со значением value в начало списка.
 */
template <class value_type>
void List<value_type>::push_front(const_reference value) {
  if (!head_)
    initHeadAndTail(value);
  else {
    head_->prev_ = new Node(value, sup_, head_);
    head_ = head_->prev_;
    sup_->next_ = head_;
  }
  size_++;
}

/**
 * @brief Удаление первого элемента.
 */
template <class value_type>
void List<value_type>::pop_front() {
  if (head_) {
    Node *tmp = head_;
    head_ = sup_->next_ = head_->next_;
    head_->prev_ = sup_;
    delete tmp;
    size_--;
  }
}

/**
 * @brief Замена значений двух списков.
 *
 * @param other второй список
 */
template <class value_type>
void List<value_type>::swap(List &other) {
  s21::List<value_type> tmp = std::move(*this);
  *this = std::move(other);
  other = std::move(tmp);
}

/**
 * @brief Объединение двух списков.
 *
 * @param other второй список
 *
 * @note other очищается
 * @note this - отсортированный список (если аргументы были отсортированы)
 */
template <class value_type>
void List<value_type>::merge(List &other) {
  s21::List<value_type> tmp;
  auto iter = this->begin(), iter_other = other.begin();
  for (int i = 0; i < (int)(size_ + other.size_); i++) {
    if (iter_other == nullptr || (iter != nullptr && *iter < *iter_other)) {
      tmp.push_back(*iter);
      ++iter;
      if (iter == this->end()) iter = nullptr;
    } else {
      tmp.push_back(*iter_other);
      ++iter_other;
      if (iter_other == other.end()) iter_other = nullptr;
    }
  }
  this->clear();
  *this = std::move(tmp);
  other.clear();
}

/**
 * @brief Удаление элементов из other и их вставка в список
 * назначения, начиная с позиции pos.
 *
 * @param pos
 * @param other
 *
 * @note other очищается
 */
template <class value_type>
void List<value_type>::splice(const_iterator pos, List &other) {
  for (auto item : other) this->insert(pos, item);
  other.clear();
}

/**
 * @brief Разворачивает элементы списка.
 */
template <class value_type>
void List<value_type>::reverse() {
  Node *node = head_;
  for (size_type i = 0; i < size_; ++i) {
    std::swap(node->prev_, node->next_);
    node = node->prev_;
  }
  std::swap(this->head_, this->tail_);
  std::swap(sup_->prev_, sup_->next_);
}

/**
 * @brief Удаление из списка повторяющихся соседних элементов.
 */
template <class value_type>
void List<value_type>::unique() {
  for (auto iter = begin(); iter != end().iter_->prev_;) {
    if (*iter == iter.iter_->next_->data_) {
      Node *tmp = iter.iter_;
      tmp->prev_->next_ = tmp->next_;
      tmp->next_->prev_ = tmp->prev_;
      iter = tmp->prev_->next_;
      delete tmp;
      size_--;
    } else
      ++iter;
  }
}

/**
 * @brief Сортировка элемтов списка.
 */
template <class value_type>
void List<value_type>::sort() {
  for (int i = 0; i < (int)size_; i++) {
    for (auto iter = begin(); iter != end() - i - 1 + 1; ++iter) {
      if (*iter > iter.iter_->next_->data_)
        std::swap(iter.iter_->data_, iter.iter_->next_->data_);
    }
  }
}

/**
 * @brief Вставка элементов args на позицию перед итератором pos.
 *
 * @return итератор на последний добавленный элемент
 */
template <class value_type>
template <class... Args>
typename List<value_type>::iterator List<value_type>::insert_many(
    const_iterator pos, Args &&...args) {
  ListIterator tmp;
  for (auto item : {args...}) tmp = insert(pos, item);
  return tmp;
}

/**
 * @brief Добавление элементов args в конец списка.
 */
template <class value_type>
template <class... Args>
void List<value_type>::insert_many_back(Args &&...args) {
  for (auto item : {args...}) push_back(item);
}

/**
 * @brief Добавление элементов args в начало списка.
 */
template <class value_type>
template <class... Args>
void List<value_type>::insert_many_front(Args &&...args) {
  auto iter = begin();
  for (auto item : {args...}) insert(iter, item);
}

/**
 * @brief Конструктор, инициализирующий элемент списка.
 */
template <class value_type>
List<value_type>::Node::Node(value_type data, Node *prev, Node *next)
    : data_(data), prev_(prev), next_(next) {}

/**
 * @brief Конструктор, инициализирующий итератор.
 */
template <class value_type>
List<value_type>::ListIterator::ListIterator(Node *iter, bool sup)
    : iter_(iter), isSup_(sup) {}

/**
 * @brief Проверка на равенство итераторов.
 *
 * @param other
 *
 * @return bool value
 *
 * @note true - итераторы равны
 * @note false - итераторы неравны
 */
template <class value_type>
bool List<value_type>::ListIterator::operator==(const iterator &other) {
  return iter_ == other.iter_;
}

/**
 * @brief Проверка на неравенство итераторов.
 *
 * @param other
 *
 * @return bool value
 *
 * @note true - итераторы неравны
 * @note false - итераторы равны
 */
template <class value_type>
bool List<value_type>::ListIterator::operator!=(const iterator &other) {
  return iter_ != other.iter_;
}

/**
 * @brief Получение значений элемента, на который указывает итератор.
 *
 * @return value_type
 */
template <class value_type>
typename List<value_type>::reference
List<value_type>::ListIterator::operator*() {
  return iter_->data_;
}

/**
 * @brief Перемещение итератора вперед для обращения к следующему элементу.
 *
 * @return следующий итератор
 */
template <class value_type>
typename List<value_type>::iterator
List<value_type>::ListIterator::operator++() {
  if (iter_) iter_ = iter_->next_;
  return *this;
}

/**
 * @brief Перемещение итератора вперед на value.
 *
 * @param value число, на которое необходимо сдвинуть итератор.
 *
 * @return новый итератор
 */
template <class value_type>
typename List<value_type>::iterator List<value_type>::ListIterator::operator+(
    int value) {
  if (iter_)
    for (int i = 0; i < value; i++) iter_ = iter_->next_;
  return *this;
}

/**
 * @brief Перемещение итератора вперед для обращения к предыдущему элементу.
 *
 * @return предыдущий итератор
 */
template <class value_type>
typename List<value_type>::iterator
List<value_type>::ListIterator::operator--() {
  if (iter_) {
    if (isSup_) {
      iter_ = iter_->prev_;
      isSup_ = 0;
    }
    iter_ = iter_->prev_;
  }
  return *this;
}

/**
 * @brief Перемещение итератора назад на value.
 *
 * @param value число, на которое необходимо сдвинуть итератор.
 *
 * @return новый итератор
 */
template <class value_type>
typename List<value_type>::iterator List<value_type>::ListIterator::operator-(
    int value) {
  if (iter_) {
    if (isSup_) {
      iter_ = iter_->prev_;
      isSup_ = 0;
    }
    for (int i = 0; i < value; i++) iter_ = iter_->prev_;
  }
  return *this;
}

/**
 * @brief Конструктор, инициализирующий const итератор.
 */
template <class value_type>
List<value_type>::ListConstIterator::ListConstIterator(const iterator &iterator)
    : ListIterator(iterator) {}

/**
 * @brief Инициализация списка.
 *
 * @note размер списка - 0
 * @note sup_ - дополнительный элемент, находящийся между head_ и tail_.
 */
template <class value_type>
void List<value_type>::initList() {
  sup_ = new Node();
  sup_->prev_ = sup_->next_ = sup_;
}

/**
 * @brief Инициализация "головы" и "хвоста" списка.
 *
 * @param value значение элемента.
 */
template <class value_type>
void List<value_type>::initHeadAndTail(value_type value) {
  if (!sup_) initList();
  head_ = tail_ = new Node(value, sup_, sup_);
  sup_->next_ = head_;
  sup_->prev_ = tail_;
}
}  // namespace s21