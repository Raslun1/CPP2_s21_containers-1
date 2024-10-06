#include <gtest/gtest.h>

// #include <ostream>
#include <string>

#include "../s21_containers.h"

TEST(Constructors, Init) {
  s21::vector<int> v;
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);

  s21::vector<int> n(5);
  EXPECT_EQ(n.size(), 0);
  EXPECT_EQ(n.capacity(), 5);
}

TEST(Constructors, CreateStr) {
  s21::vector<std::string> n{"abc", "dfg", "mn"};
  EXPECT_EQ(n[0], "abc");
  EXPECT_EQ(n[1], "dfg");
  EXPECT_EQ(n[2], "mn");
}

TEST(Constructors, CreateVector) {
  s21::vector<char> v{'a', 'b', 'c'};
  s21::vector<s21::vector<char>> n{v, v, v};
  EXPECT_EQ(n[0].at(0), 'a');
  EXPECT_EQ(n[1].at(1), 'b');
  EXPECT_EQ(n[2].at(2), 'c');
}

TEST(Constructors, Copy) {
  s21::vector<int> v{1, 2, 3, 4, 5};

  s21::vector<int> n = v;

  EXPECT_EQ(v.size(), n.size());

  EXPECT_EQ(n[0], 1);
  EXPECT_EQ(n[1], 2);
  EXPECT_EQ(n[2], 3);
  EXPECT_EQ(n[3], 4);
  EXPECT_EQ(n[4], 5);
}

TEST(Constructors, Move) {
  s21::vector<int> v{1, 2, 3, 4, 5};

  s21::vector<int> n = std::move(v);

  EXPECT_EQ(n.size(), n.size());

  EXPECT_EQ(n[0], 1);
  EXPECT_EQ(n[1], 2);
  EXPECT_EQ(n[2], 3);
  EXPECT_EQ(n[3], 4);
  EXPECT_EQ(n[4], 5);
}

TEST(Access, At) {
  s21::vector<int> v{1, 2, 3, 4, 5};

  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(1), 2);
  EXPECT_EQ(v.at(2), 3);
  EXPECT_EQ(v.at(3), 4);
  EXPECT_EQ(v.at(4), 5);
}

TEST(Operators, Assignment1) {
  s21::vector<int> v = {1, 2, 3, 4, 5};

  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(1), 2);
  EXPECT_EQ(v.at(2), 3);
  EXPECT_EQ(v.at(3), 4);
  EXPECT_EQ(v.at(4), 5);
}

TEST(Operators, Assignment2) {
  s21::vector<int> n{1, 2, 3, 4, 5};
  s21::vector<int> v;

  v = n;

  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(1), 2);
  EXPECT_EQ(v.at(2), 3);
  EXPECT_EQ(v.at(3), 4);
  EXPECT_EQ(v.at(4), 5);
}

TEST(Access, Braces) {
  s21::vector<int> n{1, 2, 3, 4, 5};

  EXPECT_EQ(n[0], 1);
  EXPECT_EQ(n[1], 2);
  EXPECT_EQ(n[2], 3);
  EXPECT_EQ(n[3], 4);
  EXPECT_EQ(n[4], 5);
}

TEST(Access, FrontBack) {
  s21::vector<int> n{1, 2, 3, 4, 5};

  EXPECT_EQ(n.front(), 1);
  EXPECT_EQ(n.back(), 5);
}

TEST(Capacity, Cap) {
  s21::vector<int> n{1, 2, 3, 4, 5};

  EXPECT_EQ(n.capacity(), 5);
}

TEST(Capacity, Empty) {
  s21::vector<int> n;

  EXPECT_EQ(n.empty(), true);
  n = {1, 2};
  EXPECT_EQ(n.empty(), false);
}

TEST(Modifiers, SrinkToFit) {
  s21::vector<int> v{1, 2, 3};

  EXPECT_EQ(v.capacity(), 3);
  v.push_back(5);

  EXPECT_EQ(v.capacity(), 6);

  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 4);
}

TEST(Modifiers, Clear) {
  s21::vector<int> v{1, 2, 3};

  v.clear();
  EXPECT_EQ(v.capacity(), 3);
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.data(), nullptr);
}

TEST(Modifiers, Pop) {
  s21::vector<int> v{1, 2, 3};

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);

  v.pop_back();
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
}

TEST(Modifiers, InsertManyBack) {
  s21::vector<int> v{1, 2, 3};

  EXPECT_EQ(v.size(), 3);

  v.insert_many_back(4, 5, 6, 7);

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], 5);
  EXPECT_EQ(v[5], 6);
  EXPECT_EQ(v[6], 7);

  EXPECT_EQ(v.size(), 7);
}

TEST(Modifiers, InsertMany1) {
  s21::vector<int> v{1, 2, 3};

  EXPECT_EQ(v.size(), 3);

  v.insert_many(v.begin(), 0, 9);

  EXPECT_EQ(v[0], 0);
  EXPECT_EQ(v[1], 9);
  EXPECT_EQ(v[2], 1);
  EXPECT_EQ(v[3], 2);
  EXPECT_EQ(v[4], 3);

  EXPECT_EQ(v.size(), 5);
}

TEST(Modifiers, InsertMany2) {
  s21::vector<int> v{1, 2, 3, 4};

  EXPECT_EQ(v.size(), 4);

  v.insert_many(v.begin() + 2, 0, 9);

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 0);
  EXPECT_EQ(v[3], 9);
  EXPECT_EQ(v[4], 3);
  EXPECT_EQ(v[5], 4);

  EXPECT_EQ(v.size(), 6);
}

TEST(Modifiers, Erase1) {
  s21::vector<int> v{1, 2, 3, 4, 5, 6};

  EXPECT_EQ(v.size(), 6);

  v.erase(v.begin());
  EXPECT_EQ(v.size(), 5);

  EXPECT_EQ(v[0], 2);
  EXPECT_EQ(v[1], 3);
  EXPECT_EQ(v[2], 4);
  EXPECT_EQ(v[3], 5);
  EXPECT_EQ(v[4], 6);
}

TEST(Modifiers, Erase2) {
  s21::vector<int> v{1, 2, 3, 4, 5, 6};

  EXPECT_EQ(v.size(), 6);

  v.erase(v.begin() + 2);
  EXPECT_EQ(v.size(), 5);

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 4);
  EXPECT_EQ(v[3], 5);
  EXPECT_EQ(v[4], 6);
}

TEST(Modifiers, ForEach) {
  s21::vector<int> v{1, 2, 3};

  int i = 1;
  for (const auto &elem : v) {
    EXPECT_EQ(i, elem);
    i++;
  }
}

TEST(Modifiers, ForEachModify) {
  s21::vector<int> v{1, 2, 3};

  for (auto &elem : v) elem = 5;
  for (const auto &elem : v) EXPECT_EQ(5, elem);
}

// int main(int argc, char **argv) {
//   std::cout << "======================= VECTOR TESTS ======================="
//             << std::endl;
//   ::testing::InitGoogleTest(&argc, argv);

//   return RUN_ALL_TESTS();
// }