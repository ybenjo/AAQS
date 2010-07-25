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
#include <tr1/unordered_set>

using namespace std;
using namespace std::tr1;

typedef unsigned int uint;
typedef string id_type;
typedef pair<id_type, id_type> key;
typedef vector<id_type> list;
typedef unordered_map<id_type, double> d_hash;
typedef unordered_map<id_type, list> each_node_hash;

class BiGraph{
public:
  BiGraph(){};
  void set_edge(const id_type& n_u, const id_type& n_v, const uint& w);
  void set_prob();
  void set_entropy();
  uint get_raw_weight(const id_type& n_u, const id_type& n_v);
  double get_prob(const id_type& n_u, const id_type& n_v);
  uint get_adj_size(const id_type& node);
  double get_score_u(const id_type& n_u);
  double get_score_v(const id_type& n_v);
  string get_query_side(const id_type& query);

  BiGraph generate_sub_graph(const id_type& from, const int& depth, const string& side);

  void read_file(const char *filename);
  vector<string> split(string s, string c);

  //CoHITS
  void cohits_set_init_score();
  void cohits_set_parameter(const double& u, const double& v);
  double cohits_calc_validation(const id_type& i);
  void cohits_one_propagate();
  void cohits_propagation(const uint& count);
  void cohits_output(const char *filename, const int& limit);

  //hitting time
  void set_hitting_prob();
  double get_hitting_prob(const id_type& from, const id_type& to);
  double hitting_get_hitting_score(const id_type& query);
  void hitting_one_random_walk(const id_type& query);
  void hitting_random_walk(const id_type& query, const uint& count);
  void hitting_output(const char *filename, const int& limit);

protected:
  void _set_prob(const each_node_hash& h);
  void _one_side_depth_search(list& now, list& checked, set<key>& sub_list, const string& side);
  each_node_hash nodes_u_;
  each_node_hash nodes_v_;
  map<key, uint> raw_weight_;
  map<key, double> prob_;
  d_hash _init_score_u_;
  d_hash _init_score_v_;
  d_hash score_u_;
  d_hash score_v_;

  //CoHITS
  void _cohits_set_init_score(const each_node_hash& nodes, d_hash& score1, d_hash& score2);
  void _cohits_one_propagate(const each_node_hash& nodes_1, d_hash& init_score, d_hash& score_1, d_hash& score_2, const double& param);
  double cohits_lambda_u_;
  double cohits_lambda_v_;

  //hitting time
  map<key, double> hitting_prob_;
  d_hash hitting_score_;
  
};

#endif //__class__BiGraph__
