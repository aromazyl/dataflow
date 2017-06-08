/*
 * object_pool.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include <queue>
#include <unordered_set>

namespace oneflow {

class ObjectPool_Test;

template <typename Type>
class ObjectPool {
public:
  Type* NewObject() {
    if (!free_vec_.empty()) {
      auto ret = free_vec_.front();
      free_vec_.pop();
      type_vec_.insert(ret);
      return ret;
    } else {
      auto ret = new Type;
      type_vec_.insert(ret);
      return ret;
    }
  }

  void FreeObject(Type* object) {
    if (type_vec_.count(object)) {
      type_vec_.erase(object);
    } else {
      fprintf(stderr, "double free: %p\n", object);
      exit(1);
    }
    free_vec_.push(object);
  }

  ~ObjectPool() { this->Destory(); }

private:
  void Destory() {
    while (!free_vec_.empty()) {
      auto p = free_vec_.front();
      free_vec_.pop();
      delete p;
    }
    while (!type_vec_.empty()) {
      auto p = *(type_vec_.begin());
      type_vec_.erase(p);
      delete p;
    }
  }

private:
  std::unordered_set<Type*> type_vec_;
  std::queue<Type*> free_vec_;

  friend class ObjectPool_Test;

};

};

#endif /* !OBJECT_POOL_H */
