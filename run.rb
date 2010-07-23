require "yaml"
require "optparse"

option = Hash.new
config_yaml = YAML.load_file("./config.yaml")

option["-m"] = config_yaml["MODE"]
option["-t"] = config_yaml["ITERATION"]
option["-d"] = config_yaml["DEPTH"]
option["-s"] = config_yaml["SIZE"]
option["-e"] = config_yaml["ENTROPY"] ? 1 : 0
option["-u"] = config_yaml["LAMBDA_U"]
option["-v"] = config_yaml["LAMBDA_V"]

OptionParser.new {|opt|
  opt.on('-i [OPTION]') {|v| option["-i"] = v}
  opt.on('-o [OPTION]') {|v| option["-o"] = v}
  opt.on('-m [OPTION]') {|v| option["-m"] = v}
  opt.on('-t [OPTION]') {|v| option["-t"] = v.to_i}
  opt.on('-d [OPTION]') {|v| option["-d"] = v.to_i}
  opt.on('-s [OPTION]') {|v| option["-s"] = v.to_i}
  opt.on('-e [OPTION]') {|v| option["-e"] = 1 if v == "true"}
  opt.on('-u [OPTION]') {|v| option["-u"] = v.to_f}
  opt.on('-v [OPTION]') {|v| option["-v"] = v.to_f}
  opt.on('-q [OPTION]') {|v| option["-q"] = "\"#{v}\""}
  opt.parse!(ARGV)
}

dir, fname = File::split(option["-i"])
option["-o"] = "#{dir}/result_#{fname.gsub(/\.txt/,"")}_#{option["-q"]}.txt" if !option.include?("-o")
command = "./main #{option.to_a.join(" ")}"
puts command
`#{command}`

