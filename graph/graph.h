/*
 * graph.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "object_pool.h"

namespace dataflow {

struct Node;
struct NodeInfo;
struct NodeOps;
struct Edge;
struct EdgeInfo;
struct EdgeOps;
struct Graph;

enum NodeType {
};

struct NodeInfo {
  int id;
  char name[50];
  int is_src;
  int is_sink;
  std::vector<int> out_neighbors;
  std::vector<int> in_neighbors;
};



struct NodeOps {
  static Node* MakeNode(const NodeInfo& info) {}
  static NodeInfo* GetNodeInfo(const Node& node) {}
  static bool CheckValidNode(const Node& node) {}
  static Node* SetNodeInfo(Node* node, const NodeInfo& info) {}
};

struct Node {
  NodeInfo info;
  int& GetId() { return info.id; }
  std::string& GetName() { return info.name; }
  std::vector<int>& OutNeigbors() { return info.out_neighbors; }
  std::vector<int>& InNeigbors() { return info.in_neighbors; }
};

struct EdgeInfo {
  int id;
  int src;
  int dst;
};

struct Edge {
  EdgeInfo info;
  int& GetId() { return info.id; }
  std::string& GetName() { return info.name; }
  int& Src() { return info.src; }
  int& Dst() { return info.dst; }
};

struct EdgeOps {
  static Edge* MakeEdge(const EdgeInfo& info);
  static EdgeInfo* GetEdgeInfo(const Edge& edge);
  static bool CheckValidEdge(const Edge& edge);
  static Node* SetEdgeInfo(Edge* edge, const EdgeInfo& info);
};

class Graph {
public:
  Graph() {}
  ~Graph() {}

public:
  static ObjectPool<Node> node_pool_;
  static ObjectPool<Edge> edge_pool_;
  // id to edges
  std::unordered_map<int, Edge*> edges_;
  // id to nodes
  std::unordered_map<int, Node*> nodes_;

};
}

#endif /* !GRAPH_H */

