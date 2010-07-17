// -*- C++ -*-
#ifndef __class__BiGraph__
#define __class__BiGraph__

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <math.h>
#include <cmath>
#include <fstream>
#include <string.h>
#include <tr1/unordered_map>

using namespace std;
using namespace std::tr1;

typedef unsigned int uint;
typedef string id_type;
typedef pair<id_type, id_type> key;
typedef set<id_type> list;
typedef map<id_type, double> d_hash;
typedef unordered_map<id_type, list> each_node_hash;

class BiGraph{
public:
  BiGraph(){};
  void set_edge(const id_type& n_u, const id_type& n_v, const uint& w);
  void set_prob();
  uint get_raw_weight(const id_type& n_u, const id_type& n_v);
  double get_prob(const id_type& n_u, const id_type& n_v);
  uint get_adj_size(const id_type& node);
  double get_score_u(const id_type& n_u);
  double get_score_v(const id_type& n_v);
protected:
  void _set_prob(const each_node_hash& h);
  each_node_hash nodes_u_;
  each_node_hash nodes_v_;
  map<key, uint> raw_weight_;
  map<key, double> prob_;
  d_hash _init_score_u_;
  d_hash _init_score_v_;
  d_hash score_u_;
  d_hash score_v_;
};

#endif //__class__BiGraph__
