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
typedef map<key, double> d_hash;
typedef unordered_map<id_type, list> each_node_hash;

class BiGraph{
public:
  BiGraph(){};

  BiGraph(double v1, double v2){
    v_1_ = v1;
    v_2_ = v2;
  };
  
  void set_edge(id_type n1, id_type n2, uint w);
  void set_weight();
  void _set_weight(each_node_hash h);
  uint get_raw_weight(id_type n1, id_type n2);
  double get_weight(id_type n1, id_type n2);
  uint get_adj_size(id_type node);
protected:
  each_node_hash hash_n1_;
  each_node_hash hash_n2_;
  map<key, uint> raw_weight_;
  map<key, double> weight_;
  d_hash score_1_;
  d_hash score_2_;
  double v_1_;
  double v_2_;
};

#endif //__class__BiGraph__

