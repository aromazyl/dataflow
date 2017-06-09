/*
 * ops.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef OPS_H
#define OPS_H

#include "caffe.pb.h"

namespace dataflow {

class Ops {
  Ops(const &) {}
  virtual ~Ops() {}
};

}

#endif /* !OPS_H */
