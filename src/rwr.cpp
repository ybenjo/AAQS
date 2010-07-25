#include "bigraph.h"

//RWR
void BiGraph::rwr_set_init(const id_type& query, const double& damping){
  cout << "rwr_set_init" << endl;
  score_u_[query] = 1.0;
  rwr_damping_ = damping;
}

double BiGraph::rwr_get_score(const id_type& query){
  string side = get_query_side(query);
  if(side == "u"){
    return score_u_[query];
  }else{
    return score_v_[query];
  }
}

void BiGraph::rwr_one_random_walk(const id_type& query){
  each_node_hash::iterator i;
  list::iterator j;
  d_hash next;

  //U side
  for(i = nodes_u_.begin();i != nodes_u_.end();++i){
    id_type from = i->first;
    list adj = i->second;
    double local_score = 0.0;
    if(from == query){
      local_score = rwr_damping_;
    }
    
    for(j = adj.begin();j != adj.end();++j){
      local_score += (1 - rwr_damping_) * get_prob(from, *j) * score_v_[*j];
    }
    next[from] = local_score;
  }

  //V side
  for(i = nodes_v_.begin();i != nodes_v_.end();++i){
    id_type from = i->first;
    list adj = i->second;
    double local_score = 0.0;
    
    for(j = adj.begin();j != adj.end();++j){
      local_score += (1 - rwr_damping_) * get_prob(from, *j) * score_u_[*j];
    }
    next[from] = local_score;
  }

  //Score update
  for(i = nodes_u_.begin();i != nodes_u_.end();++i){
    score_u_[i->first] = next[i->first];
  }
  
  for(i = nodes_v_.begin();i != nodes_v_.end();++i){
    score_v_[i->first] = next[i->first];
  }
}

void BiGraph::rwr_random_walk(const id_type& query, const uint& count){
  cout << "rwr_random_walk" << endl;
  for(uint i = 0;i < count;++i){
    rwr_one_random_walk(query);
  }
}
