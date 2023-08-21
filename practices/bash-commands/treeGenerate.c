#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void createPetal(int count)
{
    for (int i = 0; i < count; i++)
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

void createFlower(int num_petals)
{
    pid_t flower_pid = fork();

    if (flower_pid == 0)
    {
        createPetal(num_petals);
        sleep(20); // Simulating a flower's task
        exit(0);
    }
    else if (flower_pid < 0)
    {
        perror("fork");
    }
}

void createStem(int num_flowers, int num_petals)
{
    pid_t stem_pid = fork();

    if (stem_pid == 0)
    {
        for (int i = 0; i < num_flowers; i++)
        {
            createFlower(num_petals);
        }
        sleep(20); // Simulating a stem's task
        exit(0);
    }
    else if (stem_pid < 0)
    {
        perror("fork");
    }
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

    for (i = 0; i < num_tallos; i++)
    {
        stem_pid = fork();

        if (stem_pid != 0)
        {
            break;
        }
    }

    if (i == (num_tallos - 1))
    {
        // createStem(num_flores, num_petals);
        printf("ULTIMO PROCESO");
        sleep(40); // Wait for the stem process to finish creating its flowers
    }
}
