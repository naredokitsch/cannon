#!/bin/bash
clear

source_file=$1
obj_file=$(echo $source_file | sed 's/\.cpp$//')

# Warnings are suppresed
# Can compile without glew library
c++ -std=c++11 $source_file -o $obj_file -lGLEW -framework OpenGL -framework GLUT -w \
&& ./$obj_file
