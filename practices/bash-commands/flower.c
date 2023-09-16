#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int i, j, k;

	int tallos = atoi(argv[1]);
	int flores = atoi(argv[2]);
	int petalos = atoi(argv[3]);

	for (i = 0; i < tallos + flores - 1; i++) {
		if (fork()) {
			if (i > tallos - 1) {
				if (!fork()) {
					for (j = 0; j < petalos; j++) {
						if (!fork())
							break;
					}
				}
			}
			break;
		}

		if (i == tallos + flores - 2) {
			if (!fork()) {
				for (int r = 0; r < petalos; r++) {
					if (!fork())
						break;
				}
			}
		}
	}

	sleep(30);
	return 0;
}