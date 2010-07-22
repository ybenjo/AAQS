#include <unistd.h>

#include "bigraph.h"

int main(int argc, char **argv){
  char *input_filename, *output_filename;
  int result, iteration, depth, mode, size;
  double param_u, param_v;
  
  while(1){ 
    result = getopt(argc, argv, "i:o:m:d:t:u:v:s:");
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
    default :;
    }
    optarg = NULL; 
  }

  BiGraph g;
  g.read_file(input_filename);
  switch(mode){
  case 1:
    g.set_prob();
    g.cohits_set_init_score();
    g.cohits_set_parameter(param_u, param_v);
    g.cohits_propagation(iteration);
    g.cohits_output(output_filename, size);
    break;
  default : break;
  }
}
