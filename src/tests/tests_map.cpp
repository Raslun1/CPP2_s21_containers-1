#include <gtest/gtest.h>

#include <map>

#include "../s21_containers.h"

TEST(Map_Constructors, test_1) {
  s21::map<int, int> m1;
  std::map<int, int> m2;

  EXPECT_EQ(m1.size(), m2.size());
}

TEST(Map_Constructors, test_2) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}};

  EXPECT_EQ(m1.size(), m2.size());

  auto it1 = m1.begin();
  auto it2 = m2.begin();

  for (int i = 0; i < 3; i++) {
    EXPECT_EQ((*it1).first, (*it2).first);
    EXPECT_EQ((*it1).second, (*it2).second);
  }
}

TEST(Map_Constructors, test_3) {
  s21::map<char, double> m1 = {{'a', 1.0}, {'b', 2.2}, {'c', 3.5}};
  std::map<char, double> m2 = {{'a', 1.0}, {'b', 2.2}, {'c', 3.5}};

  EXPECT_EQ(m1.size(), m2.size());

  auto it1 = m1.begin();
  auto it2 = m2.begin();

  for (int i = 0; i < 3; i++) {
    EXPECT_EQ((*it1).first, (*it2).first);
    EXPECT_EQ((*it1).second, (*it2).second);
  }
}

TEST(Map_Constructors, test_4) {
  s21::map<char, double> m1 = {{'a', 1.0}, {'b', 2.2}, {'c', 3.5}};
  s21::map<char, double> m2 = m1;

  std::map<char, double> m3 = {{'a', 1.0}, {'b', 2.2}, {'c', 3.5}};
  std::map<char, double> m4 = m3;

  EXPECT_EQ(m1.size(), m4.size());

  auto it1 = m1.begin();
  auto it2 = m4.begin();

  for (int i = 0; i < 3; i++) {
    EXPECT_EQ((*it1).first, (*it2).first);
    EXPECT_EQ((*it1).second, (*it2).second);
  }
}

TEST(Map_Constructors, test_5) {
  s21::map<int, int> m1 = {{1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}};
  s21::map<int, int> m2(m1);

  std::map<int, int> m3 = {{1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}};
  std::map<int, int> m4(m3);

  EXPECT_EQ((*m2.begin()).first, (*m4.begin()).first);
  EXPECT_EQ((*m2.begin()).second, (*m4.begin()).second);

  EXPECT_EQ(m2.size(), 1);
  EXPECT_EQ(m4.size(), 1);
}

TEST(Map_Constructors, test_6) {
  s21::map<int, int> m1 = {{1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}};
  s21::map<int, int> m2(m1);

  std::map<int, int> m3 = {{1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}};
  std::map<int, int> m4(m3);

  EXPECT_EQ((*m2.begin()).first, (*m4.begin()).first);
  EXPECT_EQ((*m2.begin()).second, (*m4.begin()).second);

  EXPECT_EQ(m2.size(), 1);
  EXPECT_EQ(m4.size(), 1);
}

TEST(Map_Constructors, test_7) {
  s21::map<int, int> m1 = {{1, 0}, {5, 0}, {3, 0}, {4, 0}, {2, 0},
                           {6, 0}, {9, 0}, {7, 0}, {8, 0}};
  s21::map<int, int> m2(std::move(m1));

  int i = 1;
  for (auto value : m2) {
    EXPECT_EQ(i, value.first);
    EXPECT_EQ(0, value.second);
    i++;
  }
  EXPECT_EQ(i, 10);
  EXPECT_TRUE(m1.empty());
}

TEST(Map_Constructors, test_8) {
  s21::map<int, int> m1 = {{1, 0}, {5, 0}, {3, 0}, {4, 0}, {2, 0},
                           {6, 0}, {9, 0}, {7, 0}, {8, 0}};
  s21::map<int, int> m2, m3;
  m2 = m1;
  m3 = std::move(m1);

  for (auto it1 = m3.begin(), it2 = m2.begin(); it1 != m3.end(); it1++, it2++) {
    EXPECT_EQ((*it1).first, (*it2).first);
    EXPECT_EQ((*it1).second, (*it2).second);
  }
  int i = 1;
  for (auto value : m2) {
    EXPECT_EQ(i, value.first);
    EXPECT_EQ(0, value.second);
    i++;
  }
  EXPECT_EQ(i, 10);
  EXPECT_TRUE(m1.empty());
}

TEST(Map_Access, Adding) {
  s21::map<int, int> s;

  for (int i = 0; i < 10; i++) s[i] = i;

  int i = 0;
  for (const auto val : s) {
    EXPECT_EQ(val.first, i);
    EXPECT_EQ(val.second, i++);
  }

  EXPECT_EQ(s.size(), 10);
}

TEST(Map_Access, Changing) {
  s21::map<int, int> s;

  s[2] = 2;

  EXPECT_EQ(s[2], 2);

  s[2] = 1;

  EXPECT_EQ(s[2], 1);

  EXPECT_EQ(s.size(), 1);
}

TEST(Map_Access, Changing2) {
  s21::map<int, int> s;

  s[2] = 2;

  EXPECT_EQ(s[2], 2);

  s[2]++;

  EXPECT_EQ(s[2], 3);

  EXPECT_EQ(s.size(), 1);
}

