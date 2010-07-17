// -*- C++ -*-
#ifndef __class__CoHITS__
#define __class__CoHITS__

#include "bigraph.h"

class CoHITS : public BiGraph{
public:
  CoHITS(){};
  void set_init_score();
  void set_parameter(const double& u, const double& v);
  double calc_validation(const id_type& i);
  void propagate();
  void propagation(const uint& count);
private:
  void _set_init_score(const each_node_hash& nodes, d_hash& score1, d_hash& score2);
  void _propagate(const each_node_hash& nodes_1, d_hash& init_score, d_hash& score_1, d_hash& score_2);
  double lambda_u_;
  double lambda_v_;
};

#endif //__class__CoHITS__
