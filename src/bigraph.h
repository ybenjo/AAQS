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
typedef unordered_map<uint, list> node_list;

class BiGraph{
public:
  BiGraph(){};
protected:
  node_list v_1;
  node_list v_2;
  map<key, uint> weight;
  d_hash score_1_2;
  d_hash score_2_1;
};

#endif //__class__BiGraph__

