#!/bin/bash

# Solicitar la cantidad de cadenas a generar
read -p "Ingresa la cantidad de cadenas aleatorias a generar: " N

# Solicitar si se desea almacenar en un archivo
read -p "¿Deseas almacenar las cadenas en un archivo? (s/n): " store_in_file

generate_random_string() {
    local length=$((8 + RANDOM % 5)) # Entre 8 y 12 caracteres
    local num_digits=2
    local num_uppercase=2
    local num_lowercase=2
    local num_special=2

    # Generar la cadena aleatoria
    local random_string=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9@#$%&' | fold -w "$length" | head -n 1)

    while true; do
        if [[ $(grep -o '[0-9]' <<< "$random_string" | wc -l) -ge "$num_digits" &&
              $(grep -o '[A-Z]' <<< "$random_string" | wc -l) -ge "$num_uppercase" &&
              $(grep -o '[a-z]' <<< "$random_string" | wc -l) -ge "$num_lowercase" &&
              $(grep -o '[@#$%&]' <<< "$random_string" | wc -l) -ge "$num_special" ]]; then
            echo "$random_string"
            break
        else
            random_string=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9@#$%&' | fold -w "$length" | head -n 1)
        fi
    done
}

# Generar y mostrar o almacenar las cadenas
if [[ "$store_in_file" == "s" ]]; then
    read -p "Ingresa el nombre del archivo para almacenar las cadenas: " file_name
    for ((i = 1; i <= N; i++)); do
        generated_string=$(generate_random_string)
        echo "Cadena $i: $generated_string" | tee -a "$file_name"
    done
    echo "Cadenas generadas y almacenadas en '$file_name'."
else
    for ((i = 1; i <= N; i++)); do
        generated_string=$(generate_random_string)
        echo "Cadena $i: $generated_string"
    done
fi
