#!/bin/bash

# Compila el programa en C
gcc odd-tree.c -o odd-tree

depth=$1

./odd-tree "$depth" &

main_pid=$!

pstree -p $main_pid

sleep 3
