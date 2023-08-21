#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void createPetal(int num_petals)
{
    for (int i = 0; i < num_petals; i++)
    {
        pid_t petal_pid = fork();

        if (petal_pid == 0)
        {
            sleep(20); // Simulating a petal's task
            exit(0);
        }
        else if (petal_pid < 0)
        {
            perror("fork");
        }
    }
}

void createFlower(int num_flowers, int num_petals)
{

    for (int i = 0; i < num_flowers-1; i++)
    {
        
        pid_t flower_pid = fork();

        if (flower_pid == 0) // hijos
        {
            createPetal(num_petals);
            sleep(10); // Simulating a flower's task
            exit(0);
        }
        else if (flower_pid < 0)
        {
            break;
            perror("fork");
        }
    }
    sleep(10); // Simulating a stem's task
    exit(0);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s <num_tallos> <num_flores> <num_petals>\n", argv[0]);
        return 1;
    }

    int num_tallos = atoi(argv[1]);
    int num_flores = atoi(argv[2]);
    int num_petals = atoi(argv[3]);
    int stem_pid, i;

    int tid;
    int nivel;

    printf("NUM TALLOS :: %d\n", num_tallos);

    for (i = 0; i < num_tallos; i++)
    {
        tid = fork();
        if (tid != 0)
        { // tid!=0 proceso padre
            break;
        }
    }
    if (i == (num_tallos - 1))
    {
        createFlower(num_flores, num_petals);
        sleep(10);
    }

    sleep(10);
    return 0;
}
