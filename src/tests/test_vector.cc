#include "tests.h"

class Test_vector : public ::testing::Test {
 public:
  std::vector<int> std_empty_vector;
  s21::Vector<int> s21_empty_vector;

  std::vector<int> std_vector_int{3, -5, -3, -3, 0, 3, -10, 5, 5};
  std::vector<int> std_vector_int2{-10, -8, -1, 1, 8, 10, 15, -4, 6};
  s21::Vector<int> s21_vector_int{3, -5, -3, -3, 0, 3, -10, 5, 5};
  s21::Vector<int> s21_vector_int2{-10, -8, -1, 1, 8, 10, 15, -4, 6};

  std::vector<double> std_vector_double{-8.52, -5.83, -2.54, 0.5,
                                        0.5,   6.7,   8.91};
  s21::Vector<double> s21_vector_double{-8.52, -5.83, -2.54, 0.5,
                                        0.5,   6.7,   8.91};

  std::vector<char> std_vector_char{'c', 'o', 'n', 'N', 'T', 'a', 'a',
                                    'i', 'i', 'n', 'n', 'E', 'R', 's'};
  s21::Vector<char> s21_vector_char{'c', 'o', 'n', 'N', 'T', 'a', 'a',
                                    'i', 'i', 'n', 'n', 'E', 'R', 's'};

  // std::vector<std::string> std_vector_str{
  //     "containers library", "tests for containers",
  //     "collection of class templates", "containers library"};
  // s21::Vector<std::string> s21_vector_str{
  //     "containers library", "tests for containers",
  //     "collection of class templates", "containers library"};
};

TEST_F(Test_vector, default_constructor) {
  EXPECT_EQ(std_empty_vector.size(), s21_empty_vector.size());
  EXPECT_EQ(std_empty_vector.empty(), s21_empty_vector.empty());
}

