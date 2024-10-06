#include <set>

#include "../containersplus/s21_multiset.h"
#include "gtest/gtest.h"

TEST(Multiset_Constructors, test_1) {
  s21::multiset<int> m1;
  std::multiset<int> m2;

  EXPECT_EQ(m1.size(), m2.size());
}

TEST(Multiset_Constructors, test_2) {
  s21::multiset<int> m1 = {1, 2, 3};
  std::multiset<int> m2 = {1, 2, 3};

  EXPECT_EQ(m1.size(), m2.size());

  auto it1 = m1.begin();
  auto it2 = m2.begin();

  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(Multiset_Constructors, test_3) {
  s21::multiset<char> m1 = {'a', 'b', 'c'};
  std::multiset<char> m2 = {'a', 'b', 'c'};

  EXPECT_EQ(m1.size(), m2.size());

  auto it1 = m1.begin();
  auto it2 = m2.begin();

  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(Multiset_Constructors, test_4) {
  s21::multiset<char> m1 = {'a', 'b', 'c'};
  s21::multiset<char> m2 = m1;

  std::multiset<char> m3 = {'a', 'b', 'c'};
  std::multiset<char> m4 = m3;

  EXPECT_EQ(m1.size(), m4.size());

  auto it1 = m1.begin();
  auto it2 = m4.begin();

  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(Multiset_Constructors, test_5) {
  s21::multiset<int> m1 = {1, 1, 1, 1, 1};
  s21::multiset<int> m2(m1);

  std::multiset<int> m3 = {1, 1, 1, 1, 1};
  std::multiset<int> m4(m3);

  EXPECT_EQ(*m2.begin(), *m4.begin());

  EXPECT_EQ(m2.size(), 5);
  EXPECT_EQ(m4.size(), 5);
}

TEST(Multiset_Constructors, test_6) {
  s21::multiset<int> m1 = {1, 5, 3, 4, 2, 6, 9, 7, 8};
  s21::multiset<int> m2(std::move(m1));

  int i = 1;
  for (auto value : m2) {
    EXPECT_EQ(i, value);
    i++;
  }
  EXPECT_EQ(i, 10);
  EXPECT_TRUE(m1.empty());
}

TEST(Multiset_Constructors, test_7) {
  s21::multiset<int> m1 = {1, 5, 3, 4, 2, 6, 9, 7, 8};
  s21::multiset<int> m2, m3;
  m2 = m1;
  m3 = std::move(m1);

  for (auto it1 = m3.begin(), it2 = m2.begin(); it1 != m3.end(); it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
  int i = 1;
  for (auto value : m2) {
    EXPECT_EQ(i, value);
    i++;
  }
  EXPECT_EQ(i, 10);
  EXPECT_TRUE(m1.empty());
}

TEST(Multiset_Operations, Empty) {
  s21::multiset<int> s = {1, 2, 3, 4, 5};
  s21::multiset<int> s2;

  EXPECT_FALSE(s.empty());
  EXPECT_TRUE(s2.empty());
}

TEST(Multiset_Operations, Size) {
  s21::multiset<int> s = {1, 2, 3, 4, 5};

  EXPECT_EQ(s.size(), 5);
}

TEST(Multiset_Operations, MaxSize) {
  s21::multiset<int> s;

  EXPECT_TRUE(s.max_size() > 0);
}

TEST(Multiset_Operations, Swap) {
  s21::multiset<int> m = {1, 2, 3, 4, 5};
  s21::multiset<int> m2 = {6, 7, 8, 9, 10};

  int i = 1;
  for (const auto &value : m) EXPECT_EQ(value, i++);

  for (const auto &value : m2) EXPECT_EQ(value, i++);

  m.swap(m2);

  i = 1;
  for (const auto &value : m2) EXPECT_EQ(value, i++);

  for (const auto &value : m) EXPECT_EQ(value, i++);
}

TEST(Multiset_Operations, Clear) {
  s21::multiset<int> s = {1, 2, 3, 4, 5};

  EXPECT_EQ(s.size(), 5);
  s.clear();
  EXPECT_EQ(s.size(), 0);
}

TEST(Multiset_Operations, Contain) {
  s21::multiset<int> m;

  m.insert(1);
  m.insert(2);

  EXPECT_FALSE(m.contains(0));
  EXPECT_TRUE(m.contains(1));
  EXPECT_TRUE(m.contains(2));
  EXPECT_FALSE(m.contains(3));
}

TEST(Multiset_Operations, Insert) {
  s21::multiset<int> m1;
  std::multiset<int> m2;
  int items[] = {2, 4, 1, 5053, 3};
  for (auto i : items) {
    m1.insert(i);
    m2.insert(i);
  }
  auto it1 = m1.begin();
  for (auto it2 : m2) {
    EXPECT_EQ(*it1, it2);
    it1++;
  }
}

TEST(Multiset_Functions, Insert1) {
  s21::multiset<int> s;

  s.insert(1);
  s.insert(2);
  s.insert(3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(Multiset_Functions, Insert2) {
  s21::multiset<int> s;

  s.insert(1);
  s.insert(1);
  s.insert(1);
  s.insert(1);
  s.insert(1);
  EXPECT_EQ(s.size(), 5);
}

TEST(Multiset_Functions, Erase1) {
  s21::multiset<int> s = {1, 2, 3, 4};

  s.erase(s.find(1));
  EXPECT_EQ(s.size(), 3);

  s.erase(s.find(2));
  EXPECT_EQ(s.size(), 2);

  s.erase(s.find(3));
  EXPECT_EQ(s.size(), 1);

  EXPECT_FALSE(s.contains(1));
  EXPECT_FALSE(s.contains(2));
  EXPECT_FALSE(s.contains(3));
}

TEST(Multiset_Functions, Erase2) {
  s21::multiset<int> s = {1, 2, 3, 4};

  s.erase(s.find(6));

  EXPECT_EQ(s.size(), 4);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(4));
}

TEST(Multiset_Operations, Merge) {
  s21::multiset<int> m = {1, 2, 3, 4, 5};

  s21::multiset<int> m2;

  m2.merge(m);

  int i = 1;
  for (const auto &value : m) EXPECT_EQ(value, i++);

  for (const auto &value : m2) EXPECT_EQ(value, i++);

  EXPECT_EQ(i, 6);
}

TEST(Multiset_Operations, Find) {
  s21::multiset<int> m = {1, 2, 3, 4, 5};
  auto it = m.find(2);
  EXPECT_EQ(*it, 2);
}

TEST(Multiset_Functions, InsertMany) {
  s21::set<int> s;
  s.insert_many(1, 2, 3, 4, 5, 6);
  int i = 1;
  for (const auto &val : s) EXPECT_EQ(i++, val);

  EXPECT_EQ(6, s.size());
}

// int main(int argc, char **argv) {
//   std::cout << "======================= multiset TESTS
//   ======================="
//             << std::endl;
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
