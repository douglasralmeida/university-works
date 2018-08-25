/* URI1611 - ELEVADOR LOTADO
 * 2016
 *
 * Em um prédio de N andares temos um elevador com capacidade para até C pessoas.
 * Os andares são numerados de 0 a N-1. Há um grupo de M pessoas querendo usar o
 * elevador, todas no andar 0. Cada uma deseja ir a um andar específico. Você deve
 * decidir a ordem em que as pessoas devem usar o elevador de forma que a energia
 * utilizada seja a menor possível. Inicialmente um grupo de tamanho no máximo C
 * pessoas decidido por você entra no elevador no andar 0. Depois você deve decidir
 * a ordem em que os andares são visitados. Logicamente, os andares de todas as pessoas
 * dentro do elevador devem ser visitados. O custo de energia do elevador é apenas no
 * deslocamento, ou seja, a cada andar em que ele sobe ou desce você gasta uma unidade
 * de energia. O processo é repetido até que não se tenha mais pessoas no andar 0. No fim
 * o elevador deve voltar ao andar 0. Dado o tamanho do prédio, a capacidade do elevador
 * e os andares das pessoas que querem utilizar o elevador, monte a melhor estratégia que
 * minimize a energia utilizada. Imprima o valor desta energia.
 */

#include <stdio.h>

#define MAX_PESSOAS 50000

void trocar(int* vetor, int* i, int* j) {
	int item;

	if (*i != *j) {
		item = vetor[*i];
		vetor[*i] = vetor[*j];
		vetor[*j] = item;
	}
}

void particionar(int* vetor, int e, int d, int* i, int* j) {
	int x;
	
	*i = e;
	*j = d;
	x = vetor[e + (d-e)/2];
	do {
		while (vetor[*i] > x)
			(*i)++;
		while (x > vetor[*j]) {
			(*j)--;
		}
		if (*i <= *j) {
			trocar(vetor, i, j);
			(*i)++;
			(*j)--;
		}
	} while (*i <= *j);
}

void ordenar(int* vetor, int e, int d) {
	int i;
	int j;
	
	particionar(vetor, e, d, &i, &j);
	if (e < j)
		ordenar(vetor, e, j);
	if (i < d)
		ordenar(vetor, i, d);
}

void testar(int* Andares, int c, int n) {
	int energia = 0;
	int x = 0;

	ordenar(Andares, 0, n-1);
	while (x < n) {
		energia += 2*Andares[x];
		x += c;
	}
	printf("%d\n", energia);
}

void executar_teste(int* Andares) {
	int i, c;
	int n, m;	
	
	scanf("%d %d %d", &n, &c, &m);
	for (i = 0; i < m; i++)
		scanf("%d", Andares + i);
	testar(Andares, c, m);
}

int main() {
	int i, testequant;
	int andares[MAX_PESSOAS];

	scanf("%d", &testequant);
	for (i = 0; i < testequant; i++)
		executar_teste(andares);

	return 0;
}