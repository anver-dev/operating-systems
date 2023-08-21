#!/bin/bash

# Compilar el programa
gcc treeGenerate.c -o treeGenerate

# Ejecutar el programa en segundo plano y guardar su PID
./treeGenerate "$@" &
program_pid=$!

# Esperar un poco para que los procesos se creen
sleep 10

echo "Árbol de procesos antes de matar procesos:"
pstree -p $program_pid

# Función para matar procesos de hojas a raíz
kill_tree() {
    local parent_pid=$1
    local children=$(pgrep -P $parent_pid)

    #for child_pid in $children; do
        #kill_tree $child_pid
    #done

    echo "Matando proceso: $parent_pid"
    #kill -9 $parent_pid
}

# Llamar a la función para matar los procesos
kill_tree $program_pid

echo "Árbol de procesos después de matar procesos:"
pstree -p $program_pid
