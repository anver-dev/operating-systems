#!/bin/bash

# Solicitar el nombre del archivo de la bitácora al usuario
read -p "Ingresa el nombre del archivo de la bitácora (o presiona Enter para mostrar en consola): " LOG_FILE

# Intervalo de tiempo en segundos para monitorear
INTERVAL=15 # Cambia esto al intervalo deseado en segundos (por ejemplo, 300 segundos = 5 minutos)

# Función para escribir en la bitácora o mostrar en consola
write_to_log_or_console() {
    local timestamp="$(date '+%Y-%m-%d %H:%M:%S')"
    local user_info="$(w -h)"
    
    if [ -n "$LOG_FILE" ]; then
        echo "$timestamp - Información detallada de usuarios:" >> "$LOG_FILE"
        echo "$user_info" >> "$LOG_FILE"
        echo "" >> "$LOG_FILE"  # Agregar una línea en blanco para separar la información
        # Obtener información detallada de procesos para cada usuario
        while read -r user _; do
            ps aux | grep "^$user" | awk '{printf "%-10s %-10s %-6s %-6s %-20s %-20s\n", $1, $2, $3, $4, $9, $10}' >> "$LOG_FILE"
            echo "" >> "$LOG_FILE"  # Agregar una línea en blanco para separar los resultados
        done <<< "$user_info"
    else
        echo "$timestamp - Información detallada de usuarios:"
        echo "$user_info"
        echo ""  # Agregar una línea en blanco para separar la información
        # Obtener información detallada de procesos para cada usuario
        while read -r user _; do
            ps aux | grep "^$user" | awk '{printf "%-10s %-10s %-6s %-6s %-20s %-20s\n", $1, $2, $3, $4, $9, $10}'
            echo ""  # Agregar una línea en blanco para separar los resultados
        done <<< "$user_info"
    fi
}

# Bucle infinito para monitorear cada intervalo de tiempo
while true; do
    write_to_log_or_console
    sleep "$INTERVAL"
done
