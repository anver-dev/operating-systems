#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h> // Para trabajar con fechas y horas

#define MAX_PATH_LENGTH 512

int totalChildProcess = 0;

void print_file_info(const char *path)
{
    struct stat file_stat;

    if (stat(path, &file_stat) == -1)
    {
        perror("Error al obtener información del archivo");
    }

    printf("%-25s: %s\n", "Nombre", path);
    printf("%-26s: %ld bytes\n", "Tamaño", (long)file_stat.st_size);
    printf("%-25s: %s\n", "Tipo", S_ISDIR(file_stat.st_mode) ? "Directorio" : "Archivo");

    printf("%-25s: ", "Permisos");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf("\n");

    struct tm *mod_time = localtime(&file_stat.st_mtime);
    char mod_time_str[80];

    strftime(mod_time_str, sizeof(mod_time_str), "%Y-%m-%d %H:%M:%S", mod_time);
    printf("%-27s: %s\n", "Última modificación", mod_time_str);

    struct tm *access_time = localtime(&file_stat.st_atime);
    char access_time_str[80];

    strftime(access_time_str, sizeof(access_time_str), "%Y-%m-%d %H:%M:%S", access_time);
    printf("%-26s: %s\n", "Último acceso", access_time_str);

    printf("------------------------------------------------------------------------\n");
    printf("------------------------------------------------------------------------\n");
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <ruta_del_directorio>\n", argv[0]);
        return 1;
    }

    const char *dir_path = argv[1];
    DIR *dir = opendir(dir_path);

    if (!dir) {
        perror("opendir");
        return 1;
    }

    char *stack[MAX_PATH_LENGTH]; // Pila para rastrear los directorios
    int stack_size = 0;
    stack[stack_size++] = strdup(dir_path);

    while (stack_size > 0) {
        const char *current_dir = stack[--stack_size];

        printf("Explorando directorio: %s\n", current_dir);

        struct dirent *entry;
        dir = opendir(current_dir);

        while ((entry = readdir(dir))) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            char entry_path[MAX_PATH_LENGTH];
            snprintf(entry_path, sizeof(entry_path), "%s/%s", current_dir, entry->d_name);

            struct stat file_stat;
            if (stat(entry_path, &file_stat) == -1) {
                perror("Error al obtener información del archivo");
                continue;
            }

            if (S_ISDIR(file_stat.st_mode)) {
                // Si es un directorio, lo agregamos a la pila y creamos un proceso hijo
                stack[stack_size++] = strdup(entry_path);
                totalChildProcess++;

                if (!fork())
                {
                    printf("----------------------------------------\n");
                    printf("PROCESO PID :: {%d}\n", getpid());
                    printf("ANALIZANDO PATH :: {%s}\n", entry_path);
                    printf("----------------------------------------\n");
                    closedir(dir); // Cerrar el directorio en el proceso hijo
                    continue; // Volver al bucle while para el nuevo proceso hijo
                }
            } else {
                print_file_info(entry_path);
            }
        }

        closedir(dir);
    }

    // Esperar a que todos los procesos hijos terminen
    while (totalChildProcess > 0) {
        wait(NULL);
        totalChildProcess--;
    }

    return 0;
}
