/* gerador de entradas */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int gera_numero(int m, int n) {
	return m + (rand() % (n+1));
}

void gera_palavra(int n, char texto[100]) {
	int i;

	for (i = 0; i < n; i++)
		texto[i] = 97 + (rand() % 26);
	texto[n] = '\0';		
}


void gerar_variaveis(int n, int m, int e, int l, int k, FILE* arquivo) {
	fprintf(arquivo, "%d %d %d %d %d\n", n, m, e, l, k);
}

void gerar_livros(int q, FILE* arquivo) {
	int i;
	int x;
	char nomelivro[100];

	srand(time(NULL));	
	for (i = 0; i < q; i++)
	{
		gera_palavra(20, nomelivro);
		x = gera_numero(0, 1);
		fprintf(arquivo, "%s %d\n", nomelivro, x);
	}
}

void gerar_consultas(int q, FILE* arquivo) {
	int i;
	char consulta[100];

	srand(time(NULL));
	for (i = 0; i < q; i++)
	{
		gera_palavra(20, consulta);
		fprintf(arquivo, "%s\n", consulta);
	}
}

void gerar_entradas(int n, int m, int e, int l, int k, FILE* arquivo){

	gerar_variaveis(n, m, e, l, k, arquivo);
	gerar_livros(n, arquivo);
	gerar_consultas(k, arquivo);
}

void gerar_arquivos(int n, int m, int e, int l, int k) {
	FILE* Arquivo;
	char nome[100];
	
	sprintf(nome, "arq_%d_%d_%d_%d_%d", n, m, e, l, k);
	Arquivo = fopen(nome, "w");
	if (Arquivo) {
		gerar_entradas(n, m, e, l, k, Arquivo);
		fclose(Arquivo);
	}
	else
		printf("erro ao gerar arquivo.\n");
}

int main () {
	int i;

	for (i = 1; i < 7; i++)
	{
		gerar_arquivos(1000 * i, 5, 100, 60, 10);
		gerar_arquivos(1000, 10 * i, 10, 100, 10);
		gerar_arquivos(1000, 5, 100 * i, 100, 10);
		gerar_arquivos(1000, 5, 100, 100 * i, 10);
		gerar_arquivos(1000, 5, 100, 10, 100*i);
	}
	exit(EXIT_SUCCESS);
}
