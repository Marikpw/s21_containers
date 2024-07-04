#include "tests.h"

class Test_array : public ::testing::Test {
 public:
  std::array<int, 0> std_empty_array;
  s21::Array<int> s21_empty_array;

  std::array<int, 9> std_array_int{3, -5, -3, -3, 0, 3, -10, 5, 5};
  std::array<int, 9> std_array_int2{-10, -8, -1, 1, 8, 10, 15, -4, 6};
  s21::Array<int, 9> s21_array_int{3, -5, -3, -3, 0, 3, -10, 5, 5};
  s21::Array<int, 9> s21_array_int2{-10, -8, -1, 1, 8, 10, 15, -4, 6};

  std::array<double, 7> std_array_double{-8.52, -5.83, -2.54, 0.5,
                                         0.5,   6.7,   8.91};
  s21::Array<double, 7> s21_array_double{-8.52, -5.83, -2.54, 0.5,
                                         0.5,   6.7,   8.91};

  std::array<char, 14> std_array_char{'c', 'o', 'n', 'N', 'T', 'a', 'a',
                                      'i', 'i', 'n', 'n', 'E', 'R', 's'};
  s21::Array<char, 14> s21_array_char{'c', 'o', 'n', 'N', 'T', 'a', 'a',
                                      'i', 'i', 'n', 'n', 'E', 'R', 's'};

  // std::array<std::string, 4> std_array_str{
  //     "containers library", "tests for containers",
  //     "collection of class templates", "containers library"};
  // s21::Array<std::string, 4> s21_array_str{
  //     "containers library", "tests for containers",
  //     "collection of class templates", "containers library"};
};

TEST_F(Test_array, default_constructor) {
  EXPECT_EQ(std_empty_array.size(), s21_empty_array.size());
  EXPECT_EQ(std_empty_array.empty(), s21_empty_array.empty());
}

