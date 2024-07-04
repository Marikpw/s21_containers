#include "tests.h"

class Test_stack : public ::testing::Test {
 public:
  std::stack<int> std_empty_stack;
  s21::Stack<int> s21_empty_stack;

  std::stack<int> std_stack_int;
  std::stack<int> std_stack_int2;
  s21::Stack<int> s21_stack_int{3, -5, -3, -3, 0, 3, -10, 5, 5};
  s21::Stack<int> s21_stack_int2{-10, -8, -1, 1, 8, 10};

  std::stack<double> std_stack_double;
  s21::Stack<double> s21_stack_double = {-8.52, -5.83, -2.54, 0.5,
                                         0.5,   6.7,   8.91};
  std::stack<char> std_stack_char;
  s21::Stack<char> s21_stack_char = {'c', 'o', 'n', 'N', 'T', 'a', 'a',
                                     'i', 'i', 'n', 'n', 'E', 'R', 's'};

  std::stack<std::string> std_stack_str;
  s21::Stack<std::string> s21_stack_str = {
      "containers library", "tests for containers",
      "collection of class templates", "containers library"};

  void setIntStack() {
    std_stack_int.push(3);
    std_stack_int.push(-5);
    std_stack_int.push(-3);
    std_stack_int.push(-3);
    std_stack_int.push(0);
    std_stack_int.push(3);
    std_stack_int.push(-10);
    std_stack_int.push(5);
    std_stack_int.push(5);
  }
  void setInt2Stack() {
    std_stack_int2.push(-10);
    std_stack_int2.push(-8);
    std_stack_int2.push(-1);
    std_stack_int2.push(1);
    std_stack_int2.push(8);
    std_stack_int2.push(10);
  }
  void setDoubleStack() {
    std_stack_double.push(-8.52);
    std_stack_double.push(-5.83);
    std_stack_double.push(-2.54);
    std_stack_double.push(0.5);
    std_stack_double.push(0.5);
    std_stack_double.push(6.7);
    std_stack_double.push(8.91);
  }
  void setCharStack() {
    std_stack_char.push('c');
    std_stack_char.push('o');
    std_stack_char.push('n');
    std_stack_char.push('N');
    std_stack_char.push('T');
    std_stack_char.push('a');
    std_stack_char.push('a');
    std_stack_char.push('i');
    std_stack_char.push('i');
    std_stack_char.push('n');
    std_stack_char.push('n');
    std_stack_char.push('E');
    std_stack_char.push('R');
    std_stack_char.push('s');
  }
  void setStrStack() {
    std_stack_str.push("containers library");
    std_stack_str.push("tests for containers");
    std_stack_str.push("collection of class templates");
    std_stack_str.push("containers library");
  }
};

TEST_F(Test_stack, default_constructor) {
  EXPECT_EQ(std_empty_stack.size(), s21_empty_stack.size());
  EXPECT_EQ(std_empty_stack.empty(), s21_empty_stack.empty());
}

TEST_F(Test_stack, initializerStack_constructor_int) {
  setIntStack();
  EXPECT_EQ(std_stack_int.size(), s21_stack_int.size());
  while (std_stack_int.size()) {
    EXPECT_EQ(std_stack_int.top(), s21_stack_int.top());
    std_stack_int.pop();
    s21_stack_int.pop();
  }
}
TEST_F(Test_stack, initializerStack_constructor_double) {
  setDoubleStack();
  EXPECT_EQ(std_stack_double.size(), s21_stack_double.size());
  while (std_stack_int.size()) {
    EXPECT_EQ(std_stack_double.top(), s21_stack_double.top());
    std_stack_double.pop();
    s21_stack_double.pop();
  }
}
TEST_F(Test_stack, initializerStack_constructor_char) {
  setCharStack();
  EXPECT_EQ(std_stack_char.size(), s21_stack_char.size());
  while (std_stack_char.size()) {
    EXPECT_EQ(std_stack_char.top(), s21_stack_char.top());
    std_stack_char.pop();
    s21_stack_char.pop();
  }
}
TEST_F(Test_stack, initializerStack_constructor_str) {
  setStrStack();
  EXPECT_EQ(std_stack_str.size(), s21_stack_str.size());
  while (std_stack_str.size()) {
    EXPECT_EQ(std_stack_str.top(), s21_stack_str.top());
    std_stack_str.pop();
    s21_stack_str.pop();
  }
}

