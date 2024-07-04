#include "s21_array.h"

namespace s21 {

/**
 * @brief Базовый конструктор, инициализирующий массив.
 */
template <class value_type, size_t N>
Array<value_type, N>::Array() : arr_(nullptr), size_(N) {
  arr_ = static_cast<value_type *>(std::calloc(N, sizeof(value_type)));
}

/**
 * @brief Конструктор, инициализирующий массив, используя std::initializer_list.
 *
 * @param items initializer_list
 */
template <class value_type, size_t N>
Array<value_type, N>::Array(std::initializer_list<value_type> const &items)
    : arr_(nullptr), size_(0) {
  if (N < items.size())
    throw std::invalid_argument("arr size less initializer_list size");
  copy(items);
}

/**
 * @brief Конструктор копирования
 *
 * @param a копируемый массив
 */
template <class value_type, size_t N>
Array<value_type, N>::Array(const Array &a) : arr_(nullptr) {
  copy(a);
}

/**
 * @brief Конструктор переноса
 *
 * @param a копируемый массив
 */
template <class value_type, size_t N>
Array<value_type, N>::Array(Array &&a) : arr_(nullptr) {
  copy(a);
}

/**
 * @brief Деструктор
 */
template <class value_type, size_t N>
Array<value_type, N>::~Array() {
  clear();
}

/**
 * @brief Оператор присваивания.
 *
 * @param a копируемый массив
 *
 * @return скопированный объект
 */
template <class value_type, size_t N>
Array<value_type, N> Array<value_type, N>::operator=(Array &&a) {
  copy(a);
  return *this;
}

/**
 * @brief Возвращение значения элемента массива, находящегося на позиции pos.
 *
 * @exception pos >= size()
 *
 * @return значение элемента на позиции pos
 */
template <class value_type, size_t N>
typename Array<value_type, N>::reference Array<value_type, N>::at(
    size_type pos) {
  if (pos >= size_) throw std::out_of_range("index > arr size");
  return arr_[pos];
}

/**
 * @brief Возвращение значения элемента массива, находящегося на позиции pos.
 *
 * @return значение элемента на позиции pos
 */
template <class value_type, size_t N>
typename Array<value_type, N>::reference Array<value_type, N>::operator[](
    size_type pos) {
  return arr_[pos];
}

/**
 * @brief Возвращение значения первого элемента массива.
 *
 * @return значения первого элемента
 */
template <class value_type, size_t N>
typename Array<value_type, N>::const_reference Array<value_type, N>::front() {
  return arr_[0];
}

/**
 * @brief Возвращение значения последнего элемента массива.
 *
 * @return значения последнего элемента
 */
template <class value_type, size_t N>
typename Array<value_type, N>::const_reference Array<value_type, N>::back() {
  return arr_[size_ - 1];
}

/**
 * @brief Возвращение адреса базового элемента массива.
 *
 * @return адрес базового элемента
 */
template <class value_type, size_t N>
typename Array<value_type, N>::iterator Array<value_type, N>::data() {
  return arr_;
}

/**
 * @brief Возвращение адреса первого элемента массива.
 *
 * @return адрес первого элемента
 */
template <class value_type, size_t N>
typename Array<value_type, N>::iterator Array<value_type, N>::begin() const {
  return arr_;
}

/**
 * @brief Возвращение адреса последнего элемента массива.
 *
 * @return адрес последнего элемента
 */
template <class value_type, size_t N>
typename Array<value_type, N>::iterator Array<value_type, N>::end() const {
  return arr_ + size_ - 1;
}

/**
 * @brief Проверка пустой ли массив.
 *
 * @return bool value
 *
 * @note true - список пустой
 * @note false - список непустой
 */
template <class value_type, size_t N>
bool Array<value_type, N>::empty() {
  return size_ ? false : true;
}

/**
 * @return Количество элементов массива.
 */
template <class value_type, size_t N>
typename Array<value_type, N>::size_type Array<value_type, N>::size() const {
  return size_;
}

/**
 * @return Максимально возможное количество элементов массива.
 */
template <class value_type, size_t N>
typename Array<value_type, N>::size_type Array<value_type, N>::max_size() {
  return size_;
}

/**
 * @brief Замена значений двух массивов.
 *
 * @param other второй массив
 */
template <class value_type, size_t N>
void Array<value_type, N>::swap(Array &other) {
  s21::Array<value_type, N> tmp = std::move(*this);
  *this = std::move(other);
  other = std::move(tmp);
}

/**
 * @brief Замена значений двух массивов.
 *
 * @param other второй массив
 */
template <class value_type, size_t N>
void Array<value_type, N>::fill(const_reference value) {
  for (int i = 0; i < (int)size(); i++) arr_[i] = value;
}

/**
 * @brief Копирование
 */
template <class value_type, size_t N>
template <typename Arr>
void Array<value_type, N>::copy(Arr &copyArr) {
  size_ = copyArr.size();
  if (!arr_)
    arr_ = static_cast<value_type *>(std::calloc(size_, sizeof(value_type)));
  std::copy(copyArr.begin(), copyArr.end(), arr_);
}

/**
 * @brief Удаление всех элементов массива.
 */
template <class value_type, size_t N>
void Array<value_type, N>::clear() {
  if (arr_) {
    free(arr_);
    arr_ = nullptr;
    size_ = 0;
  }
}
}  // namespace s21