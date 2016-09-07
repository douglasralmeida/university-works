#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
	char* alfabeto = "abcdefghijklmnopqrstuvwxyz";
	char palavra[11];
	FILE* arquivo;
	int j, x;
	unsigned long long i, q;
	
	srand(time(NULL));
	q = atoi(argv[2]);
	arquivo = fopen(argv[1], "wt");
	for (i = 0; i < q; i++) {
		for (j = 0; j < 10; j++)
		{
			x = rand() % 26;
			palavra[j] = alfabeto[x];
		}
		fprintf(arquivo, "%s ", palavra);
	}

	fclose(arquivo);
	exit(EXIT_SUCCESS);
}