TEST_F(Test_array, initializerArray_constructor_int) {
  EXPECT_EQ(std_array_int.size(), s21_array_int.size());
  auto iter = std_array_int.begin();
  for (auto item : s21_array_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
TEST_F(Test_array, initializerArray_constructor_double) {
  EXPECT_EQ(std_array_double.size(), s21_array_double.size());
  auto iter = std_array_double.begin();
  for (auto item : s21_array_double) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
TEST_F(Test_array, initializerArray_constructor_char) {
  EXPECT_EQ(std_array_char.size(), s21_array_char.size());
  auto iter = std_array_char.begin();
  for (auto item : s21_array_char) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
// TEST_F(Test_array, initializerArray_constructor_str) {
// EXPECT_EQ(4, std_array_str.size());
// auto iter = std_array_str.begin();
// for (auto item : s21_array_str) {
//   EXPECT_EQ(item, *iter);
//   ++iter;
// }
// }

TEST_F(Test_array, copy_constructor) {
  s21::Array<int, 9> s21_array = s21_array_int;
  std::array<int, 9> std_array = std_array_int;
  EXPECT_EQ(s21_array_int.size(), s21_array.size());
  EXPECT_EQ(std_array.size(), s21_array.size());
  EXPECT_EQ(s21_array_int.empty(), false);
  auto iter_s21 = s21_array_int.begin();
  auto iter_std = std_array_int.begin();
  for (auto item : s21_array) {
    EXPECT_EQ(item, *iter_s21);
    EXPECT_EQ(item, *iter_std);
    ++iter_s21;
    ++iter_std;
  }
}

TEST_F(Test_array, move_constructor__operator_overload) {
  s21::Array<int, 9> s21_array = std::move(s21_array_int);
  std::array<int, 9> std_array = std::move(std_array_int);
  EXPECT_EQ(std_array.size(), s21_array.size());
  auto iter = std_array.begin();
  for (auto item : s21_array) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
  EXPECT_EQ(std_array_int.size(), s21_array_int.size());
  EXPECT_EQ(s21_array_int.empty(), false);

  s21_array_int = std::move(s21_array);
  std_array_int = std::move(std_array);
  EXPECT_EQ(std_array_int.size(), s21_array_int.size());
  iter = std_array_int.begin();
  for (auto item : s21_array_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
  EXPECT_EQ(std_array.size(), s21_array.size());
  EXPECT_EQ(s21_array.empty(), false);
}

TEST_F(Test_array, at) {
  for (int i = 0; i < (int)std_array_int.size(); i++)
    EXPECT_EQ(std_array_int.at(i), s21_array_int.at(i));
}
TEST_F(Test_array, at_throw) { ASSERT_ANY_THROW(s21_array_int.at(25)); }

TEST_F(Test_array, operator_access_specified) {
  for (int i = 0; i < (int)std_array_int.size(); i++)
    EXPECT_EQ(std_array_int[i], s21_array_int[i]);
}

TEST_F(Test_array, front) {
  EXPECT_EQ(s21_array_int.front(), std_array_int.front());
  EXPECT_EQ(s21_array_double.front(), std_array_double.front());
  EXPECT_EQ(s21_array_char.front(), std_array_char.front());
  // EXPECT_EQ(s21_array_str.front(), std_array_str.front());
}
TEST_F(Test_array, back) {
  EXPECT_EQ(s21_array_int.back(), std_array_int.back());
  EXPECT_EQ(s21_array_double.back(), std_array_double.back());
  EXPECT_EQ(s21_array_char.back(), std_array_char.back());
  // EXPECT_EQ(s21_array_str.back(), std_array_str.back());
}

TEST_F(Test_array, data) {
  int s21_num = *s21_array_int.data();
  int std_num = *std_array_int.data();
  EXPECT_EQ(s21_num, std_num);
}
TEST_F(Test_array, begin) {
  int s21_num = *s21_array_int.begin();
  int std_num = *std_array_int.begin();
  EXPECT_EQ(s21_num, std_num);
}
TEST_F(Test_array, end) {
  int s21_num = *s21_array_int.end();
  int std_num = *(std_array_int.end() - 1);
  EXPECT_EQ(s21_num, std_num);
}

TEST_F(Test_array, empty) {
  EXPECT_EQ(s21_empty_array.empty(), true);
  EXPECT_EQ(s21_array_int.empty(), false);
}
TEST_F(Test_array, size) {
  EXPECT_EQ(std_empty_array.size(), s21_empty_array.size());
  EXPECT_EQ(std_array_int.size(), s21_array_int.size());
  EXPECT_EQ(std_array_double.size(), s21_array_double.size());
  EXPECT_EQ(std_array_char.size(), s21_array_char.size());
  // EXPECT_EQ(std_array_str.size(), s21_array_str.size());
}
TEST_F(Test_array, max_size) {
  EXPECT_EQ(std_empty_array.max_size(), s21_empty_array.max_size());
  EXPECT_EQ(std_array_int.max_size(), s21_array_int.max_size());
  EXPECT_EQ(std_array_double.max_size(), s21_array_double.max_size());
  EXPECT_EQ(std_array_char.max_size(), s21_array_char.max_size());
  // EXPECT_EQ(std_array_str.max_size(), s21_array_str.max_size());
}

TEST_F(Test_array, swap) {
  std_array_int.swap(std_array_int2);
  s21_array_int.swap(s21_array_int2);

  auto iter = std_array_int.begin();
  for (auto item : s21_array_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
  iter = std_array_int2.begin();
  for (auto item : s21_array_int2) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}

TEST_F(Test_array, fill) {
  s21::Array<int, 9> s21_array;
  std::array<int, 9> std_array;

  s21_array.fill(5);
  std_array.fill(5);

  auto iter = std_array.begin();
  for (auto item : s21_array) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }

  s21_array_int.fill(1);
  std_array_int.fill(1);

  iter = std_array_int.begin();
  for (auto item : s21_array_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}