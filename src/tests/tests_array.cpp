#include <gtest/gtest.h>

#include "../s21_containersplus.h"
#include "string"

TEST(Array_Constructors, Init) {
  s21::array<int, 5> a;
  EXPECT_EQ(a.size(), 5);

  for (size_t i = 0; i < a.size(); ++i) {
    EXPECT_EQ(a[i], 0);
  }
}

TEST(Array_Constructors, CreateStr) {
  s21::array<std::string, 3> n{"abc", "dfg", "mn"};
  EXPECT_EQ(n[0], "abc");
  EXPECT_EQ(n[1], "dfg");
  EXPECT_EQ(n[2], "mn");
}

TEST(Array_Constructors, CreateArray) {
  s21::array<char, 3> a{'a', 'b', 'c'};
  s21::array<s21::array<char, 3>, 3> n{a, a, a};
  EXPECT_EQ(n[0].at(0), 'a');
  EXPECT_EQ(n[1].at(1), 'b');
  EXPECT_EQ(n[2].at(2), 'c');
}

TEST(Array_Constructors, Copy) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};

  s21::array<int, 5> n = a;

  EXPECT_EQ(a.size(), n.size());

  EXPECT_EQ(n[0], 1);
  EXPECT_EQ(n[1], 2);
  EXPECT_EQ(n[2], 3);
  EXPECT_EQ(n[3], 4);
  EXPECT_EQ(n[4], 5);
}

TEST(Array_Constructors, Move) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};

  s21::array<int, 5> n = std::move(a);

  EXPECT_EQ(n.size(), n.size());

  EXPECT_EQ(n[0], 1);
  EXPECT_EQ(n[1], 2);
  EXPECT_EQ(n[2], 3);
  EXPECT_EQ(n[3], 4);
  EXPECT_EQ(n[4], 5);
}

TEST(Array_Access, At) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};

  EXPECT_EQ(a.at(0), 1);
  EXPECT_EQ(a.at(1), 2);
  EXPECT_EQ(a.at(2), 3);
  EXPECT_EQ(a.at(3), 4);
  EXPECT_EQ(a.at(4), 5);
}

TEST(Array_Operators, Assignment1) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};

  EXPECT_EQ(a.at(0), 1);
  EXPECT_EQ(a.at(1), 2);
  EXPECT_EQ(a.at(2), 3);
  EXPECT_EQ(a.at(3), 4);
  EXPECT_EQ(a.at(4), 5);
}

TEST(Array_Operators, Assignment2) {
  s21::array<int, 5> n{1, 2, 3, 4, 5};
  s21::array<int, 5> a;

  a = n;

  EXPECT_EQ(a.at(0), 1);
  EXPECT_EQ(a.at(1), 2);
  EXPECT_EQ(a.at(2), 3);
  EXPECT_EQ(a.at(3), 4);
  EXPECT_EQ(a.at(4), 5);
}

TEST(Array_Access, Braces) {
  s21::array<int, 5> n{1, 2, 3, 4, 5};

  EXPECT_EQ(n[0], 1);
  EXPECT_EQ(n[1], 2);
  EXPECT_EQ(n[2], 3);
  EXPECT_EQ(n[3], 4);
  EXPECT_EQ(n[4], 5);
}

TEST(Array_Access, FrontBack) {
  s21::array<int, 5> n{1, 2, 3, 4, 5};

  EXPECT_EQ(n.front(), 1);
  EXPECT_EQ(n.back(), 5);
}

TEST(Array_Access, Data) {
  s21::array<int, 5> n{1, 2, 3, 4, 5};

  EXPECT_EQ(n.data(), n.begin());
}

TEST(Array_Iterators, BeginEnd) {
  s21::array<int, 5> n{1, 2, 3, 4, 5};

  EXPECT_EQ(n.data(), n.begin());
  EXPECT_EQ(n.data() + n.size(), n.end());
}

TEST(Array_Capacity, Empty) {
  s21::array<int, 0> n;

  EXPECT_EQ(n.empty(), true);

  s21::array<int, 6> a = {1, 2};
  EXPECT_EQ(a.empty(), false);
}

// int main(int argc, char **argv) {
//   std::cout << "======================= ARRAY TESTS ======================="
//             << std::endl;
//   ::testing::InitGoogleTest(&argc, argv);

//   return RUN_ALL_TESTS();
// }