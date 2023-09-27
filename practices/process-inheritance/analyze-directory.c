#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h> // Para trabajar con fechas y horas

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

void explore_directory(const char *dir_path)
{
    int v;
    DIR *dir;
    struct dirent *entry;

    dir = opendir(dir_path);

    if (!dir)
    {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)))
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        char entry_path[512];
        snprintf(entry_path, sizeof(entry_path), "%s/%s", dir_path, entry->d_name);

        // Si es un directorio crea un proceso para analizarlo sino imprime informacion del archivo
        if (entry->d_type == DT_DIR)
        {
            if (!fork())
            {
                printf("----------------------------------------\n");
                printf("PROCESO PID :: {%d}\n", getpid());
                printf("ANALIZANDO PATH :: {%s}\n", entry_path);
                printf("----------------------------------------\n");
                explore_directory(entry_path);
                exit(0);
            }
            totalChildProcess++;
        }
        else
        {
            print_file_info(entry_path);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[])
{
    int v;
    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <ruta_del_directorio>\n", argv[0]);
        return 1;
    }

    int root = getpid();

    printf("SOY EL PROCESO PADRE PID :: {%d}\n", getpid());
    const char *dir_path = argv[1];
    explore_directory(dir_path);

    if (root == getpid())
    {
        printf("########################################\n");
        printf("TOTAL DE PROCESOS HIJOS CREADOS :: {%d}\n", totalChildProcess);
        printf("########################################\n");
        for (int i = 0; i < totalChildProcess; i++)
        {
            wait(&v);
        }

        exit(0);
    } else {
        exit(1);
    }
}