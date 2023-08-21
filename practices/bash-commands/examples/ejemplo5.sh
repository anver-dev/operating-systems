#!/bin/bash

echo "Compilando el programa binario"
gcc binario.c -o binario
for (( k=1; k<=$1; k++ ))
do
     echo "Ejecutando el programa con "
     ./binario $k &
     pid=$(ps -eo pid,user,comm | grep 'binario' | head -n 1 | awk {'print $1'})
     echo "Pid de la Raiz:"$pid
     pstree -cp $pid
     killall binario
done

