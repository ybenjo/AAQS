#include "bigraph.h"

void BiGraph::set_edge(const id_type& n_u, const id_type& n_v, const uint& w){
  if (n_u == n_v){
    exit(EXIT_FAILURE);
  }

  nodes_u_[n_u].insert(n_v);
  nodes_v_[n_v].insert(n_u);
  raw_weight_[key(n_u, n_v)] += w;
}

void BiGraph::_set_weight(const each_node_hash& h){
  each_node_hash::const_iterator e;
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

void BiGraph::set_weight(){
  _set_weight(nodes_u_);
  _set_weight(nodes_v_);
}

void BiGraph::set_parameter(const double& u, const double& v){
  lambda_u_ = u;
  lambda_v_ = v;
}

uint BiGraph::get_raw_weight(const id_type& n_u, const id_type& n_v){
  uint w = raw_weight_[key(n_u, n_v)];
  return w == 0 ? raw_weight_[key(n_v, n_u)] : w;
}

double BiGraph::get_weight(const id_type& n_u, const id_type& n_v){
  return weight_[key(n_u, n_v)];
}

uint BiGraph::get_adj_size(const id_type& node){
  uint s_u = nodes_u_[node].size();
  uint s_v = nodes_v_[node].size();
  return s_u > s_v ? s_u : s_v;
}

void BiGraph::_set_init_score(const each_node_hash& nodes, d_hash& score1, d_hash& score2){
  uint size = nodes.size();
  each_node_hash::const_iterator i;
  for(i = nodes.begin();i != nodes.end();++i){
    id_type node = i->first;
    score1[node] = 1.0 / size;
    score2[node] = 1.0 / size;
  }
}

void BiGraph::set_init_score(){
  _set_init_score(nodes_u_, _init_score_u_, score_u_);
  _set_init_score(nodes_v_, _init_score_v_, score_v_);
}

double BiGraph::get_score_u(const id_type& n_u){
  return score_u_[n_u];
}

double BiGraph::get_score_v(const id_type& n_v){
  return score_v_[n_v];
}

double BiGraph::calc_validation(const id_type& i){
  double sum = 0.0;
  d_hash score1, score2;
  d_hash::iterator flag = _init_score_u_.find(i);
  if(flag != _init_score_u_.end()){
    score1 = _init_score_u_;
    score2 = _init_score_v_;
  }else{
    score1 = _init_score_v_;
    score2 = _init_score_u_;
  }
  
  d_hash::iterator j;
  d_hash::iterator k;
  for(j = score1.begin();j != score1.end();++j){
    id_type node_j = j->first;
    for(k = score2.begin();k != score2.end();++k){
      id_type node_k = k->first;
      sum += weight_[key(i, node_k)] * weight_[key(node_k, node_j)];
    }
  }
  return sum;
}

void BiGraph::_propagate(const each_node_hash& nodes, d_hash& init_score, d_hash& score_1, d_hash& score_2){
  each_node_hash::const_iterator n;
  for(n = nodes.begin();n != nodes.end();++n){
    id_type node_n = n->first;
    list list_m = n->second;
    score_1[node_n] = (1 - lambda_u_) * init_score[node_n];
    for(list::iterator m = list_m.begin();m != list_m.end();++m){
      id_type node_m = *m;
      score_1[node_n] += lambda_u_ * score_2[node_m] * weight_[key(node_m, node_n)];
    }
  }
}

void BiGraph::propagate(){
  _propagate(nodes_u_, _init_score_u_, score_u_, score_v_);
  _propagate(nodes_v_, _init_score_v_, score_v_, score_u_);
}

void BiGraph::propagation(const uint& count){
  for(int i = 0;i < count;++i){
    propagate();
  }
}

