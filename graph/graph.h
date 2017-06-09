/*
 * graph.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "logic.hpp"
#include "object_pool.h"
#include "caffe.pb.h"

namespace dataflow {

struct Node;
struct NodeInfo;
struct Edge;
struct EdgeInfo;
struct Graph;

enum NodeType {
};

struct NodeInfo {
  int id;
  char name[50];
  int is_src;
  int is_sink;
  LayerProto* layer_info;
  std::vector<int> out_neighbors;
  std::vector<int> in_neighbors;
};

struct Node {
  NodeInfo info;
  std::string& GetName() { return info.name; }
};

struct EdgeInfo {
  int id;
  int src;
  int dst;
};

struct Edge {
  EdgeInfo info;
};

class Graph {
public:
  Graph() {}
  ~Graph() {}

public:
  void SetNetDefinition(const caffe::NetProto* proto);
  void BuildNet();

private:
  Node* CreateNode(const caffe::LayerProto& proto);
  void BuildEdges();

public:
  static ObjectPool<Node> node_pool_;
  static ObjectPool<Edge> edge_pool_;
  // id to edges
  std::unordered_map<int, Edge*> edges_;
  // id to nodes
  std::unordered_map<int, Node*> nodes_;

};


};

}

#endif /* !GRAPH_H */

