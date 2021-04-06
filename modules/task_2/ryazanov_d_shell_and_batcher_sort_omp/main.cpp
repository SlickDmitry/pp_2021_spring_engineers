// Copyright 2021 Dmitry Ryazanov
#include <omp.h>
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include "./shell_and_batcher_sort_omp.h"

TEST(getRandomVector, no_exceptions) { ASSERT_NO_THROW(getRandomVector(100)); }

TEST(getRandomVector, wrong_size) { ASSERT_ANY_THROW(getRandomVector(-100)); }

TEST(getRandomVector, works) {
  auto vect = getRandomVector(100);
  ASSERT_EQ(static_cast<int>(vect.size()), 100);
}

TEST(Shell_and_Batcher_sort, no_exceptions) {
  auto vect = getRandomVector(100);
  ASSERT_NO_THROW(SortShell(vect));
}

TEST(Shell_and_Batcher_sort, works_size_two) {
  auto vect = std::vector<int>({2, 1});
  print(vect);
  auto res = SortShell(vect);
  print(res);
  ASSERT_EQ(res, std::vector<int>({1, 2}));
}

TEST(Shell_and_Batcher_sort, works_size_4) {
  std::vector<int> vect = getRandomVector(4);
  print(vect);
  auto res = BatcherSort(vect);
  print(res);
}

TEST(Shell_and_Batcher_sort, works_size_10_OMP) {
  std::vector<int> vect = getRandomVector(10);
  print(vect);
  auto res = BatcherSortOMP(vect);
  print(res);
}

TEST(Shell_and_Batcher_sort, works_random_size_100) {
  auto vect = getRandomVector(100);
  auto sorted = SortShell(vect);
  std::sort(vect.begin(), vect.end());
  ASSERT_EQ(vect, sorted);
}

TEST(Shell_and_Batcher_sort, test_time) {
  auto vect = getRandomVector(100);
  double start = omp_get_wtime();
  auto res = BatcherSort(vect);
  double end = omp_get_wtime();
  std::cout << "Seq sort time: " << end - start << std::endl;

  start = omp_get_wtime();
  auto resOMP = BatcherSortOMP(vect);
  end = omp_get_wtime();
  std::cout << "OMP sort time: " << end - start << std::endl;

  ASSERT_EQ(res, resOMP);
}

TEST(Shell_and_Batcher_sort, works_random_vec_Shell_and_Batcher) {
  auto vect = getRandomVector(100);
  auto res1 = SortShell(vect);
  auto res2 = BatcherSort(vect);
  std::sort(vect.begin(), vect.end());
  ASSERT_EQ(res1, res2);
}

TEST(Shell_and_Batcher_sort, works_random_vec_Shell_and_Batcher_OMP) {
  auto vect = getRandomVector(10);
  auto res2 = BatcherSortOMP(vect);
  std::sort(vect.begin(), vect.end());
  ASSERT_EQ(vect, res2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}