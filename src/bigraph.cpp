#include "bigraph.h"
void BiGraph::set_edge(const id_type& n_u, const id_type& n_v, const uint& w){
  if (n_u == n_v){
    exit(EXIT_FAILURE);
  }

  nodes_u_[n_u].insert(n_v);
  nodes_v_[n_v].insert(n_u);
  raw_weight_[key(n_u, n_v)] += w;
}

void BiGraph::_set_prob(const each_node_hash& h){
  each_node_hash::const_iterator e;
  for(e = h.begin();e != h.end();++e){
    id_type n = e->first;
    list node_list = e->second;
    double sum = 0;
    for(list::iterator i = node_list.begin();i != node_list.end();++i){
      sum += get_raw_weight(n, *i);
    }

    for(list::iterator i = node_list.begin();i != node_list.end();++i){
      prob_[key(n, *i)] = get_raw_weight(n, *i) / sum;
    }
  }
}

void BiGraph::set_prob(){
  _set_prob(nodes_u_);
  _set_prob(nodes_v_);
}

uint BiGraph::get_raw_weight(const id_type& n_u, const id_type& n_v){
  uint w = raw_weight_[key(n_u, n_v)];
  return w == 0 ? raw_weight_[key(n_v, n_u)] : w;
}

double BiGraph::get_prob(const id_type& n_u, const id_type& n_v){
  return prob_[key(n_u, n_v)];
}

uint BiGraph::get_adj_size(const id_type& node){
  uint s_u = nodes_u_[node].size();
  uint s_v = nodes_v_[node].size();
  return s_u > s_v ? s_u : s_v;
}

double BiGraph::get_score_u(const id_type& n_u){
  return score_u_[n_u];
}

double BiGraph::get_score_v(const id_type& n_v){
  return score_v_[n_v];
}

