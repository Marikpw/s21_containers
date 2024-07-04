#include "tests.h"

class Test_queue : public ::testing::Test {
 public:
  std::queue<int> std_empty_queue;
  s21::Queue<int> s21_empty_queue;

  std::queue<int> std_queue_int;
  std::queue<int> std_queue_int2;
  s21::Queue<int> s21_queue_int{3, -5, -3, -3, 0, 3, -10, 5, 5};
  s21::Queue<int> s21_queue_int2{-10, -8, -1, 1, 8, 10};

  std::queue<double> std_queue_double;
  s21::Queue<double> s21_queue_double = {-8.52, -5.83, -2.54, 0.5,
                                         0.5,   6.7,   8.91};
  std::queue<char> std_queue_char;
  s21::Queue<char> s21_queue_char = {'c', 'o', 'n', 'N', 'T', 'a', 'a',
                                     'i', 'i', 'n', 'n', 'E', 'R', 's'};

  std::queue<std::string> std_queue_str;
  s21::Queue<std::string> s21_queue_str = {
      "containers library", "tests for containers",
      "collection of class templates", "containers library"};

  void setIntQueue() {
    std_queue_int.push(3);
    std_queue_int.push(-5);
    std_queue_int.push(-3);
    std_queue_int.push(-3);
    std_queue_int.push(0);
    std_queue_int.push(3);
    std_queue_int.push(-10);
    std_queue_int.push(5);
    std_queue_int.push(5);
  }
  void setInt2Queue() {
    std_queue_int2.push(-10);
    std_queue_int2.push(-8);
    std_queue_int2.push(-1);
    std_queue_int2.push(1);
    std_queue_int2.push(8);
    std_queue_int2.push(10);
  }
  void setDoubleQueue() {
    std_queue_double.push(-8.52);
    std_queue_double.push(-5.83);
    std_queue_double.push(-2.54);
    std_queue_double.push(0.5);
    std_queue_double.push(0.5);
    std_queue_double.push(6.7);
    std_queue_double.push(8.91);
  }
  void setCharQueue() {
    std_queue_char.push('c');
    std_queue_char.push('o');
    std_queue_char.push('n');
    std_queue_char.push('N');
    std_queue_char.push('T');
    std_queue_char.push('a');
    std_queue_char.push('a');
    std_queue_char.push('i');
    std_queue_char.push('i');
    std_queue_char.push('n');
    std_queue_char.push('n');
    std_queue_char.push('E');
    std_queue_char.push('R');
    std_queue_char.push('s');
  }
  void setStrQueue() {
    std_queue_str.push("containers library");
    std_queue_str.push("tests for containers");
    std_queue_str.push("collection of class templates");
    std_queue_str.push("containers library");
  }
};

TEST_F(Test_queue, default_constructor) {
  EXPECT_EQ(std_empty_queue.size(), s21_empty_queue.size());
  EXPECT_EQ(std_empty_queue.empty(), s21_empty_queue.empty());
}

TEST_F(Test_queue, initializerQueue_constructor_int) {
  setIntQueue();
  EXPECT_EQ(std_queue_int.size(), s21_queue_int.size());
  while (std_queue_int.size()) {
    EXPECT_EQ(std_queue_int.front(), s21_queue_int.front());
    std_queue_int.pop();
    s21_queue_int.pop();
  }
}
TEST_F(Test_queue, initializerQueue_constructor_double) {
  setDoubleQueue();
  EXPECT_EQ(std_queue_double.size(), s21_queue_double.size());
  while (std_queue_int.size()) {
    EXPECT_EQ(std_queue_double.front(), s21_queue_double.front());
    std_queue_double.pop();
    s21_queue_double.pop();
  }
}
TEST_F(Test_queue, initializerQueue_constructor_char) {
  setCharQueue();
  EXPECT_EQ(std_queue_char.size(), s21_queue_char.size());
  while (std_queue_char.size()) {
    EXPECT_EQ(std_queue_char.front(), s21_queue_char.front());
    std_queue_char.pop();
    s21_queue_char.pop();
  }
}
TEST_F(Test_queue, initializerQueue_constructor_str) {
  setStrQueue();
  EXPECT_EQ(std_queue_str.size(), s21_queue_str.size());
  while (std_queue_str.size()) {
    EXPECT_EQ(std_queue_str.front(), s21_queue_str.front());
    std_queue_str.pop();
    s21_queue_str.pop();
  }
}

TEST_F(Test_queue, copy_constructor) {
  setIntQueue();
  s21::Queue<int> s21_queue = s21_queue_int;
  std::queue<int> std_queue = std_queue_int;
  EXPECT_EQ(s21_queue_int.size(), s21_queue.size());
  EXPECT_EQ(std_queue_int.size(), s21_queue.size());
  EXPECT_EQ(s21_queue_int.empty(), false);
  while (std_queue.size()) {
    EXPECT_EQ(std_queue.front(), s21_queue.front());
    std_queue.pop();
    s21_queue.pop();
  }
}

