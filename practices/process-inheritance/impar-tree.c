#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char *argv[])
{
    int nivel = atoi(argv[1]);

    int i, j, sub_nivel, raiz, sub_raiz, v1, v2;
    int totalProcess;

    sub_nivel = nivel - 1;
    raiz = getpid();

    for (j = nivel - 1; j >= 0; j -= 2) { // Total de impares
        if (fork()) { // Se crea un nuevo proceso hijo y el proceso padre entra en este bloque
            wait(&v1);
            
            for (i = 0; i < j; i++) {
                if (fork()) { // Se crean los subniveles
                    wait(&v1);
                    wait(&v1);
                    
                    if (raiz == getpid()) {
                        printf("#Procesos creados: %d\n", WEXITSTATUS(v1) + 1);
                        exit(0);
                    } else {
                        exit(WEXITSTATUS(v1) + 1);
                    }

                    break;
                }
            }

            exit(WEXITSTATUS(v1) + 1);
            break;
        }
    }

    sleep(3);
    exit(1); 
}