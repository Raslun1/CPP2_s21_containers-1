#include <gtest/gtest.h>

#include "../s21_containers.h"

TEST(Queue_Constructors, Move) {
  s21::queue<char> n{'a', 'b', 'c', 'd'};

  s21::queue<char> q = std::move(n);

  char temp = q.front();
  q.pop();
  EXPECT_EQ(temp, 'a');
  temp = q.front();
  q.pop();
  EXPECT_EQ(temp, 'b');
  temp = q.front();
  q.pop();
  EXPECT_EQ(temp, 'c');
  temp = q.front();
  EXPECT_EQ(temp, 'd');
}

TEST(Queue_Constructors, Copy) {
  s21::queue<char> m{'a', 'b', 'c', 'd'};
  s21::queue<char> q = m;

  char temp = q.front();
  q.pop();
  EXPECT_EQ(temp, 'a');
  temp = q.front();
  q.pop();
  EXPECT_EQ(temp, 'b');
  temp = q.front();
  q.pop();
  EXPECT_EQ(temp, 'c');
  temp = q.front();
  EXPECT_EQ(temp, 'd');
}

TEST(Queue_Constructors, Initializer) {
  s21::queue<char> q{'a', 'b', 'c', 'd'};

  char temp = q.front();
  q.pop();
  EXPECT_EQ(temp, 'a');
  temp = q.front();
  q.pop();
  EXPECT_EQ(temp, 'b');
  temp = q.front();
  q.pop();
  EXPECT_EQ(temp, 'c');
  temp = q.front();
  EXPECT_EQ(temp, 'd');
}

TEST(Queue_Constructors, pop) {
  s21::queue<char> q{'a', 'b', 'c', 'd'};

  q.pop();
  int size = q.size();
  EXPECT_EQ(size, 3);
}

TEST(Queue_Constructors, push) {
  s21::queue<int> q{1, 2, 3, 4};

  q.push(10);
  int size = q.size();
  EXPECT_EQ(size, 5);
  int val = q.back();
  EXPECT_EQ(val, 10);
}

TEST(Queue_Constructors, front) {
  s21::queue<int> q{1, 2, 3, 4};

  int val = q.front();
  EXPECT_EQ(val, 1);
}

TEST(Queue_Constructors, back) {
  s21::queue<int> q{1, 2, 3, 4};

  int val = q.back();
  EXPECT_EQ(val, 4);
}

TEST(Queue_Constructors, Size) {
  s21::queue<int> q{1, 2, 3, 4};

  int size = q.size();
  EXPECT_EQ(size, 4);
}

TEST(Queue_Constructors, EmptyTrue) {
  s21::queue<int> q;

  bool res = q.empty();
  EXPECT_EQ(res, true);
}

TEST(Queue_Constructors, EmptyFalse) {
  s21::queue<int> q{1, 2, 3, 4};

  bool res = q.empty();
  EXPECT_EQ(res, false);
}

TEST(Queue_Constructors, Operator) {
  s21::queue<char> m{'a', 'b', 'c', 'd'};
  s21::queue<char> q;

  q = m;

  char temp = q.front();
  q.pop();
  EXPECT_EQ(temp, 'a');
  temp = q.front();
  q.pop();
  EXPECT_EQ(temp, 'b');
  temp = q.front();
  q.pop();
  EXPECT_EQ(temp, 'c');
  temp = q.front();
  EXPECT_EQ(temp, 'd');
}

TEST(Queue_Constructors, swap) {
  s21::queue<char> m{'a', 'b', 'c', 'd'};
  s21::queue<char> q{'c', 'e'};

  m.swap(q);

  char temp = q.front();
  q.pop();
  EXPECT_EQ(temp, 'a');
  temp = q.front();
  q.pop();
  EXPECT_EQ(temp, 'b');
  temp = q.front();
  q.pop();
  EXPECT_EQ(temp, 'c');
  temp = q.front();
  EXPECT_EQ(temp, 'd');

  temp = m.front();
  m.pop();
  EXPECT_EQ(temp, 'c');
  temp = m.front();
  EXPECT_EQ(temp, 'e');
}

TEST(Queue_DOP, test) {
  s21::queue<int> q;
  q.insert_many_back(1, 2, 3, 4, 5);
  int size = q.size();
  EXPECT_EQ(size, 5);
}

// int main(int argc, char **argv) {
//   std::cout << "======================= queue TESTS ======================="
//             << std::endl;
//   ::testing::InitGoogleTest(&argc, argv);

//   return RUN_ALL_TESTS();
// }