/*
 * graph_token.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef GRAPH_TOKEN_H
#define GRAPH_TOKEN_H

#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "./graph.h"

namespace dataflow {

struct Tree {
  std::string key;
  std::string value;
  std::vector<Tree*> children;
};

inline void deleteTree(Tree* tree) {
  if (!tree) return;

  for (auto& u : children)
    deleteTree(u);

  delete tree;
}

inline void PrintTree(Tree* tree) {
  if (!tree) return;
  std::cout << "{" << tree->key << ":" << tree->value << "}, ";
  for (auto& child : tree->children) {
    PrintTree(child);
  }
  std::cout << "\n";
}

template <typename Type>
struct ParserImpl;

struct GraphInfo;
struct NodeArea;
struct NodeInfo;
struct KeyValue;

template <>
struct ParserImpl<KeyValue> {
  static bool Apply(std::ifstream& is, Tree* tree) {
    tree->children.push_back(new Tree);
    auto& key = tree->children.rbegin()->key
    is >> key;
    if (key == "}") return true;
    if (key == "{") return false;
    auto& value = tree->children.rbegin()->value
    is >> value;
    if (value != ":") return false;
    is >> value;
    return ParserImpl<KeyValue>::Apply(is, tree);
  }
};

template <>
struct ParserImpl<NodeInfo> {
  static bool Apply(std::ifstream& is, Tree* tree) {
    if (is.peek() == '}') return true;
    is >> tree->key;
    is >> tree->value;
    if (tree->value != "{") return false;
    return ParserImpl<KeyValue>::Apply(is, tree);
  }
};

template <>
struct ParserImpl<NodeArea> {
  static bool Apply(std::ifstream& is, Tree* tree) {
    is >> tree->value;
    if (tree->value != "{") return false;
    tree->children.push_back(new Tree);
    bool ret =
      ParserImpl<NodeInfo>::Apply(is, tree->children[tree->children.size() - 1]);
    if (!ret) return false;
    is >> tree->value;
    if (tree->value != "}") return false;
    return true;
  }
};

template <>
struct ParserImpl<GraphInfo> {
  static bool Apply(std::ifstream& is, Tree* tree) {
    if (is.peek() == EOF) return true;
    tree->children.push_back(new Tree);
    return
      ParserImpl<NodeArea>::Apply(is, tree->children[tree->children.size() - 1])
      && ParserImpl<GraphInfo>::Apply(is, tree);
  }
};

inline Tree* ParseTree(const std::string& filename) {
  auto tree = new Tree;
  std::ifstream is(filename);
  bool ret = ParserImpl<GraphInfo>::Apply(is, tree);
  if (!ret) {
    fprintf(stderr, "parse tree failure");
    exit(1);
  }
  return tree;
}



}

#endif /* !GRAPH_TOKEN_H */
