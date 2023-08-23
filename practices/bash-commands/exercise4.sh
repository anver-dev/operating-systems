#!/bin/bash

# Compila el programa en C
gcc programa.c -o flower_program

# Verifica si se proporcionaron los argumentos adecuados
if [ $# -ne 3 ]; then
    echo "Uso: $0 <tallos> <flores> <petalos>"
    exit 1
fi

tallos=$1
flores=$2
petalos=$3

# Ejecuta el programa en C con los argumentos proporcionados en segundo plano
./flower_program "$tallos" "$flores" "$petalos" &

# Espera un poco para que los procesos tengan tiempo de ejecutarse
sleep 2

# Obtén el PID del proceso principal del programa en C
main_pid=$!

# Muestra el árbol de procesos antes de eliminar los pétalos
echo "Árbol de procesos antes de eliminar los pétalos:"
pstree -p $main_pid

# Calcula el número total de procesos de tallos y flores
total_processes=$((tallos + (2 * flores)))
total_tallo_flor=$((tallos + (flores)))

# Obtén los PIDs de los procesos de las "flores" utilizando pstree y awk
flower_pids=$(pstree -p $main_pid | grep -oP 'flower_program\(\K\d+(?=\))' | awk 'NR > '$total_tallo_flor' && NR <= '$total_processes'')

echo "Flower PIDs: $flower_pids"
sleep 1
# Itera a través de los PIDs de las "flores" y termina los procesos de los "pétalos"
for flower_pid in $flower_pids; do
    kill -9 "$flower_pid"
done

# Espera un poco para que los procesos de los pétalos sean terminados
sleep 2

# Muestra el árbol de procesos después de eliminar los pétalos
echo "Árbol de procesos después de eliminar los pétalos:"
pstree -p $main_pid


steam_pids=$(pstree -p $main_pid | grep -oP 'flower_program\(\K\d+(?=\))' | awk 'NR > '$total_tallo_flor' && NR <= '$total_processes'')

# Limpia el archivo ejecutable
rm flower_program
