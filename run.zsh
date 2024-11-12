#!/bin/bash

filename=$1
if [[ -f ~/prog/opengl/tetris/$filename ]]; then
  gcc $filename -lGL -lglut -lm -lGLU -lGLEW -o ${filename%.*} && ./${filename%.*}
else
  echo  "$filename não encontrado."
fi
