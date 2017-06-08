/*
 * graph_token_test.cc
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "graph_token.h"

#include <gtest/gtest.h>
#include <glog/logging.h>

namespace dataflow {
class GraphTokenTest : public ::testing::Test {
public:
  void SetUp() {}
  void TearDown() {}

private:
};

TEST_F(GraphTokenTest, ReadTest) {
  Tree* tree = ParseTree("./conf");
  PrintTree(tree);
}
