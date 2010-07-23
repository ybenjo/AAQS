#include "bigraph.h"
void BiGraph::set_edge(const id_type& n_u, const id_type& n_v, const uint& w){
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
  cout << "set_prob" << endl;
  _set_prob(nodes_u_);
  _set_prob(nodes_v_);
}

void BiGraph::set_entropy(){
  each_node_hash::iterator i;
  d_hash iqf;
  d_hash cfiqf;
  for(i = nodes_v_.begin();i != nodes_v_.end();++i){
    iqf[i->first] = log(nodes_u_.size() / i->second.size());
  }

  for(i = nodes_u_.begin();i != nodes_u_.end();++i){
    id_type u = i->first;
    list adj = i->second;
    
    for(list::iterator j = adj.begin();j != adj.end();++j){
      cfiqf[u] += get_raw_weight(u, *j) * iqf[*j];
    }

    for(list::iterator j = adj.begin();j != adj.end();++j){
      if(iqf[*j] == 0){
	prob_[key(u, *j)] = 0.0;
      }else{
	prob_[key(u, *j)] = get_raw_weight(u, *j) * iqf[*j] / cfiqf[u];
      }
    }
  }
  
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

BiGraph BiGraph::generate_sub_graph(const id_type& from, const int& depth, const string& side){

  list now, checked;
  set<key> sub_list;
  int lim = depth;
  if(side == "v"){
    ++lim;
  }
  now.insert(from);
  
  for(int count = 0;count < lim;++count){
    if(count % 2 == 0){
      _one_side_depth_search(now, checked, sub_list, "u");
    }else{
      _one_side_depth_search(now, checked, sub_list, "v");
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


void BiGraph::_one_side_depth_search(list& now, list& checked, set<key>& sub_list, const string& side){
  
  each_node_hash side_hash;
  list next;
  
  if(side == "u"){
    side_hash = nodes_u_;
  }else{
    side_hash = nodes_v_;
  }

  for(list::iterator x = now.begin();x != now.end();++x){
    if(checked.find(*x) == checked.end()){
      list connected = side_hash[*x];
      if(connected.size() != 0){
	for(list::iterator y = connected.begin();y != connected.end();++y){
	  if(side == "u"){
	    sub_list.insert(key(*x, *y));
	  }else{
	    sub_list.insert(key(*y, *x));
	  }
	  next.insert(*y);
	}
	checked.insert(*x);
      }else{
	//開始地点がV側だった場合nextに追加
	next.insert(*x);
      }
    }
  }
  now.clear();
  for(list::iterator x = next.begin(); x != next.end(); ++x){
    now.insert(*x);
  }
}


void BiGraph::read_file(const char *filename){
  cout << "Reading " << filename << endl;
  ifstream ifs;
  vector<string> ret;
  string line;
  ifs.open(filename, ios::in);

  while(getline(ifs, line)){
    ret = split(line,"\t");
    string u = ret.at(0);
    string v = ret.at(1);
    uint w = atoi(ret.at(2).c_str());
    set_edge(u, v, w);
  }
  ifs.close();
}

//split
vector<string> BiGraph::split(string s, string c){
  vector<string> ret;
  for(int i=0, n; i <= s.length(); i=n+1){
    n = s.find_first_of(c, i);
    if(n == string::npos) n = s.length();
    string tmp = s.substr(i, n-i);
    ret.push_back(tmp);
  }
  return ret;
}

string BiGraph::get_query_side(const id_type& query){
  string side = "u";
  each_node_hash::iterator flag = nodes_v_.find(query);
  if(flag != nodes_v_.end()){
    side = "v";
  }
  return side;
}
