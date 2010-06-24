#include "bigraph.h"

void BiGraph::set_edge(uint n1, uint n2, uint w){
  hash_n1[n1].insert(n2);
  hash_n2[n2].insert(n1);
  raw_weight[key(n1, n2)] += w;
}

void BiGraph::set_weight(){
}

uint BiGraph::get_adj_size(uint node){
  return hash_n1[node].size() > hash_n2[node].size() ? hash_n1[node].size() : hash_n2[node].size();
}
