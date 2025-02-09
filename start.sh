#!/bin/bash

clear

g++ -std=c++17 -o ./matriz/main.out ./matriz/main.cpp

if [ $? -eq 0 ]; then
    ./matriz/main.out
else
    echo "Erro na compilação"
fi
