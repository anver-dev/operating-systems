#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int A, N, i, j, v;

    A = 2;
    N = 4;

    for (j = 0; j < A; j++)
    {
        for (i = 0; i < N; i++)
        {
            if (!fork())
            {
                break;
            }
            
        }

        if (i == N) {
            for (i = 0; i < N; i++)
            {
                wait(&v);
                exit(0);
            }
            
        }
        
    }

    sleep(5);
    
}
