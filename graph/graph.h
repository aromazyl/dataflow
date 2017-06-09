/*
 * graph.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>
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
  Convolution = 0,
  Loader,
  InnerProduct,
  Pooling,
  ReLU,
  LRN,
  Sigmoid,
  Softmax,
  MultinomialLogisticLoss,
  Split,
  Concat,
  BatchNorm,
  ModelUpdate,
  NullUpdate,
  Store,
  LoadPartialModel,
  Placeholder
};


struct NodeInfo {
  NodeType type;
  int id;
  std::string name;
  bool is_src;
  bool is_sink;
  std::vector<std::string> out_nodes;
  std::vector<std::string> in_nodes;
};

struct Node {
  NodeInfo info;
  LayerProto proto;
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
  static Graph* CreateGraphByConfigFile(const std::string& config);
  static Graph* CreateGraphByNetConfig(const caffe::NetParameter& confg);

public:
  Graph() {}
  ~Graph() {}


public:
  void SetNetDefinition(const caffe::NetParameter& param);
  void BuildNet();

private:
  Node* CreateNode(const caffe::LayerProto& proto, int index);
  Edge* CreateEdge(int src, int sink, int index);
  void BuildEdges();

public:
  static ObjectPool<Node> node_pool_;
  static ObjectPool<Edge> edge_pool_;

  std::unordered_map<std::string, int> edge_index_;
  std::unordered_map<std::string, int> node_index_;
  // id to edges
  std::unordered_map<int, Edge*> edges_;
  // id to nodes
  std::unordered_map<int, Node*> nodes_;

  static std::unordered_map<std::string, NodeType> kLayerNameToNodeType;
};

};

}

#endif /* !GRAPH_H */

