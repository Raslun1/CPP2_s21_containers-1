#include <gtest/gtest.h>

#include "../s21_containers.h"

TEST(Stack_stackTest, IsemptyOnInit) {
  s21::stack<int> stack;
  EXPECT_TRUE(stack.empty());
}

TEST(Stack_stackTest, pushAndSize) {
  s21::stack<int> stack;
  stack.push(1);
  stack.push(2);
  EXPECT_EQ(stack.size(), 2);
}

TEST(Stack_stackTest, popAndempty) {
  s21::stack<int> stack;
  stack.push(1);
  stack.push(2);
  stack.pop();
  stack.pop();
  EXPECT_TRUE(stack.empty());
}

TEST(Stack_stackTest, top) {
  s21::stack<int> stack;
  stack.push(1);
  stack.push(2);
  EXPECT_EQ(stack.top(), 2);
}

TEST(Stack_stackTest, swap) {
  s21::stack<int> stack1;
  stack1.push(1);
  s21::stack<int> stack2;
  stack2.push(2);
  stack2.push(3);
  stack1.swap(stack2);
  EXPECT_EQ(stack1.size(), 2);
  EXPECT_EQ(stack2.size(), 1);
  EXPECT_EQ(stack1.top(), 3);
  EXPECT_EQ(stack2.top(), 1);
}

TEST(Stack_stackTest, OperatorEquals) {
  s21::stack<int> stack1;
  stack1.push(1);
  stack1.push(2);
  s21::stack<int> stack2;
  stack2.push(1);
  stack2.push(2);

  EXPECT_TRUE(stack1 == stack2);

  stack2.pop();
  stack2.push(3);
  EXPECT_FALSE(stack1 == stack2);
}

TEST(Stack_stackTest, CopyAssignmentoperator) {
  s21::stack<int> stack1;
  stack1.push(1);
  stack1.push(2);
  s21::stack<int> stack2;
  stack2 = std::move(stack1);

  stack2.pop();
  EXPECT_EQ(stack1.size(), 0);
  EXPECT_EQ(stack2.size(), 1);
}

TEST(Stack_stackTest, MoveAssignmentoperator) {
  s21::stack<int> stack1;
  stack1.push(1);
  stack1.push(2);
  s21::stack<int> stack2;
  stack2 = std::move(stack1);

  EXPECT_EQ(stack1.size(), 0);
  EXPECT_EQ(stack2.size(), 2);
  EXPECT_EQ(stack2.top(), 2);
}

TEST(Stack_stackInsertManyFrontTest, InsertSingleElement) {
  s21::stack<int> stack;
  stack.insert_many_back(1);

  EXPECT_EQ(stack.top(), 1);
  EXPECT_EQ(stack.size(), 1);
}

TEST(Stack_stackInsertManyFrontTest, InsertMultipleElements) {
  s21::stack<int> stack;
  stack.insert_many_back(1, 2, 3);

  EXPECT_EQ(stack.top(), 3);
  stack.pop();
  EXPECT_EQ(stack.top(), 2);
  stack.pop();
  EXPECT_EQ(stack.top(), 1);
  EXPECT_EQ(stack.size(), 1);
}

TEST(Stack_stackInsertManyFrontTest, InsertIntoNonemptystack) {
  s21::stack<int> stack;
  stack.insert_many_back(1);
  stack.insert_many_back(2, 3);

  EXPECT_EQ(stack.top(), 3);
  EXPECT_EQ(stack.size(), 3);
}

TEST(Stack_stackTest, BoundaryConditions) {
  s21::stack<int> stack;

  for (int i = 0; i < 40; i++) {
    stack.push(i);
  }
  EXPECT_EQ(stack.size(), 40);
  for (int i = 40 - 1; i >= 0; i--) {
    EXPECT_EQ(stack.top(), i);
    stack.pop();
  }
  EXPECT_TRUE(stack.empty());
}

TEST(Stack_stackTest, SequentialOperations) {
  s21::stack<int> stack;
  stack.push(1);
  stack.push(2);
  EXPECT_EQ(stack.top(), 2);
  stack.pop();
  EXPECT_EQ(stack.top(), 1);
  stack.pop();
  EXPECT_TRUE(stack.empty());
}

TEST(Stack_stackTest, CopyAndMoveIntegrity) {
  s21::stack<int> original;
  original.push(1);
  s21::stack<int> copy = original;
  s21::stack<int> moved(std::move(original));
  original.push(2);
  EXPECT_EQ(copy.top(), 1);
  EXPECT_EQ(moved.top(), 1);
  EXPECT_EQ(original.top(), 2);
}

TEST(Stack_stackTest, ExceptionSafety) {
  s21::stack<int> stack;
  EXPECT_THROW(stack.pop(), std::out_of_range);
  EXPECT_THROW(stack.top(), std::out_of_range);
}

TEST(Stack_stackTest, StressTest) {
  s21::stack<int> stack;
  for (int i = 0; i < 1000000; i++) {
    stack.push(i);
  }
  for (int i = 999999; i >= 0; i--) {
    EXPECT_EQ(stack.top(), i);
    stack.pop();
  }
  EXPECT_TRUE(stack.empty());
}

TEST(Stack_stackInsertManyFrontTest, InsertElementsOfDifferentTypes) {
  s21::stack<int> stack;
  stack.insert_many_back(1, 2);

  EXPECT_EQ(stack.top(), 2);
  stack.pop();
  EXPECT_EQ(stack.top(), 1);
}

// int main(int argc, char **argv) {
//   std::cout << "======================= STACK TESTS ======================="
//             << std::endl;
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }