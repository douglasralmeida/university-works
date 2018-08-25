/* URI1034 - FESTIVAL DE ESTÁTUAS DE GELO
 * 2017
 *
 * Todos os anos, artistas de todo o mundo se reúnem na cidade,
 * onde fazem esculturas de gelo gigantescas. A cidade vira uma
 * galeria de arte ao céu aberto, uma vez que as esculturas ficam
 * expostas na rua por semanas, sem derreter. Afinal, a temperatura
 * média no inverno de Harbin (época em que ocorrerá a final mundial
 * do ICPC) é de -20 graus.
 * O primeiro passo para fazer a escultura é montar um grande bloco de
 * gelo da dimensão pedida pelo artista. Os blocos são recortados das
 * geleiras de Harbin em blocos de altura e profundidade padrão e vários
 * comprimentos diferentes. O artista pode determinar qual o comprimento
 * que ele deseja que tenha o seu bloco de gelo para que a escultura
 * possa começar a ser esculpida.
 * Os comprimentos disponíveis dos blocos são {a1; a2; ...;  aN} e o comprimento
 * que o artista deseja é M. O bloco de comprimento 1 é muito usado, por
 * este motivo ele sempre aparece na lista de blocos disponíveis. Sua tarefa é
 * determinar o número mínimo de blocos tal que a soma de seus comprimentos seja M.
 */

#include <stdio.h>
#include <limits.h>

#define MAX_VALORES 25

void processar(long* Vetor, int tam, long Limite) {
	int i, j, x;
	int r[Limite+1];
	
	r[0] = 0;
	for (i=1; i <= Limite; i++)
		r[i] = INT_MAX;
	for (i = 1; i <= Limite; i++) {
		for (j = 0; j < tam; j++)
			if (Vetor[j] <= i) {
				x = r[i-Vetor[j]];
				if (x != INT_MAX && x + 1 < r[i])
					r[i] = x + 1;
			}
	}
	printf("%d\n", r[Limite]);
}

void executar() {
	int i, tam;
	long lim;
	long Valores[MAX_VALORES];
	
	scanf("%d %ld", &tam, &lim);
	for (i = 0; i < tam; i++)
		scanf("%ld", Valores + i);
	processar(Valores, tam, lim);
}

int main() {
	int t;
	
	scanf("%d", &t);
	while(t--) {
		executar();
	}	
	exit(0);
}