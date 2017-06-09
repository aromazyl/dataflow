/*
 * graph.cc
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "graph.h"


namespace dataflow {

#define LAYER(name) \
  {name, #name}

std::unordered_map<std::string, NodeType>
  Graph::kLayerNameToNodeType = {
    LAYER(Convolution),
    LAYER(Loader),
    LAYER(InnerProduct),
    LAYER(Pooling),
    LAYER(ReLU),
    LAYER(LRN),
    LAYER(Sigmoid),
    LAYER(Softmax),
    LAYER(MultinomialLogisticLoss),
    LAYER(Split),
    LAYER(Concat),
    LAYER(BatchNorm),
    LAYER(ModelUpdate),
    LAYER(NullUpdate),
    LAYER(Store),
    LAYER(LoadPartialModel),
    LAYER(Placeholder)
  };

void Graph::SetNetDefinition(const caffe::NetParameter& param) {

  nodes_.clear(); node_index_.clear();
  edge_index_.clear(); edges_.clear();

  for (int i = 0; i < proto.layer_size(); ++i) {
    this->CreateNode(proto.layer(i), i);
  }

}

void Graph::BuildNet() {
  int edge_index = 0;
  for (size_t i = 0; i < node_index_.size(); ++i) {
    for (auto& node : nodes_[i].out_nodes) {
      this->CreateEdge(nodes_[i].id, node_index_[node.name], edge_index);
      ++edge_index;
    }
  }
}

Node* Graph::CreateNode(const caffe::LayerProto& proto, int index) {
  Node* node = node_pool_.NewObject();
  node->info.name = proto.name();
  node->info.type = this->kLayerNameToNodeType[proto.name()];
  node->id = index;
  node->proto = proto;
  node->is_src = 
}

Edge* Graph::CreateEdge(int src, int sink, int index) {
  
}
}
