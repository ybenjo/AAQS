# -*- coding: utf-8 -*-
#/usr/bin/env ruby

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
option["-c"] = config_yaml["DAMPING"]

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
  opt.on('-q [OPTION]') {|v|
    query = v.split(" ").sort.join(" ")
    option["-q"] = "\"#{query}\""
  }
  opt.on('-c [OPTION]') {|v| option["-c"] = v.to_f}
  opt.parse!(ARGV)
}

if !option.include?("-i")
  puts "入力ファイルを指定してください"
  exit()
elsif !File.exist?(option["-i"])
  puts "入力ファイル(#{option["-i"]})が見つかりません"
  exit()
elsif !option.include?("-q")
  puts "クエリを指定してください"
  exit()
end

dir, fname = File::split(option["-i"])
option["-o"] = "#{dir}/result_#{fname.gsub(/\.txt/,"")}_#{option["-q"]}.txt" if !option.include?("-o")
command = "./main #{option.to_a.join(" ")}"
puts command
system command

