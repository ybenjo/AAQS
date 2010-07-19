#include "bigraph.h"
void BiGraph::set_edge(const id_type& n_u, const id_type& n_v, const uint& w){
  if (n_u == n_v){
    exit(EXIT_FAILURE);
  }

  nodes_u_[n_u].insert(n_v);
  nodes_v_[n_v].insert(n_u);
  raw_weight_[key(n_u, n_v)] = w;
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

BiGraph BiGraph::generate_sub_graph(const id_type& from, const int& depth, const int& side){

  list next, checked;
  set<key> sub_list;
  int lim = depth;
  if(side == 2){
    ++lim;
  }
  next.insert(from);
  
  for(int count = 0;count < lim;++count){
    if(count % 2 == 0){
      list tmp;
      for(list::iterator u = next.begin();u != next.end();++u){
	if(checked.find(*u) == checked.end()){
	  list connected = nodes_u_[*u];
	  for(list::iterator v = connected.begin();v != connected.end();++v){
	    tmp.insert(*v);
	    sub_list.insert(key(*u, *v));
	  }
	  checked.insert(*u);
	}
      }

      next.clear();
      for(list::iterator t = tmp.begin();t != tmp.end();++t){
	next.insert(*t);
      }
    }else{
      list tmp;
      for(list::iterator v = next.begin();v != next.end();++v){
	if(checked.find(*v) == checked.end()){
	  list connected = nodes_v_[*v];
	  for(list::iterator u = connected.begin();u != connected.end();++u){
	    tmp.insert(*u);
	    sub_list.insert(key(*u, *v));
	  }
	  checked.insert(*v);
	}
      }
      next.clear();
      for(list::iterator t = tmp.begin();t != tmp.end();++t){
	next.insert(*t);
      }
    }
  }

  BiGraph sub_graph;
  set<key>::iterator z;
  for(z = sub_list.begin();z != sub_list.end();++z){
    id_type u = z->first;
    id_type v = z->second;
    sub_graph.set_edge(u, v, get_raw_weight(u, v));
  }
  return sub_graph;
}
