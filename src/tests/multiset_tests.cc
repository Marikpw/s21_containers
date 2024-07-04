#include <gtest/gtest.h>

#include "../multiset/s21_multiset.h"

namespace std {
template <typename T>
bool operator==(const s21::multiset<T>& lhs, const std::multiset<T>& rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }

  auto lhs_copy = lhs;

  auto it_std = rhs.begin();
  auto it_s21 = lhs_copy.begin();
  for (; it_std != rhs.end(); ++it_std, ++it_s21) {
    if (*it_s21 != *it_std) {
      return false;
    }
  }
  return true;
}
}  // namespace std

namespace s21 {
template <typename T>
bool operator==(const s21::multiset<T>& lhs, const s21::multiset<T>& rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }

  auto it_rhs = rhs.begin();
  auto it_lhs = lhs.begin();

  for (; it_rhs != rhs.end(); ++it_rhs, ++it_lhs) {
    if (*it_lhs != *it_rhs) {
      return false;
    }
  }

  return true;
}
}  // namespace s21

TEST(MultisetTest, DefaultConstructor) {
  s21::multiset<int> int_multiset{};
  EXPECT_EQ(int_multiset.empty(), true);
}

TEST(MultisetTest, InsertAndCount) {
  s21::multiset<int> int_multiset = {1, 2, 3, 4};
  EXPECT_EQ(int_multiset.size(), 4);
}

TEST(MultisetTest, LargeSize) {
  s21::multiset<int> int_multiset{};
  for (int i = 0; i < 500; ++i) {
    int_multiset.insert(i);
  }
  EXPECT_EQ(int_multiset.size(), 500);
}

TEST(MultisetTest, Erase) {
  s21::multiset<int> int_multiset{};
  std::multiset<int> std_int_multiset{};
  for (int i = 0; i < 500; ++i) {
    int_multiset.insert(i);
    std_int_multiset.insert(i);
  }
  for (int i = 0; i < 500; i += 3) {
    int_multiset.erase(int_multiset.begin());
    std_int_multiset.erase(std_int_multiset.begin());
  }
  EXPECT_EQ(int_multiset, std_int_multiset);
}

TEST(MultisetTest, Find) {
  s21::multiset<int> int_multiset{};
  std::multiset<int> std_int_multiset{};

  for (int i = 0; i < 500; i += 5) {
    int_multiset.insert(i);
    std_int_multiset.insert(i);
  }

  auto finded = int_multiset.find(10);
  auto finded_std = std_int_multiset.find(10);

  int_multiset.erase(finded);
  std_int_multiset.erase(finded_std);

  EXPECT_EQ(int_multiset, std_int_multiset);
}

TEST(MultisetTest, Swap) {
  s21::multiset<int> int_multiset_1{1, 2, 3, 4};
  s21::multiset<int> int_multiset_2{4, 3, 2, 1};

  auto prev_1 = int_multiset_1;
  auto prev_2 = int_multiset_2;

  int_multiset_1.swap(int_multiset_2);

  EXPECT_EQ(int_multiset_1, prev_2);
  EXPECT_EQ(int_multiset_2, prev_1);
}

TEST(MultisetTest, Merge) {
  s21::multiset<int> int_multiset_1{1, 2, 3, 4};

  std::multiset<int> std_multiset{2, 3, 4, 5};
  s21::multiset<int> s21_multiset{2, 3, 4, 5};
  s21_multiset.merge(int_multiset_1);
  for (const auto elem : int_multiset_1) {
    std_multiset.insert(elem);
  }

  EXPECT_EQ(s21_multiset, std_multiset);
}

TEST(MultisetTest, Count) {
  s21::multiset<int> int_multiset{};
  for (size_t i = 0; i < 25; ++i) {
    int_multiset.insert(1);
  }
  EXPECT_EQ(int_multiset.count(1), 25);
}

TEST(MultisetTest, Constain) {
  s21::multiset<int> int_multiset{};
  int_multiset.insert(10);
  EXPECT_EQ(int_multiset.contains(10), true);
  EXPECT_EQ(int_multiset.contains(1), false);
}

TEST(MultisetTest, EqualRange) {
  s21::multiset<int> int_multiset = {1, 2, 2, 3, 4, 4, 4, 5};
  auto range = int_multiset.equal_range(4);
  std::multiset<int> std_multiset = {1, 2, 2, 3, 4, 4, 4, 5};
  auto std_range = std_multiset.equal_range(4);

  // Проверка наличия диапазона
  EXPECT_EQ(*range.first, *std_range.first);
  EXPECT_EQ(*range.second, *std_range.second);
}

TEST(MultisetTest, LowerBound) {
  s21::multiset<int> int_multiset = {1, 2, 2, 3, 4, 4, 4, 5};
  auto it = int_multiset.lower_bound(3);
  EXPECT_EQ(*it, 3);
}

TEST(MultisetTest, UpperBound) {
  s21::multiset<int> int_multiset = {1, 2, 2, 3, 4, 4, 4, 5};
  auto it = int_multiset.upper_bound(3);
  EXPECT_EQ(*it, 4);
}

TEST(MultisetTest, InsertMany) {
  s21::multiset<int> int_multiset;

  auto result = int_multiset.insert_many(1, 2, 3, 4, 5);
  EXPECT_EQ(result.size(), 5);  // Ожидаем, что 5 элементов были вставлены
  for (const auto& pair : result) {
    EXPECT_TRUE(
        pair.second);  // Ожидаем, что второй элемент пары (булевое значение)
                       // будет true, что означает успешную вставку
  }

  // Проверка, что элементы были действительно вставлены и содержатся в
  // множестве
  for (int i = 1; i <= 5; ++i) {
    EXPECT_TRUE(int_multiset.contains(i));
  }
}
