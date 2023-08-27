#!/bin/bash

# Compila el programa en C
gcc programa.c -o flower_program

if [ $# -ne 3 ]; then
    echo "Uso: $0 <tallos> <flores> <petalos>"
    exit 1
fi

tallos=$1
flores=$2
petalos=$3

./flower_program "$tallos" "$flores" "$petalos" &

main_pid=$!

sleep 2

# Función recursiva para obtener los PIDs descendientes
get_all_children_pids() {
    local parent_pid=$1
    local descendants=($(pgrep -P $parent_pid))

    for pid in "${descendants[@]}"; do
        echo $pid
        get_all_children
    _pids $pid
    done
}
# Función para obtener los PIDs de los hijos de un proceso
get_children_pids() {
    local parent_pid=$1
    local children_pids=($(pgrep -P $parent_pid))

    echo "${children_pids[@]}"
}

kill_petals() {
    # Obtén los PIDs de todos los procesos descendientes del main PID de manera recursiva
    all_pids=($main_pid)
    all_pids+=($(get_all_children
_pids $main_pid))

    # Obtén los PIDs de los procesos que tienen hijos
    pids_with_children=()
    for pid in "${all_pids[@]}"; do
        children_pids=($(get_children_pids $pid))
        if [ ${#children_pids[@]} -gt 0 ]; then
            pids_with_children+=($pid)
        fi
    done

    # Obtén los PIDs de los procesos que no tienen más hijos
    pids_without_children=()
    for pid in "${all_pids[@]}"; do
        if [[ ! " ${pids_with_children[@]} " =~ " $pid " ]]; then
            pids_without_children+=($pid)
        fi
    done

    parent_pids_without_children=()
    for pid in "${pids_without_children[@]}"; do
        parent_pid=$(ps -o ppid= -p $pid)
        if [ -n "$parent_pid" ] && [[ ! " ${parent_pids_without_children[@]} " =~ " $parent_pid " ]]; then
            parent_pids_without_children+=($parent_pid)
        fi
    done

    # Termina los procesos padres de los procesos sin más hijos
    for pid in "${parent_pids_without_children[@]}"; do
        kill -9 "$pid"
    done
}

kill_flowers() {
    last_tallo_pid=$(pstree -p $main_pid | grep -oP 'flower_program\(\K\d+(?=\))' | tail -n +$((tallos)) | head -n 1)

    if [ $tallos -eq 1 ]; then
        last_tallo_pid=$(pstree -p $main_pid | grep -oP 'flower_program\(\K\d+(?=\))' | tail -n +$((tallos+1)) | head -n 1)
    fi

    echo "Ultimo tallo: $last_tallo_pid"
    kill -9 "$last_tallo_pid"
}

kill_steam() {
    kill -9 "$main_pid"
}

echo "Árbol de procesos antes de iniciar poda:"
pstree -p $main_pid
echo "=========================================================================================="

echo "Eliminando petalos..."
echo ""
sleep 2

kill_petals

echo "Árbol de procesos despues de eliminar los pétalos:"
pstree -p $main_pid
echo "=========================================================================================="

echo "Eliminando flores..."
echo ""
sleep 2

kill_flowers

echo "Árbol de procesos despues de eliminar las flores:"
pstree -p $main_pid
echo "=========================================================================================="

echo "Eliminando tallo..."
echo ""
sleep 2

kill_steam

echo "Árbol de procesos despues de eliminar el tallo:"
pstree -p $main_pid
echo "=========================================================================================="
echo "PODA FINALIZADA"
