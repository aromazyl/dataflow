/*
 * test_.cc
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <vector>
#include <string>
#include <stdio.h>

int main() {
  printf("%d,%d", sizeof(std::vector<int>), sizeof(std::string));
  return 0;
}
