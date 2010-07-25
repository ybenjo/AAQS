
#include <unistd.h>

#include "bigraph.h"

int main(int argc, char **argv){
  cout << "Start" << endl;
  char *input_filename, *output_filename;
  int result, iteration, depth, mode, size, entropy;
  double param_u, param_v, damping;
  string query;
  while(1){
    result = getopt(argc, argv, "i:o:m:d:t:u:v:s:e:q:c:");
    if(result == -1) break;
    
    switch(result){
    case 'i' : input_filename = optarg; break; 
    case 'o' : output_filename = optarg; break;
    case 'm' : mode = atoi(optarg); break; 
    case 'd' : depth = atoi(optarg); break;
    case 't' : iteration = atoi(optarg); break;
    case 'u' : param_u = atof(optarg); break; 
    case 'v' : param_v = atof(optarg); break;
    case 's' : size = atoi(optarg); break;
    case 'e' : entropy = atoi(optarg); break;
    case 'q' : query = string(optarg); break;
    case 'c' : damping = atof(optarg); break;
    }
    optarg = NULL; 
  }

  BiGraph* g = new BiGraph;
  g->read_file(input_filename);
  switch(mode){
  case 1:
    //random walk with restart
    {
      string side = g->get_query_side(query);
      BiGraph g_sub = g->generate_sub_graph(query, depth, side);
      delete g;
      g_sub.set_prob();
      if(entropy == 1){
	g_sub.set_entropy();
      }
      g_sub.rwr_set_init(query, damping);
      g_sub.rwr_random_walk(query, iteration);
      g_sub.output_double_score(output_filename, size);
      break;
    }
  case 2:
    //entropy biased model
    {
      string side = g->get_query_side(query);
      BiGraph g_sub = g->generate_sub_graph(query, depth, side);
      delete g;
      g_sub.set_prob();
      g_sub.set_entropy();
      g_sub.rwr_set_init(query, damping);
      g_sub.rwr_random_walk(query, iteration);
      g_sub.output_double_score(output_filename, size);
      break;
    }
    
  case 3:
    //generalized Co-HITS
    {
      string side = g->get_query_side(query);
      BiGraph g_sub = g->generate_sub_graph(query, depth, side);
      delete g;
      g_sub.set_prob();
      if(entropy == 1){
	g_sub.set_entropy();
      }
      g_sub.cohits_set_init_score();
      g_sub.cohits_set_parameter(param_u, param_v);
      g_sub.cohits_propagation(iteration);
      g_sub.output_double_score(output_filename, size);
      break;
    }
  case 4:
    //hitting time
    {
      string side = g->get_query_side(query);
      BiGraph g_sub = g->generate_sub_graph(query, depth, side);
      delete g;
      g_sub.set_prob();
      if(entropy == 1){
	g_sub.set_entropy();
      }
      g_sub.set_hitting_prob();
      g_sub.hitting_random_walk(query, iteration);
      g_sub.hitting_output(output_filename, size);
      break;
    }
  }
}
