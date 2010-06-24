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
typedef pair<uint, uint> key;
typedef set<uint> list;
typedef map<key, double> d_hash;
typedef unordered_map<uint, list> each_node_hash;

class BiGraph{
public:
  BiGraph(){};
  
  BiGraph(double v1, double v2){
    v_1 = v1;
    v_2 = v2;
  };
  
  void set_edge(uint n1, uint n2, uint w);
  void set_weight();
  uint get_adj_size(uint node);
protected:
  each_node_hash hash_n1;
  each_node_hash hash_n2;
  map<key, uint> raw_weight;
  map<key, double> weight;
  d_hash score_1;
  d_hash score_2;
  double v_1;
  double v_2;
};

#endif //__class__BiGraph__

