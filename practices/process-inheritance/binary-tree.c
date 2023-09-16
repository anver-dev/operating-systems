#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int i, v1, v2, raiz;
	raiz = getpid();
	int deep = atoi(argv[1]);

	for (i = 0; i < deep; i++)
	{
		if (fork())
		{
			if (fork())
			{
				wait(&v1);
				wait(&v2);

				if (raiz == getpid()) {
					printf("#Procesos creados: %d\n", WEXITSTATUS(v1) + WEXITSTATUS(v2) + 1);
					exit(0);
				} else {
					exit(WEXITSTATUS(v1) + WEXITSTATUS(v2) + 1);
				}
				break;
			}
		}
	}

	sleep(30);
	exit(1);
}