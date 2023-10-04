#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int nivel = atoi(argv[1]);

    int i, j, raiz, v1, v2, v3;

    raiz = getpid();

    for (j = nivel - 1; j > 0; j -= 2)
    {
        if (fork())
        {
            break;
        }
    }

    for (i = 0; i < j; i++)
    {
        if (fork())
        {
            break;
        }
    }

    sleep(3);

    if (i == j) {
        exit(1);
    }

    if (i > 0) {
        wait(&v1);
        exit(WEXITSTATUS(v1) + 1);
    }

    if (i == 0) {
        wait(&v1);
        wait(&v2);
    }

    if (raiz == getpid()) {
        printf("#Procesos creados: %d\n", WEXITSTATUS(v1) + WEXITSTATUS(v2) + 1);
        exit(0);
    } else {
        exit(WEXITSTATUS(v1) + WEXITSTATUS(v2) + 1);
    }
}