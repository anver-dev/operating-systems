#!/bin/bash

read -p "Ingresa el nombre del archivo de la bitácora (o presiona Enter para mostrar en consola): " LOG_FILE

# Intervalo de tiempo en segundos para monitorear
INTERVAL=15

# Función para escribir en la bitácora o mostrar en consola
write_to_log_or_console() {
    local timestamp="$(date '+%Y-%m-%d %H:%M:%S')"
    local user_info="$(w -h)"
    
    if [ -n "$LOG_FILE" ]; then
        echo "$timestamp - Información detallada de usuarios:" >> "$LOG_FILE"
        echo "$user_info" >> "$LOG_FILE"
        echo "" >> "$LOG_FILE" 

        while read -r user _; do
            ps aux | grep "^$user" | awk '{printf "%-10s %-10s %-6s %-6s %-20s %-20s\n", $1, $2, $3, $4, $9, $10}' >> "$LOG_FILE"
            echo "" >> "$LOG_FILE"
        done <<< "$user_info"
    else
        echo "$timestamp - Información detallada de usuarios:"
        echo "$user_info"
        echo ""  

        while read -r user _; do
            ps aux | grep "^$user" | awk '{printf "%-10s %-10s %-6s %-6s %-20s %-20s\n", $1, $2, $3, $4, $9, $10}'
            echo ""
        done <<< "$user_info"
    fi
}

while true; do
    write_to_log_or_console
    sleep "$INTERVAL"
done
