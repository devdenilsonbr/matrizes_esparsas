#!/bin/bash

clear

g++ -o main.out main.cpp

if [ $? -eq 0 ]; then
    ./main.out
else
    echo "Erro na compilação"
fi