TEST(Map_Access, At) {
  s21::map<int, int> s;

  s[2] = 2;

  EXPECT_EQ(s[2], 2);

  s[2]++;

  EXPECT_EQ(s.at(2), 3);

  EXPECT_EQ(s.size(), 1);
}

TEST(Map_Iterators, ultimate) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      for (int k = 0; k < 5; k++) {
        for (int q = 0; q < 5; q++) {
          for (int w = 0; w < 5; w++) {
            s21::map<int, int> m1 = {{i, 0}, {j, 0}, {k, 0}, {q, 0}, {w, 0}};
            std::map<int, int> m2 = {{i, 0}, {j, 0}, {k, 0}, {q, 0}, {w, 0}};
            auto it2 = m2.begin();
            for (auto it1 = m1.begin(); it1 != m1.end(); it1++, it2++) {
              EXPECT_EQ((*it1).first, ((*it2).first));
            }
          }
        }
      }
    }
  }
}

TEST(Map_Operations, Empty) {
  s21::map<int, int> s = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  s21::map<int, int> s2;

  EXPECT_FALSE(s.empty());
  EXPECT_TRUE(s2.empty());
}

TEST(Map_Operations, Size) {
  s21::map<int, int> s = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

  EXPECT_EQ(s.size(), 5);
}

TEST(Map_Operations, MaxSize) {
  s21::map<int, int> s;

  EXPECT_TRUE(s.max_size() > 0);
}

TEST(Map_Operations, Swap) {
  s21::map<int, int> m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  s21::map<int, int> m2 = {{6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}};

  int i = 1;
  for (const auto &value : m) EXPECT_EQ(value.first, i++);

  for (const auto &value : m2) EXPECT_EQ(value.first, i++);

  m.swap(m2);

  i = 1;
  for (const auto &value : m2) EXPECT_EQ(value.first, i++);

  for (const auto &value : m) EXPECT_EQ(value.first, i++);
}

TEST(Map_Operations, Clear) {
  s21::map<int, int> s = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

  EXPECT_EQ(s.size(), 5);
  s.clear();
  EXPECT_EQ(s.size(), 0);
}

TEST(Map_Operations, Contain) {
  s21::map<int, int> m;

  m.insert_or_assign(1, 1);
  m.insert_or_assign(2, 2);

  EXPECT_FALSE(m.contains(0));
  EXPECT_TRUE(m.contains(1));
  EXPECT_TRUE(m.contains(2));
  EXPECT_FALSE(m.contains(3));
}

TEST(Map_Operations, Merge) {
  s21::map<int, int> m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

  s21::map<int, int> m2;

  m2.merge(m);

  int i = 1;
  for (const auto &value : m) EXPECT_EQ(value.first, i++);

  for (const auto &value : m2) EXPECT_EQ(value.first, i++);

  EXPECT_EQ(i, 6);
}

TEST(Map_Insert, test_1) {
  std::pair<int, int> items[] = {{10, 4}, {1341, 341}, {-134, 2345}};
  s21::map<int, int> m1;
  std::map<int, int> m2;
  for (int i = 0; i < 3; i++) {
    m1.insert(items[i]);
    m2.insert(items[i]);
  }
  EXPECT_EQ(m1.size(), m2.size());
  auto it2 = m2.begin();
  for (auto it1 : m1) {
    EXPECT_EQ(it1.first, (*it2).first);
    EXPECT_EQ(it1.second, (*it2).second);
    it2++;
  }
}

TEST(Map_Insert, test_2) {
  std::pair<int, int> items[] = {{10, 4}, {1341, 341}, {-134, 2345}};
  s21::map<int, int> m1;
  std::map<int, int> m2;
  for (int i = 0; i < 3; i++) {
    m1.insert(items[i].first, items[i].second);
    m2.insert(items[i]);
  }
  EXPECT_EQ(m1.size(), m2.size());
  auto it2 = m2.begin();
  for (auto it1 : m1) {
    EXPECT_EQ(it1.first, (*it2).first);
    EXPECT_EQ(it1.second, (*it2).second);
    it2++;
  }
}
TEST(Map_Insert, test_3) {
  s21::map<int, int> s;

  s.insert_or_assign(1, 1);
  s.insert_or_assign(2, 2);
  s.insert_or_assign(3, 3);
  s.insert_or_assign(4, 4);
  s.insert_or_assign(5, 5);

  int i = 1;
  for (const auto &value : s) EXPECT_EQ(value.first, i++);

  EXPECT_EQ(i, 6);
}

TEST(Map_Insert, test_4) {
  s21::map<int, int> s;

  s.insert_or_assign(1, 0);
  s.insert_or_assign(1, 1);

  int i = 1;
  for (const auto &value : s) EXPECT_EQ(value.first, i++);

  EXPECT_EQ(i, 2);
}

TEST(Map_Insert, test_5) {
  s21::map<int, int> s;

  s.insert_or_assign(1, 1);
  s.insert_or_assign(2, 2);

  EXPECT_FALSE(s.contains(0));
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_FALSE(s.contains(3));
}

TEST(Map_Operations, InsertMany) {
  s21::map<int, int> s;
  s.insert_many(std::pair(1, 1), std::pair(2, 2), std::pair(3, 3),
                std::pair(4, 4), std::pair(5, 5));

  int i = 1;
  for (const auto &value : s) EXPECT_EQ(value.first, i++);

  EXPECT_EQ(i, 6);
}

// int main(int argc, char **argv) {
//   std::cout << "======================= MAP TESTS ======================="
//             << std::endl;
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
