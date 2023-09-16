#!/bin/bash

# Compila el programa en C
gcc binary-tree.c -o binary-tree

depth=$1

./binary-tree "$depth" &

main_pid=$!

pstree -p $main_pid
