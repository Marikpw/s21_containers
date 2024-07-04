#include "tests.h"

class Test_list : public ::testing::Test {
 public:
  std::list<int> std_empty_list;
  s21::List<int> s21_empty_list;

  std::list<int> std_list_int{3, -5, -3, -3, 0, 3, -10, 5, 5};
  std::list<int> std_list_int2{-10, -8, -1, 1, 8, 10};
  s21::List<int> s21_list_int{3, -5, -3, -3, 0, 3, -10, 5, 5};
  s21::List<int> s21_list_int2{-10, -8, -1, 1, 8, 10};

  std::list<double> std_list_double{-8.52, -5.83, -2.54, 0.5, 0.5, 6.7, 8.91};
  s21::List<double> s21_list_double{-8.52, -5.83, -2.54, 0.5, 0.5, 6.7, 8.91};

  std::list<char> std_list_char{'c', 'o', 'n', 'N', 'T', 'a', 'a',
                                'i', 'i', 'n', 'n', 'E', 'R', 's'};
  s21::List<char> s21_list_char{'c', 'o', 'n', 'N', 'T', 'a', 'a',
                                'i', 'i', 'n', 'n', 'E', 'R', 's'};

  std::list<std::string> std_list_str{
      "containers library", "tests for containers",
      "collection of class templates", "containers library"};
  s21::List<std::string> s21_list_str{
      "containers library", "tests for containers",
      "collection of class templates", "containers library"};
};

TEST_F(Test_list, default_constructor) {
  EXPECT_EQ(std_empty_list.size(), s21_empty_list.size());
  EXPECT_EQ(std_empty_list.empty(), s21_empty_list.empty());
}