TEST_F(Test_vector, initializerVector_constructor_int) {
  EXPECT_EQ(std_vector_int.size(), s21_vector_int.size());
  auto iter = std_vector_int.begin();
  for (auto item : s21_vector_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
TEST_F(Test_vector, initializerVector_constructor_double) {
  EXPECT_EQ(std_vector_double.size(), s21_vector_double.size());
  auto iter = std_vector_double.begin();
  for (auto item : s21_vector_double) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
TEST_F(Test_vector, initializerVector_constructor_char) {
  EXPECT_EQ(std_vector_char.size(), s21_vector_char.size());
  auto iter = std_vector_char.begin();
  for (auto item : s21_vector_char) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
// TEST_F(Test_vector, initializerVector_constructor_str) {
//   EXPECT_EQ(std_vector_str.size(), s21_vector_str.size());
//   auto iter = std_vector_str.begin();
//   for (auto item : s21_vector_str) {
//     EXPECT_EQ(item, *iter);
//     ++iter;
//   }
// }

TEST_F(Test_vector, copy_constructor) {
  s21::Vector<int> s21_vector = s21_vector_int;
  std::vector<int> std_vector = std_vector_int;
  EXPECT_EQ(s21_vector_int.size(), s21_vector.size());
  EXPECT_EQ(std_vector.size(), s21_vector.size());
  EXPECT_EQ(s21_vector_int.empty(), false);
  auto iter_s21 = s21_vector_int.begin();
  auto iter_std = std_vector_int.begin();
  for (auto item : s21_vector) {
    EXPECT_EQ(item, *iter_s21);
    EXPECT_EQ(item, *iter_std);
    ++iter_s21;
    ++iter_std;
  }
}

TEST_F(Test_vector, move_constructor__operator_overload) {
  s21::Vector<int> s21_vector = std::move(s21_vector_int);
  std::vector<int> std_vector = std::move(std_vector_int);
  EXPECT_EQ(std_vector.size(), s21_vector.size());
  auto iter = std_vector.begin();
  for (auto item : s21_vector) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
  EXPECT_EQ(std_vector_int.size(), s21_vector_int.size());
  EXPECT_EQ(s21_vector_int.empty(), true);

  s21_vector_int = std::move(s21_vector);
  std_vector_int = std::move(std_vector);
  EXPECT_EQ(std_vector_int.size(), s21_vector_int.size());
  iter = std_vector_int.begin();
  for (auto item : s21_vector_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
  EXPECT_EQ(std_vector.size(), s21_vector.size());
  EXPECT_EQ(s21_vector.empty(), true);
}

TEST_F(Test_vector, at) {
  for (int i = 0; i < (int)std_vector_int.size(); i++)
    EXPECT_EQ(std_vector_int.at(i), s21_vector_int.at(i));
}
TEST_F(Test_vector, at_throw) { ASSERT_ANY_THROW(s21_vector_int.at(25)); }

TEST_F(Test_vector, operator_access_specified) {
  for (int i = 0; i < (int)std_vector_int.size(); i++)
    EXPECT_EQ(std_vector_int[i], s21_vector_int[i]);
}

TEST_F(Test_vector, front) {
  EXPECT_EQ(s21_vector_int.front(), std_vector_int.front());
  EXPECT_EQ(s21_vector_double.front(), std_vector_double.front());
  EXPECT_EQ(s21_vector_char.front(), std_vector_char.front());
  // EXPECT_EQ(s21_vector_str.front(), std_vector_str.front());
}
TEST_F(Test_vector, back) {
  EXPECT_EQ(s21_vector_int.back(), std_vector_int.back());
  EXPECT_EQ(s21_vector_double.back(), std_vector_double.back());
  EXPECT_EQ(s21_vector_char.back(), std_vector_char.back());
  // EXPECT_EQ(s21_vector_str.back(), std_vector_str.back());
}

TEST_F(Test_vector, data) {
  int s21_num = *s21_vector_int.data();
  int std_num = *std_vector_int.data();
  EXPECT_EQ(s21_num, std_num);
}
TEST_F(Test_vector, begin) {
  int s21_num = *s21_vector_int.begin();
  int std_num = *std_vector_int.begin();
  EXPECT_EQ(s21_num, std_num);
}
TEST_F(Test_vector, end) {
  int s21_num = *s21_vector_int.end();
  int std_num = *(std_vector_int.end() - 1);
  EXPECT_EQ(s21_num, std_num);
}

TEST_F(Test_vector, empty) {
  EXPECT_EQ(s21_empty_vector.empty(), true);
  EXPECT_EQ(s21_vector_int.empty(), false);
}
TEST_F(Test_vector, size) {
  EXPECT_EQ(std_empty_vector.size(), s21_empty_vector.size());
  EXPECT_EQ(std_vector_int.size(), s21_vector_int.size());
  EXPECT_EQ(std_vector_double.size(), s21_vector_double.size());
  EXPECT_EQ(std_vector_char.size(), s21_vector_char.size());
  // EXPECT_EQ(std_vector_str.size(), s21_vector_str.size());
}
TEST_F(Test_vector, max_size) {
  EXPECT_EQ(std_empty_vector.max_size(), s21_empty_vector.max_size());
  EXPECT_EQ(std_vector_int.max_size(), s21_vector_int.max_size());
  EXPECT_EQ(std_vector_double.max_size(), s21_vector_double.max_size());
  EXPECT_EQ(std_vector_char.max_size(), s21_vector_char.max_size());
  // EXPECT_EQ(std_vector_str.max_size(), s21_vector_str.max_size());
}
TEST_F(Test_vector, capacity) {
  EXPECT_EQ(std_empty_vector.capacity(), s21_empty_vector.capacity());
  EXPECT_EQ(std_vector_int.capacity(), s21_vector_int.capacity());
  EXPECT_EQ(std_vector_double.capacity(), s21_vector_double.capacity());
  EXPECT_EQ(std_vector_char.capacity(), s21_vector_char.capacity());
  // EXPECT_EQ(std_vector_str.capacity(), s21_vector_str.capacity());
}

TEST_F(Test_vector, reserve) {
  std_vector_int.reserve(15);
  s21_vector_int.reserve(15);
  EXPECT_EQ(std_vector_int.capacity(), s21_vector_int.capacity());

  auto iter = std_vector_int.begin();
  for (auto item : s21_vector_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}

TEST_F(Test_vector, shrink_to_fit) {
  std_vector_int.reserve(15);
  s21_vector_int.reserve(15);
  std_vector_int.shrink_to_fit();
  s21_vector_int.shrink_to_fit();
  EXPECT_EQ(std_vector_int.capacity(), s21_vector_int.capacity());

  auto iter = std_vector_int.begin();
  for (auto item : s21_vector_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}

TEST_F(Test_vector, insert) {
  std_vector_int.insert(std_vector_int.begin(), 15);
  s21_vector_int.insert(s21_vector_int.begin(), 15);
  EXPECT_EQ(std_vector_int.capacity(), s21_vector_int.capacity());
  EXPECT_EQ(std_vector_int.size(), s21_vector_int.size());

  auto iter = std_vector_int.begin();
  for (auto item : s21_vector_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}

TEST_F(Test_vector, erase) {
  std_vector_int.erase(std_vector_int.begin());
  s21_vector_int.erase(s21_vector_int.begin());
  EXPECT_EQ(std_vector_int.capacity(), s21_vector_int.capacity());
  EXPECT_EQ(std_vector_int.size(), s21_vector_int.size());

  auto iter = std_vector_int.begin();
  for (auto item : s21_vector_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}

TEST_F(Test_vector, pop_back) {
  std_vector_int.pop_back();
  s21_vector_int.pop_back();
  EXPECT_EQ(std_vector_int.capacity(), s21_vector_int.capacity());
  EXPECT_EQ(std_vector_int.size(), s21_vector_int.size());

  auto iter = std_vector_int.begin();
  for (auto item : s21_vector_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}

TEST_F(Test_vector, push_back) {
  std_vector_int.push_back(10);
  s21_vector_int.push_back(10);
  EXPECT_EQ(std_vector_int.capacity(), s21_vector_int.capacity());
  EXPECT_EQ(std_vector_int.size(), s21_vector_int.size());

  auto iter = std_vector_int.begin();
  for (auto item : s21_vector_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}

TEST_F(Test_vector, swap) {
  std_vector_int.swap(std_vector_int2);
  s21_vector_int.swap(s21_vector_int2);

  auto iter = std_vector_int.begin();
  for (auto item : s21_vector_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
  iter = std_vector_int2.begin();
  for (auto item : s21_vector_int2) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}

TEST_F(Test_vector, insert_many) {
  std_vector_int.insert(std_vector_int.begin(), 21);
  std_vector_int.insert(std_vector_int.begin(), 18);
  std_vector_int.insert(std_vector_int.begin(), 15);
  s21_vector_int.insert_many(s21_vector_int.begin(), 15, 18, 21);
  EXPECT_EQ(std_vector_int.capacity(), s21_vector_int.capacity());
  EXPECT_EQ(std_vector_int.size(), s21_vector_int.size());

  auto iter = std_vector_int.begin();
  for (auto item : s21_vector_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}

TEST_F(Test_vector, insert_many_back) {
  std_vector_int.insert(std_vector_int.end(), 15);
  std_vector_int.insert(std_vector_int.end(), 18);
  std_vector_int.insert(std_vector_int.end(), 21);
  s21_vector_int.insert_many_back(15, 18, 21);
  EXPECT_EQ(std_vector_int.capacity(), s21_vector_int.capacity());
  EXPECT_EQ(std_vector_int.size(), s21_vector_int.size());

  auto iter = std_vector_int.begin();
  for (auto item : s21_vector_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}