TEST_F(Test_queue, move_constructor) {
  setIntQueue();
  s21::Queue<int> s21_queue = std::move(s21_queue_int);
  std::queue<int> std_queue = std::move(std_queue_int);
  EXPECT_EQ(std_queue.size(), s21_queue.size());
  EXPECT_EQ(std_queue_int.size(), s21_queue_int.size());
  EXPECT_EQ(s21_queue_int.empty(), true);
  while (std_queue.size()) {
    EXPECT_EQ(std_queue.front(), s21_queue.front());
    std_queue.pop();
    s21_queue.pop();
  }
}
TEST_F(Test_queue, operator_overload) {
  setIntQueue();
  s21::Queue<int> s21_queue = std::move(s21_queue_int);
  std::queue<int> std_queue = std::move(std_queue_int);
  s21_queue_int = std::move(s21_queue);
  std_queue_int = std::move(std_queue);
  EXPECT_EQ(std_queue_int.size(), s21_queue_int.size());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
  EXPECT_EQ(s21_queue.empty(), true);
  while (std_queue_int.size()) {
    EXPECT_EQ(std_queue_int.front(), s21_queue_int.front());
    std_queue_int.pop();
    s21_queue_int.pop();
  }
}

TEST_F(Test_queue, front) {
  setIntQueue();
  setInt2Queue();
  setDoubleQueue();
  setCharQueue();
  setStrQueue();
  EXPECT_EQ(s21_queue_int.front(), std_queue_int.front());
  EXPECT_EQ(s21_queue_int2.front(), std_queue_int2.front());
  EXPECT_EQ(s21_queue_double.front(), std_queue_double.front());
  EXPECT_EQ(s21_queue_char.front(), std_queue_char.front());
  EXPECT_EQ(s21_queue_str.front(), std_queue_str.front());
}

TEST_F(Test_queue, back) {
  setIntQueue();
  setInt2Queue();
  setDoubleQueue();
  setCharQueue();
  setStrQueue();
  EXPECT_EQ(s21_queue_int.back(), std_queue_int.back());
  EXPECT_EQ(s21_queue_int2.back(), std_queue_int2.back());
  EXPECT_EQ(s21_queue_double.back(), std_queue_double.back());
  EXPECT_EQ(s21_queue_char.back(), std_queue_char.back());
  EXPECT_EQ(s21_queue_str.back(), std_queue_str.back());
}

TEST_F(Test_queue, empty) {
  EXPECT_EQ(s21_empty_queue.empty(), true);
  EXPECT_EQ(s21_queue_int.empty(), false);
}
TEST_F(Test_queue, size) {
  setIntQueue();
  setDoubleQueue();
  setCharQueue();
  setStrQueue();
  EXPECT_EQ(std_empty_queue.size(), s21_empty_queue.size());
  EXPECT_EQ(std_queue_int.size(), s21_queue_int.size());
  EXPECT_EQ(std_queue_double.size(), s21_queue_double.size());
  EXPECT_EQ(std_queue_char.size(), s21_queue_char.size());
  EXPECT_EQ(std_queue_str.size(), s21_queue_str.size());
}

TEST_F(Test_queue, push) {
  setIntQueue();

  std_queue_int.push(10);
  s21_queue_int.push(10);

  while (std_queue_int.size()) {
    EXPECT_EQ(std_queue_int.front(), s21_queue_int.front());
    std_queue_int.pop();
    s21_queue_int.pop();
  }
}
TEST_F(Test_queue, pop) {
  setIntQueue();
  std_queue_int.pop();
  s21_queue_int.pop();

  while (std_queue_int.size()) {
    EXPECT_EQ(std_queue_int.front(), s21_queue_int.front());
    std_queue_int.pop();
    s21_queue_int.pop();
  }
}

TEST_F(Test_queue, swap) {
  setIntQueue();
  setInt2Queue();
  std_queue_int.swap(std_queue_int2);
  s21_queue_int.swap(s21_queue_int2);

  while (std_queue_int.size()) {
    EXPECT_EQ(std_queue_int.front(), s21_queue_int.front());
    std_queue_int.pop();
    s21_queue_int.pop();
  }
  while (std_queue_int2.size()) {
    EXPECT_EQ(std_queue_int2.front(), s21_queue_int2.front());
    std_queue_int2.pop();
    s21_queue_int2.pop();
  }
}

TEST_F(Test_queue, insert_many_front) {
  s21::Queue<int> s21_res{3, -5, -3, -3, 0, 3, -10, 5, 5, 5, 6, 7};
  s21_queue_int.insert_many_back(5, 6, 7);

  while (s21_res.size()) {
    EXPECT_EQ(s21_res.front(), s21_queue_int.front());
    s21_res.pop();
    s21_queue_int.pop();
  }
}