#include <sys/types.h>
#include <unistd.h>

int main()
{
    int i;
    if (fork())
        for (i = 0; i < 2 && fork(); i++)
            fork();
    sleep(1000);
    return 0;
}