TEST_F(Test_list, parameterized_constructor) {
  s21::List<int> s21_list(5);
  std::list<int> std_list(5);
  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST_F(Test_list, initializerList_constructor_int) {
  EXPECT_EQ(std_list_int.size(), s21_list_int.size());
  auto iter = std_list_int.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
TEST_F(Test_list, initializerList_constructor_double) {
  EXPECT_EQ(std_list_double.size(), s21_list_double.size());
  auto iter = std_list_double.begin();
  for (auto item : s21_list_double) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
TEST_F(Test_list, initializerList_constructor_char) {
  EXPECT_EQ(std_list_char.size(), s21_list_char.size());
  auto iter = std_list_char.begin();
  for (auto item : s21_list_char) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
TEST_F(Test_list, initializerList_constructor_str) {
  EXPECT_EQ(std_list_str.size(), s21_list_str.size());
  auto iter = std_list_str.begin();
  for (auto item : s21_list_str) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}

TEST_F(Test_list, copy_constructor) {
  s21::List<int> s21_list = s21_list_int;
  std::list<int> std_list = std_list_int;
  EXPECT_EQ(s21_list_int.size(), s21_list.size());
  EXPECT_EQ(std_list_int.size(), s21_list.size());
  EXPECT_EQ(s21_list_int.empty(), false);
  auto iter_s21 = s21_list_int.begin();
  auto iter_std = std_list_int.begin();
  for (auto item : s21_list) {
    EXPECT_EQ(item, *iter_s21);
    EXPECT_EQ(item, *iter_std);
    ++iter_s21;
    ++iter_std;
  }
}

TEST_F(Test_list, move_constructor__operator_overload) {
  s21::List<int> s21_list = std::move(s21_list_int);
  std::list<int> std_list = std::move(std_list_int);
  EXPECT_EQ(std_list.size(), s21_list.size());
  auto iter = std_list.begin();
  for (auto item : s21_list) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
  EXPECT_EQ(std_list_int.size(), s21_list_int.size());
  EXPECT_EQ(s21_list_int.empty(), true);

  s21_list_int = std::move(s21_list);
  std_list_int = std::move(std_list);
  EXPECT_EQ(std_list_int.size(), s21_list_int.size());
  iter = std_list_int.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
  EXPECT_EQ(std_list.size(), s21_list.size());
  EXPECT_EQ(s21_list.empty(), true);
}

TEST_F(Test_list, front__back) {
  EXPECT_EQ(s21_list_int.front(), std_list_int.front());
  EXPECT_EQ(s21_list_double.front(), std_list_double.front());
  EXPECT_EQ(s21_list_char.front(), std_list_char.front());
  EXPECT_EQ(s21_list_str.front(), std_list_str.front());

  EXPECT_EQ(s21_list_int.back(), std_list_int.back());
  EXPECT_EQ(s21_list_double.back(), std_list_double.back());
  EXPECT_EQ(s21_list_char.back(), std_list_char.back());
  EXPECT_EQ(s21_list_str.back(), std_list_str.back());
}
TEST_F(Test_list, begin__end) {
  auto iter_std = std_list_int.begin();
  auto iter_s21 = s21_list_int.begin();
  EXPECT_EQ(*iter_std, *iter_s21);

  iter_std = --std_list_int.end();
  iter_s21 = s21_list_int.end();
  EXPECT_EQ(*iter_std, *iter_s21);
}

TEST_F(Test_list, empty) {
  EXPECT_EQ(s21_empty_list.empty(), true);
  EXPECT_EQ(s21_list_int.empty(), false);
}
TEST_F(Test_list, size) {
  EXPECT_EQ(std_empty_list.size(), s21_empty_list.size());
  EXPECT_EQ(std_list_int.size(), s21_list_int.size());
  EXPECT_EQ(std_list_double.size(), s21_list_double.size());
  EXPECT_EQ(std_list_char.size(), s21_list_char.size());
  EXPECT_EQ(std_list_str.size(), s21_list_str.size());
}
TEST_F(Test_list, max_size) {
  EXPECT_EQ(std_empty_list.max_size(), s21_empty_list.max_size());
  EXPECT_EQ(std_list_int.max_size(), s21_list_int.max_size());
  EXPECT_EQ(std_list_double.max_size(), s21_list_double.max_size());
  EXPECT_EQ(std_list_char.max_size(), s21_list_char.max_size());
  EXPECT_EQ(std_list_str.max_size(), s21_list_str.max_size());
}

TEST_F(Test_list, clear) {
  s21::List<int> s21_list = s21_list_int;
  std::list<int> std_list = std_list_int;
  s21_list.clear();
  std_list.clear();
  EXPECT_EQ(std_list.size(), s21_list.size());
  EXPECT_EQ(s21_list.empty(), true);
}

TEST_F(Test_list, insert_begin) {
  auto iter_std = std_list_int.begin();
  auto iter_s21 = s21_list_int.begin();

  auto iter_std_res = std_list_int.insert(iter_std, 5);
  auto iter_s21_res = s21_list_int.insert(iter_s21, 5);

  EXPECT_EQ(*iter_std_res, *iter_s21_res);
  auto iter = std_list_int.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
TEST_F(Test_list, insert_end) {
  auto iter_std = std_list_int.end();
  auto iter_s21 = s21_list_int.end();

  auto iter_std_res = std_list_int.insert(iter_std, 15);
  auto iter_s21_res = s21_list_int.insert(iter_s21, 15);

  EXPECT_EQ(*iter_std_res, *iter_s21_res);
  auto iter = std_list_int.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
TEST_F(Test_list, insert) {
  auto iter_std = std_list_int.begin();
  auto iter_s21 = s21_list_int.begin();

  auto iter_std_res = std_list_int.insert(++iter_std, -10);
  auto iter_s21_res = s21_list_int.insert(++iter_s21, -10);

  EXPECT_EQ(*iter_std_res, *iter_s21_res);
  auto iter = std_list_int.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}

TEST_F(Test_list, erase_begin) {
  auto iter_std = std_list_int.begin();
  auto iter_s21 = s21_list_int.begin();

  std_list_int.erase(iter_std);
  s21_list_int.erase(iter_s21);

  auto iter = std_list_int.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
TEST_F(Test_list, erase_end) {
  auto iter_std = --std_list_int.end();
  auto iter_s21 = s21_list_int.end();

  std_list_int.erase(iter_std);
  s21_list_int.erase(iter_s21);

  auto iter = std_list_int.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
TEST_F(Test_list, erase) {
  auto iter_std = std_list_int.begin();
  auto iter_s21 = s21_list_int.begin();

  std_list_int.erase(++iter_std);
  s21_list_int.erase(++iter_s21);

  auto iter = std_list_int.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}

TEST_F(Test_list, push_back) {
  std_list_int.push_back(10);
  s21_list_int.push_back(10);

  auto iter = std_list_int.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
TEST_F(Test_list, pop_back) {
  std_list_int.pop_back();
  s21_list_int.pop_back();

  auto iter = std_list_int.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}

TEST_F(Test_list, push_front) {
  std_list_int.push_front(10);
  s21_list_int.push_front(10);

  auto iter = std_list_int.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
TEST_F(Test_list, pop_front) {
  std_list_int.pop_front();
  s21_list_int.pop_front();

  auto iter = std_list_int.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}

TEST_F(Test_list, swap) {
  std_list_int.swap(std_list_int2);
  s21_list_int.swap(s21_list_int2);

  auto iter = std_list_int.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
  iter = std_list_int2.begin();
  for (auto item : s21_list_int2) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}

TEST_F(Test_list, merge) {
  std_list_int.merge(std_list_int2);
  s21_list_int.merge(s21_list_int2);

  auto iter = std_list_int.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
  EXPECT_EQ(s21_list_int2.size(), std_list_int2.size());
  EXPECT_EQ(s21_list_int2.empty(), true);
}

TEST_F(Test_list, splice_begin) {
  auto iter_std = std_list_int.begin();
  auto iter_s21 = s21_list_int.begin();

  std_list_int.splice(iter_std, std_list_int2);
  s21_list_int.splice(iter_s21, s21_list_int2);

  auto iter = std_list_int.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
  EXPECT_EQ(s21_list_int2.size(), std_list_int2.size());
  EXPECT_EQ(s21_list_int2.empty(), true);
}
TEST_F(Test_list, splice_end) {
  auto iter_std = std_list_int.end();
  auto iter_s21 = s21_list_int.end();

  std_list_int.splice(iter_std, std_list_int2);
  s21_list_int.splice(iter_s21, s21_list_int2);

  auto iter = std_list_int.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
  EXPECT_EQ(s21_list_int2.size(), std_list_int2.size());
  EXPECT_EQ(s21_list_int2.empty(), true);
}
TEST_F(Test_list, splice) {
  auto iter_std = std_list_int.begin();
  auto iter_s21 = s21_list_int.begin();

  std_list_int.splice(++iter_std, std_list_int2);
  s21_list_int.splice(++iter_s21, s21_list_int2);

  auto iter = std_list_int.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
  EXPECT_EQ(s21_list_int2.size(), std_list_int2.size());
  EXPECT_EQ(s21_list_int2.empty(), true);
}

TEST_F(Test_list, reverse) {
  std_list_int.reverse();
  s21_list_int.reverse();

  auto iter = std_list_int.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}

TEST_F(Test_list, unique1) {
  std_list_int.unique();
  s21_list_int.unique();

  auto iter = std_list_int.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
TEST_F(Test_list, unique2) {
  std_list_double.unique();
  s21_list_double.unique();

  auto iter = std_list_double.begin();
  for (auto item : s21_list_double) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
TEST_F(Test_list, unique3) {
  std_list_char.unique();
  s21_list_char.unique();

  auto iter = std_list_char.begin();
  for (auto item : s21_list_char) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
TEST_F(Test_list, unique4) {
  std_list_str.unique();
  s21_list_str.unique();

  auto iter = std_list_str.begin();
  for (auto item : s21_list_str) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}

TEST_F(Test_list, sort) {
  std_list_int.sort();
  s21_list_int.sort();

  auto iter = std_list_int.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
TEST_F(Test_list, sort2) {
  std_list_double.sort();
  s21_list_double.sort();

  auto iter = std_list_double.begin();
  for (auto item : s21_list_double) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
TEST_F(Test_list, sort3) {
  std_list_char.sort();
  s21_list_char.sort();

  auto iter = std_list_char.begin();
  for (auto item : s21_list_char) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
TEST_F(Test_list, sort4) {
  std_list_str.sort();
  s21_list_str.sort();

  auto iter = std_list_str.begin();
  for (auto item : s21_list_str) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}

TEST_F(Test_list, insert_many_begin) {
  std::list<int> s21_res{5, 6, 7, 3, -5, -3, -3, 0, 3, -10, 5, 5};
  auto iter_s21 = s21_list_int.begin();
  auto iter_s21_res = s21_list_int.insert_many(iter_s21, 5, 6, 7);

  EXPECT_EQ(*iter_s21_res, 7);
  auto iter = s21_res.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
TEST_F(Test_list, insert_many_end) {
  std::list<int> s21_res{3, -5, -3, -3, 0, 3, -10, 5, 5, 5, 6, 7};
  auto iter_s21 = s21_list_int.end();
  auto iter_s21_res = s21_list_int.insert_many(iter_s21, 5, 6, 7);

  EXPECT_EQ(*iter_s21_res, 7);
  auto iter = s21_res.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
TEST_F(Test_list, insert_many) {
  std::list<int> s21_res{3, 5, 6, 7, -5, -3, -3, 0, 3, -10, 5, 5};
  auto iter_s21 = s21_list_int.begin();
  auto iter_s21_res = s21_list_int.insert_many(++iter_s21, 5, 6, 7);

  EXPECT_EQ(*iter_s21_res, 7);
  auto iter = s21_res.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}

TEST_F(Test_list, insert_many_back) {
  std::list<int> s21_res{3, -5, -3, -3, 0, 3, -10, 5, 5, 5, 6, 7};
  s21_list_int.insert_many_back(5, 6, 7);

  auto iter = s21_res.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}
TEST_F(Test_list, insert_many_front) {
  std::list<int> s21_res{5, 6, 7, 3, -5, -3, -3, 0, 3, -10, 5, 5};
  s21_list_int.insert_many_front(5, 6, 7);

  auto iter = s21_res.begin();
  for (auto item : s21_list_int) {
    EXPECT_EQ(item, *iter);
    ++iter;
  }
}