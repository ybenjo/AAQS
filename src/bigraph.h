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
typedef uint id_type;
typedef pair<id_type, id_type> key;
typedef set<id_type> list;
typedef map<uint, double> d_hash;
typedef unordered_map<id_type, list> each_node_hash;

class BiGraph{
public:
  BiGraph(){};

  BiGraph(double u, double v){
    lambda_u_ = u;
    lambda_v_ = v;
  };
  
  void set_edge(const id_type n_u, const id_type n_v, const uint w);
  void set_weight();
  uint get_raw_weight(const id_type n_u, const id_type n_v);
  double get_weight(const id_type n_u, const id_type n_v);
  void set_parameter(const double u, const double v);
  uint get_adj_size(const id_type node);
  void set_init_score();
  double get_score_u(const id_type n_u);
  double get_score_v(const id_type n_v);
  double calc_validation(const id_type i);
  void propagete();
protected:
  void _set_weight(const each_node_hash h);
  void _set_init_score(const each_node_hash nodes, d_hash &score1, d_hash &score2);
  each_node_hash nodes_u_;
  each_node_hash nodes_v_;
  map<key, uint> raw_weight_;
  map<key, double> weight_;
  d_hash _init_score_u_;
  d_hash _init_score_v_;
  d_hash score_u_;
  d_hash score_v_;
  double lambda_u_;
  double lambda_v_;
};

#endif //__class__BiGraph__
