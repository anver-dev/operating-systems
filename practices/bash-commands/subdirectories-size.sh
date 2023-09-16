#!/bin/bash

# Función para convertir el tamaño en bytes a una unidad legible por personas
human_readable_size() {
    local size=$1

    if [ $size -lt 1024 ]; then
        echo "${size}B"
    elif [ $size -lt 1048576 ]; then
        echo "$((size / 1024))KB"
    elif [ $size -lt 1073741824 ]; then
        echo "$((size / 1048576))MB"
    else
        echo "$((size / 1073741824))GB"
    fi
}

# Función para iterar a través de los directorios y mostrar tamaños
get_directory_sizes() {
    local dir=$1

    size=$(du -s "$dir" | cut -f1)
    readable_size=$(human_readable_size $size)
    echo "Tamaño de '$dir': $readable_size"

    subdirectories=$(find "$dir" -maxdepth 1 -mindepth 1 -type d)
    for subdir in $subdirectories; do
        get_directory_sizes "$subdir"
    done
}

# Obtener la lista de directorios en la ruta actual
directories=$(find . -maxdepth 1 -type d)

# Iterar a través de los directorios y mostrar el tamaño en unidades legibles por personas
for dir in $directories; do
    if [ "$dir" != "." ]; then
        get_directory_sizes "$dir"
    fi
done
