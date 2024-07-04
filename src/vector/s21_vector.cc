#include "s21_vector.h"

namespace s21 {

/**
 * @brief Базовый конструктор, инициализирующий вектор.
 */
template <class value_type>
Vector<value_type>::Vector() : Array<value_type>(), capacity_(0){};

/**
 * @brief Параметризированный конструктор, инициализирующий вектор размером n.
 *
 * @param n размер вектора
 */
template <class value_type>
Vector<value_type>::Vector(size_type n) {
  reserve(n);
  this->size_ = n;
}

/**
 * @brief Конструктор, инициализирующий вектор, используя
 std::initializer_list.
 *
 * @param items initializer_list
 */
template <class value_type>
Vector<value_type>::Vector(std::initializer_list<value_type> const &items) {
  reserve(items.size());
  Array<value_type>::copy(items);
}

/**
 * @brief Конструктор копирования
 *
 * @param v копируемый вектор
 */
template <class value_type>
Vector<value_type>::Vector(const Vector &v)
    : Array<value_type>(v), capacity_(v.size()) {}

/**
 * @brief Конструктор переноса
 *
 * @param v переносимый вектор
 */
template <class value_type>
Vector<value_type>::Vector(Vector &&v)
    : Array<value_type>(v), capacity_(v.size()) {
  v.clear();
}

/**
 * @brief Деструктор
 */
template <class value_type>
Vector<value_type>::~Vector() {
  capacity_ = 0;
}

/**
 * @brief Оператор присваивания.
 *
 * @param v копируемый вектор
 *
 * @return скопированный вектор
 */
template <class value_type>
Vector<value_type> Vector<value_type>::operator=(Vector &&v) {
  Array<value_type>::clear();
  Array<value_type>::copy(v);
  v.clear();
  return *this;
}

/**
 * @return Максимально возможное количество элементов вектора.
 */
template <class value_type>
typename Vector<value_type>::size_type Vector<value_type>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(reference) / 2;
}

/**
 * @return Размер буффера.
 */
template <class value_type>
typename Vector<value_type>::size_type Vector<value_type>::capacity() {
  return capacity_;
}

/**
 * @brief Увеличение capacity_ до size.
 */
template <class value_type>
void Vector<value_type>::reserve(size_type size) {
  this->capacity_ = size;
  this->arr_ = static_cast<value_type *>(
      std::realloc(this->arr_, sizeof(value_type) * this->capacity_));
  for (int i = (int)this->size_; i < (int)this->capacity_; i++)
    this->arr_[i] = 0;
}

/**
 * @brief Уменьшение использования памяти за счет освобождения неиспользуемой
 * памяти.
 */
template <class value_type>
void Vector<value_type>::shrink_to_fit() {
  if ((int)this->capacity_ != (int)this->size_) capacity_ = this->size_;
}

/**
 * @brief Вставка элемента со значением value на позицию, на которую указывает
 * итератор pos.
 *
 * @return итератор на добавленный элемент
 */
template <class value_type>
typename Vector<value_type>::iterator Vector<value_type>::insert(
    iterator pos, const_reference value) {
  int index = pos - Array<value_type>::begin();
  if ((int)this->capacity_ <= (int)this->size_ + 1) reserve(capacity_ * 2);
  this->size_++;
  value_type newVal = value;
  for (auto iter = &this->arr_[index]; iter != Array<value_type>::end() + 1;
       ++iter)
    std::swap(newVal, *iter);
  return &this->arr_[index];
}

/**
 * @brief Удаление элемента, на который указывает итератор pos.
 */
template <class value_type>
void Vector<value_type>::erase(iterator pos) {
  int index = pos - Array<value_type>::begin();
  this->arr_[index] = 0;
  this->size_--;
  for (int i = index; i < (int)this->size_; i++)
    std::swap(this->arr_[i], this->arr_[i + 1]);
}

/**
 * @brief Удаление последнего элемента.
 */
template <class value_type>
void Vector<value_type>::pop_back() {
  this->arr_[this->size_ - 1] = 0;
  this->size_--;
}

/**
 * @brief Добавление элемента со значением value в конец вектора.
 */
template <class value_type>
void Vector<value_type>::push_back(const_reference value) {
  insert(Array<value_type>::end() + 1, value);
}

/**
 * @brief Замена значений двух векторов.
 *
 * @param other второй вектор
 */
template <class value_type>
void Vector<value_type>::swap(Vector &other) {
  s21::Vector<value_type> tmp = std::move(*this);
  *this = std::move(other);
  other = std::move(tmp);
}

/**
 * @brief Вставка элемента args перед итератором pos.
 *
 * @return итератор на последний добавленный элемент
 */
template <class value_type>
template <class... Args>
typename Vector<value_type>::iterator Vector<value_type>::insert_many(
    iterator pos, Args &&...args) {
  iterator tmp = --pos;
  for (auto item : {args...}) tmp = insert(++tmp, item);
  return tmp;
}

/**
 * @brief Добавление элемента со значением value в конец вектора.
 */
template <class value_type>
template <class... Args>
void Vector<value_type>::insert_many_back(Args &&...args) {
  for (auto item : {args...}) push_back(item);
}
}  // namespace s21