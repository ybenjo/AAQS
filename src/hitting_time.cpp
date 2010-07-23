#include "bigraph.h"

void BiGraph::set_hitting_prob(){
  cout << "set_hitting_prob" << endl;
  each_node_hash::iterator i;
  for(i = nodes_u_.begin();i != nodes_u_.end();++i){
    id_type from = i->first;
    list adj_from = i->second;
    for(list::iterator j = adj_from.begin();j != adj_from.end();++j){
      id_type tmp = *j;
      list adj_to = nodes_v_[tmp];
      for(list::iterator to = adj_to.begin();to != adj_to.end();++to){
	hitting_prob_[key(from, *to)] += get_prob(from, tmp) * get_prob(tmp, *to);
      }
    }
  }
}

double BiGraph::get_hitting_prob(const id_type& from, const id_type& to){
  return hitting_prob_[key(from, to)];
}

double BiGraph::hitting_get_hitting_score(const id_type& query){
  return hitting_score_[query];
}

void BiGraph::hitting_one_random_walk(const id_type& query){
  each_node_hash::iterator i, j;
  d_hash h_t_1;
  
  for(i = nodes_u_.begin();i != nodes_u_.end();++i){
    id_type from = i->first;
    h_t_1[from] += 1;
    for(j = nodes_u_.begin();j != nodes_u_.end();++j){
      id_type to = j->first;
      if(query != to){
	h_t_1[from] += get_hitting_prob(from, to) * hitting_score_[to];
      }
    }
  }

  for(d_hash::iterator t = h_t_1.begin();t != h_t_1.end();++t){
    hitting_score_[t->first] = t->second;
  }
}

void BiGraph::hitting_random_walk(const id_type& query, const uint& count){
  cout << "hitting_random_walk" << endl;
  for(uint i = 0;i < count;++i){
    hitting_one_random_walk(query);
  }
}

void BiGraph::hitting_output(const char *filename, const int& limit){
  cout << "hitting_output" << endl;
  std::ofstream ofs;
  multimap<double, id_type> output;

  for(d_hash::iterator i = hitting_score_.begin();i != hitting_score_.end();++i){
    output.insert(make_pair(i->second, i->first));
  }
  
  ofs.open(filename);
  multimap<double, id_type>::reverse_iterator i;
  int count = 1;
  for(i = output.rbegin();i != output.rend();++i){
    if(count > limit) break;
    ofs << i->second << "," << i->first << endl;
    ++count;
  }
  ofs.close();
}
