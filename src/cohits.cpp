#include "bigraph.h"

void BiGraph::_cohits_set_init_score(const each_node_hash& nodes, d_hash& score1, d_hash& score2){
  uint size = nodes.size();
  each_node_hash::const_iterator i;
  for(i = nodes.begin();i != nodes.end();++i){
    id_type node = i->first;
    score1[node] = 1.0 / size;
    score2[node] = 1.0 / size;
  }
}

void BiGraph::cohits_set_init_score(){
  cout << "cohits_set_init_score" << endl;
  _cohits_set_init_score(nodes_u_, _init_score_u_, score_u_);
  _cohits_set_init_score(nodes_v_, _init_score_v_, score_v_);
}

void BiGraph::cohits_set_parameter(const double& u, const double& v){
  cout << "cohits_set_parameter" << endl;
  cohits_lambda_u_ = u;
  cohits_lambda_v_ = v;
}


double BiGraph::cohits_calc_validation(const id_type& i){
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
      sum += prob_[key(i, node_k)] * prob_[key(node_k, node_j)];
    }
  }
  return sum;
}

void BiGraph::_cohits_one_propagate(const each_node_hash& nodes, d_hash& init_score, d_hash& score_1, d_hash& score_2, const double& param){
  each_node_hash::const_iterator n;
  for(n = nodes.begin();n != nodes.end();++n){
    id_type node_n = n->first;
    list list_m = n->second;
    score_1[node_n] = (1 - param) * init_score[node_n];
    double kakko_sum = 0.0;
    for(list::iterator m = list_m.begin();m != list_m.end();++m){
      id_type node_m = *m;
      kakko_sum += score_2[node_m] * get_prob(node_m, node_n);
    }
    score_1[node_n] += param * kakko_sum;
  }
}

void BiGraph::cohits_one_propagate(){
  _cohits_one_propagate(nodes_u_, _init_score_u_, score_u_, score_v_, cohits_lambda_u_);
  _cohits_one_propagate(nodes_v_, _init_score_v_, score_v_, score_u_, cohits_lambda_v_);
}

void BiGraph::cohits_propagation(const uint& count){
  cout << "cohits_propagation" << endl;
  for(uint i = 0;i < count;++i){
    cohits_one_propagate();
  }
}
