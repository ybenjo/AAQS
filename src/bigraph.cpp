#include "bigraph.h"

void BiGraph::set_edge(id_type n1, id_type n2, uint w){
  hash_n1_[n1].insert(n2);
  hash_n2_[n2].insert(n1);
  raw_weight_[key(n1, n2)] += w;
}

void BiGraph::set_weight(){
  _set_weight(hash_n1_);
  _set_weight(hash_n2_);
}

void BiGraph::_set_weight(each_node_hash h){
  each_node_hash::iterator e;
  for(e = h.begin();e != h.end();++e){
    id_type n = e->first;
    list node_list = e->second;
    double sum = 0;
    for(list::iterator i = node_list.begin();i != node_list.end();++i){
      sum += get_raw_weight(n, *i);
    }

    for(list::iterator i = node_list.begin();i != node_list.end();++i){
      weight_[key(n, *i)] = get_raw_weight(n, *i) / sum;
    }
  }
}

uint BiGraph::get_raw_weight(id_type n1, id_type n2){
  uint w = raw_weight_[key(n1, n2)];
  return w == 0 ? raw_weight_[key(n2, n1)] : w;
}

double BiGraph::get_weight(id_type n1, id_type n2){
  return weight_[key(n1, n2)];
}

uint BiGraph::get_adj_size(id_type node){
  return hash_n1_[node].size() > hash_n2_[node].size() ? hash_n1_[node].size() : hash_n2_[node].size();
}
