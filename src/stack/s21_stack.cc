#include "s21_stack.h"

namespace s21 {

/**
 * @brief Базовый конструктор, инициализирующий стек.
 */
template <class value_type, class Container>
Stack<value_type, Container>::Stack() {}

/**
 * @brief Конструктор, инициализирующий стек, используя std::initializer_list.
 *
 * @param items initializer_list
 */
template <class value_type, class Container>
Stack<value_type, Container>::Stack(
    std::initializer_list<value_type> const &items)
    : baseClass_(items) {}

/**
 * @brief Конструктор копирования
 *
 * @param s копируемый стек
 */
template <class value_type, class Container>
Stack<value_type, Container>::Stack(const Stack &s)
    : baseClass_(s.baseClass_) {}

/**
 * @brief Конструктор переноса
 *
 * @param s переносимый стек
 */
template <class value_type, class Container>
Stack<value_type, Container>::Stack(Stack &&s)
    : baseClass_(std::move(s.baseClass_)) {}

/**
 * @brief Деструктор
 */
template <class value_type, class Container>
Stack<value_type, Container>::~Stack() {}

/**
 * @brief Оператор присваивания.
 *
 * @param s копируемый стек
 *
 * @return скопированный объект
 */
template <class value_type, class Container>
Stack<value_type, Container> Stack<value_type, Container>::operator=(
    Stack &&s) {
  baseClass_ = std::move(s.baseClass_);
  return *this;
}

/**
 * @brief Возвращение значения последнего элемента стека.
 *
 * @return значение последнего элемента
 */
template <class value_type, class Container>
typename Stack<value_type, Container>::const_reference
Stack<value_type, Container>::top() {
  return baseClass_.back();
}

/**
 * @brief Проверка пустой ли стек.
 *
 * @return bool value
 *
 * @note true - стек пустой
 * @note false - стек непустой
 */
template <class value_type, class Container>
bool Stack<value_type, Container>::empty() {
  return baseClass_.empty();
}

/**
 * @return Количество элементов стека.
 */
template <class value_type, class Container>
typename Stack<value_type, Container>::size_type
Stack<value_type, Container>::size() {
  return baseClass_.size();
}

/**
 * @return Добавление элемента со значением value.
 */
template <class value_type, class Container>
void Stack<value_type, Container>::push(const_reference value) {
  baseClass_.push_back(value);
}

/**
 * @return Удаление элемента.
 */
template <class value_type, class Container>
void Stack<value_type, Container>::pop() {
  baseClass_.pop_back();
}

/**
 * @brief Замена значений двух стеков.
 *
 * @param other второй стек
 */
template <class value_type, class Container>
void Stack<value_type, Container>::swap(Stack &other) {
  baseClass_.swap(other.baseClass_);
}

/**
 * @return Добавление элементов args.
 */
template <class value_type, class Container>
template <class... Args>
void Stack<value_type, Container>::insert_many_front(Args &&...args) {
  for (auto item : {args...}) baseClass_.push_back(item);
}
}  // namespace s21