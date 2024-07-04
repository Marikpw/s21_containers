#include <gtest/gtest.h>

#include <set>

#include "../set/s21_set.h"

TEST(set, constructor) {
  s21::set<int> test{};
  EXPECT_TRUE(test.empty());
}

TEST(set, init) {
  s21::set<int> test = {52, 54, 45, 48, 53};
  std::set<int> test2 = {52, 54, 45, 48, 53};
  std::set<int>::iterator it = test2.begin();
  s21::set<int>::iterator it2 = test.begin();
  for (; it != test2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
}

TEST(set, copy_constructor) {
  s21::set<int> test = {52, 54, 45, 48, 53};
  s21::set<int> test2(test);
  std::set<int> set = {52, 54, 45, 48, 53};
  std::set<int> set2(set);
  std::set<int>::iterator it = set2.begin();
  s21::set<int>::iterator it2 = test2.begin();
  for (; it != set2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
}

TEST(set, move_constructor) {
  s21::set<int> test = {52, 54, 45, 48, 53};
  s21::set<int> test2(std::move(test));
  std::set<int> set = {52, 54, 45, 48, 53};
  std::set<int> set2(std::move(set));
  std::set<int>::iterator it = set2.begin();
  s21::set<int>::iterator it2 = test2.begin();
  for (; it != set2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
  ASSERT_EQ(test2.size(), set2.size());
}

TEST(set, move_assignment) {
  s21::set<int> test = {52, 54, 45, 48, 53};
  s21::set<int> test2 = {7, 4, 8, 0, -1};
  test2 = std::move(test);
  std::set<int> set = {52, 54, 45, 48, 53};
  std::set<int> set2 = {7, 4, 8, 0, -1};
  set2 = std::move(set);
  std::set<int>::iterator it = set2.begin();
  s21::set<int>::iterator it2 = test2.begin();
  for (; it != set2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
  ASSERT_EQ(test2.size(), set2.size());
}

TEST(set, begin) {
  s21::set<int> test = {52, 54, 45, 48, 53};
  s21::set<int>::iterator it = test.begin();
  std::set<int> test2 = {52, 54, 45, 48, 53};
  std::set<int>::iterator it2 = test2.begin();
  ASSERT_EQ(*it, *it2);
  it++;
  it2++;
  ASSERT_EQ(*it, *it2);
}

TEST(set, minus) {
  s21::set<int> test = {52, 54, 45, 48, 53};
  s21::set<int>::iterator it = test.begin();
  std::set<int> test2 = {52, 54, 45, 48, 53};
  std::set<int>::iterator it2 = test2.begin();
  it++;
  it2++;
  it--;
  it2--;
  ASSERT_EQ(*it, *it2);
}

TEST(set, find) {
  s21::set<int> test = {52, 54, 45, 48, 53};
  s21::set<int>::iterator it = test.find(45);
  std::set<int> test2 = {52, 54, 45, 48, 53};
  std::set<int>::iterator it2 = test2.find(45);
  ASSERT_EQ(*it, *it2);
}

TEST(set, contains) {
  s21::set<int> test = {52, 54, 45, 48, 53};
  bool check = test.contains(60);
  ASSERT_FALSE(check);
}

TEST(set, insert) {
  std::set<int> test = {52, 54, 45, 48, 53};
  std::pair<std::set<int>::iterator, bool> check = test.insert(45);
  s21::set<int> test2 = {52, 54, 45, 48, 53};
  std::pair<s21::set<int>::iterator, bool> check2 = test2.insert(45);
  ASSERT_EQ(*check.first, *check2.first);
  ASSERT_EQ(check.second, check2.second);
}

TEST(set, insert2) {
  std::set<int> test = {52, 54, 45, 48, 53};
  std::pair<std::set<int>::iterator, bool> check = test.insert(0);
  s21::set<int> test2 = {52, 54, 45, 48, 53};
  std::pair<s21::set<int>::iterator, bool> check2 = test2.insert(0);
  ASSERT_EQ(*check.first, *check2.first);
  ASSERT_EQ(check.second, check2.second);
}

TEST(set, clear) {
  std::set<int> test = {52, 54, 45, 48, 53};
  s21::set<int> test2 = {52, 54, 45, 48, 53};
  test.clear();
  test2.clear();
  ASSERT_EQ(test.size(), test2.size());
}

TEST(set, size) {
  std::set<int> test = {52, 54, 45, 48, 53};
  s21::set<int> test2 = {52, 54, 45, 48, 53};
  ASSERT_EQ(test.size(), test2.size());
}

TEST(set, empty) {
  s21::set<int> test2{};
  ASSERT_TRUE(test2.empty());
  test2.insert(45);
  ASSERT_FALSE(test2.empty());
}

TEST(set, swap) {
  s21::set<int> test = {52, 54, 45, 48, 53};
  s21::set<int> test2 = {7, 4, 8, 0, -1, 48, 53};
  std::set<int> set = {52, 54, 45, 48, 53};
  std::set<int> set2 = {7, 4, 8, 0, -1, 48, 53};
  test2.swap(test);
  set2.swap(set);
  std::set<int>::iterator it = set2.begin();
  s21::set<int>::iterator it2 = test2.begin();
  for (; it != set2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
  it2 = test.begin();
  for (it = set.begin(); it != set.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
}

TEST(set, erase) {
  std::set<int> test = {52, 54, 45, 48, 53};
  s21::set<int> test2 = {52, 54, 45, 48, 53};
  std::set<int>::iterator it = test.begin();
  s21::set<int>::iterator it2 = test2.begin();
  ++it;
  ++it2;
  test.erase(it);
  test2.erase(it2);
  it = test.begin();
  it2 = test2.begin();
  for (; it != test.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
}

TEST(set, InsertMany) {
  s21::set<int> test;
  auto results = test.insert_many(52, 54, 45, 48, 53);

  ASSERT_EQ(test.size(), 5);

  for (const auto& result : results) {
    ASSERT_TRUE(result.second);
  }
}

TEST(set, InsertManyDuplicate) {
  s21::set<int> test = {52, 54, 45};
  auto results = test.insert_many(52, 54, 45, 48, 53);

  ASSERT_EQ(test.size(), 5);

  int expected_insertions = 0;
  for (const auto& result : results) {
    if (result.second) {
      ++expected_insertions;
    }
  }
  ASSERT_EQ(expected_insertions, 2);
}
