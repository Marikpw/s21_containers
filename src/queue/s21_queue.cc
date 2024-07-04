#include "s21_queue.h"

namespace s21 {

/**
 * @brief Базовый конструктор, инициализирующий очередь.
 */
template <class value_type, class Container>
Queue<value_type, Container>::Queue() {}

/**
 * @brief Конструктор, инициализирующий очередь, используя
 * std::initializer_list.
 *
 * @param items initializer_list
 */
template <class value_type, class Container>
Queue<value_type, Container>::Queue(
    std::initializer_list<value_type> const &items)
    : baseClass_(items) {}

/**
 * @brief Конструктор копирования
 *
 * @param q копируемая очередь
 */
template <class value_type, class Container>
Queue<value_type, Container>::Queue(const Queue &q)
    : baseClass_(q.baseClass_) {}

/**
 * @brief Конструктор переноса
 *
 * @param q переносимая очередь
 */
template <class value_type, class Container>
Queue<value_type, Container>::Queue(Queue &&q)
    : baseClass_(std::move(q.baseClass_)) {}

/**
 * @brief Деструктор
 */
template <class value_type, class Container>
Queue<value_type, Container>::~Queue() {}

/**
 * @brief Оператор присваивания.
 *
 * @param q копируемая очередь
 *
 * @return скопированный объект
 */
template <class value_type, class Container>
Queue<value_type, Container> Queue<value_type, Container>::operator=(
    Queue &&q) {
  baseClass_ = std::move(q.baseClass_);
  return *this;
}

/**
 * @brief Возвращение значения первого элемента очереди.
 *
 * @return значение первого элемента
 */
template <class value_type, class Container>
typename Queue<value_type, Container>::const_reference
Queue<value_type, Container>::front() {
  return baseClass_.front();
}

/**
 * @brief Возвращение значения последнего элемента очереди.
 *
 * @return значение последнего элемента
 */
template <class value_type, class Container>
typename Queue<value_type, Container>::const_reference
Queue<value_type, Container>::back() {
  return baseClass_.back();
}

/**
 * @brief Проверка пустая ли очередь.
 *
 * @return bool value
 *
 * @note true - очередь пустая
 * @note false - очередь непустая
 */
template <class value_type, class Container>
bool Queue<value_type, Container>::empty() {
  return baseClass_.empty();
}

/**
 * @return Количество элементов очереди.
 */
template <class value_type, class Container>
typename Queue<value_type, Container>::size_type
Queue<value_type, Container>::size() {
  return baseClass_.size();
}

/**
 * @return Добавление элемента со значением value.
 */
template <class value_type, class Container>
void Queue<value_type, Container>::push(const_reference value) {
  baseClass_.push_back(value);
}

/**
 * @return Удаление элемента.
 */
template <class value_type, class Container>
void Queue<value_type, Container>::pop() {
  baseClass_.pop_front();
}

/**
 * @brief Замена значений двух очередей.
 *
 * @param other вторая очередь
 */
template <class value_type, class Container>
void Queue<value_type, Container>::swap(Queue &other) {
  baseClass_.swap(other.baseClass_);
}

/**
 * @return Добавление элементов args.
 */
template <class value_type, class Container>
template <class... Args>
void Queue<value_type, Container>::insert_many_back(Args &&...args) {
  for (auto item : {args...}) baseClass_.push_back(item);
}
}  // namespace s21