TEST_F(Test_stack, copy_constructor) {
  setIntStack();
  s21::Stack<int> s21_stack = s21_stack_int;
  std::stack<int> std_stack = std_stack_int;
  EXPECT_EQ(s21_stack_int.size(), s21_stack.size());
  EXPECT_EQ(std_stack_int.size(), s21_stack.size());
  EXPECT_EQ(s21_stack_int.empty(), false);
  while (std_stack.size()) {
    EXPECT_EQ(std_stack.top(), s21_stack.top());
    std_stack.pop();
    s21_stack.pop();
  }
}

TEST_F(Test_stack, move_constructor) {
  setIntStack();
  s21::Stack<int> s21_stack = std::move(s21_stack_int);
  std::stack<int> std_stack = std::move(std_stack_int);
  EXPECT_EQ(std_stack.size(), s21_stack.size());
  EXPECT_EQ(std_stack_int.size(), s21_stack_int.size());
  EXPECT_EQ(s21_stack_int.empty(), true);
  while (std_stack.size()) {
    EXPECT_EQ(std_stack.top(), s21_stack.top());
    std_stack.pop();
    s21_stack.pop();
  }
}
TEST_F(Test_stack, operator_overload) {
  setIntStack();
  s21::Stack<int> s21_stack = std::move(s21_stack_int);
  std::stack<int> std_stack = std::move(std_stack_int);
  s21_stack_int = std::move(s21_stack);
  std_stack_int = std::move(std_stack);
  EXPECT_EQ(std_stack_int.size(), s21_stack_int.size());
  EXPECT_EQ(std_stack.size(), s21_stack.size());
  EXPECT_EQ(s21_stack.empty(), true);
  while (std_stack_int.size()) {
    EXPECT_EQ(std_stack_int.top(), s21_stack_int.top());
    std_stack_int.pop();
    s21_stack_int.pop();
  }
}

TEST_F(Test_stack, top) {
  setIntStack();
  setInt2Stack();
  setDoubleStack();
  setCharStack();
  setStrStack();
  EXPECT_EQ(s21_stack_int.top(), std_stack_int.top());
  EXPECT_EQ(s21_stack_int2.top(), std_stack_int2.top());
  EXPECT_EQ(s21_stack_double.top(), std_stack_double.top());
  EXPECT_EQ(s21_stack_char.top(), std_stack_char.top());
  EXPECT_EQ(s21_stack_str.top(), std_stack_str.top());
}

TEST_F(Test_stack, empty) {
  EXPECT_EQ(s21_empty_stack.empty(), true);
  EXPECT_EQ(s21_stack_int.empty(), false);
}
TEST_F(Test_stack, size) {
  setIntStack();
  setDoubleStack();
  setCharStack();
  setStrStack();
  EXPECT_EQ(std_empty_stack.size(), s21_empty_stack.size());
  EXPECT_EQ(std_stack_int.size(), s21_stack_int.size());
  EXPECT_EQ(std_stack_double.size(), s21_stack_double.size());
  EXPECT_EQ(std_stack_char.size(), s21_stack_char.size());
  EXPECT_EQ(std_stack_str.size(), s21_stack_str.size());
}

TEST_F(Test_stack, push) {
  setIntStack();

  std_stack_int.push(10);
  s21_stack_int.push(10);

  while (std_stack_int.size()) {
    EXPECT_EQ(std_stack_int.top(), s21_stack_int.top());
    std_stack_int.pop();
    s21_stack_int.pop();
  }
}
TEST_F(Test_stack, pop) {
  setIntStack();
  std_stack_int.pop();
  s21_stack_int.pop();

  while (std_stack_int.size()) {
    EXPECT_EQ(std_stack_int.top(), s21_stack_int.top());
    std_stack_int.pop();
    s21_stack_int.pop();
  }
}

TEST_F(Test_stack, swap) {
  setIntStack();
  setInt2Stack();
  std_stack_int.swap(std_stack_int2);
  s21_stack_int.swap(s21_stack_int2);

  while (std_stack_int.size()) {
    EXPECT_EQ(std_stack_int.top(), s21_stack_int.top());
    std_stack_int.pop();
    s21_stack_int.pop();
  }
  while (std_stack_int2.size()) {
    EXPECT_EQ(std_stack_int2.top(), s21_stack_int2.top());
    std_stack_int2.pop();
    s21_stack_int2.pop();
  }
}

TEST_F(Test_stack, insert_many_front) {
  s21::Stack<int> s21_res{3, -5, -3, -3, 0, 3, -10, 5, 5, 5, 6, 7};
  s21_stack_int.insert_many_front(5, 6, 7);

  while (s21_res.size()) {
    EXPECT_EQ(s21_res.top(), s21_stack_int.top());
    s21_res.pop();
    s21_stack_int.pop();
  }
}