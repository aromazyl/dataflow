/*
 * object_pool_test.cc
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <gtest/gtest.h>

#define private public
#define protected public

#include "object_pool.h"


namespace oneflow {
class ObjectPool_Test : public ::testing::Test {
public:
  void SetUp() {}
  void TearDown() {}

  ObjectPool<int> pool;
};

TEST_F(ObjectPool_Test, NewObjectTest) {
  std::vector<int*> intvec;
  for (int i = 0; i < 10; ++i)
    intvec.push_back(pool.NewObject());

  EXPECT_EQ((int)(pool.type_vec_.size()), 10);
  for (int i = 0; i < 10; ++i)
    pool.FreeObject(intvec[i]);
  intvec.clear();

  EXPECT_EQ((int)(pool.type_vec_.size()), 0);
  EXPECT_EQ((int)(pool.free_vec_.size()), 10);

  pool.NewObject();
  EXPECT_EQ((int)(pool.free_vec_.size()), 9);
  EXPECT_EQ((int)(pool.type_vec_.size()), 1);
}
}
