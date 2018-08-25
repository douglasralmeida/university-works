/* URI1084 - APAGANDO E GANHANDO
 * 2016
 *
 * Juliano é fã do programa de auditório Apagando e Ganhando,
 * um programa no qual os participantes são selecionados através
 * de um sorteio e recebem prêmios em dinheiro por participarem.
 * No programa, o apresentador escreve um número de N dígitos em
 * uma lousa. O participante então deve apagar exatamente D dígitos
 * do número que está na lousa; o número formado pelos dígitos que
 * restaram é então o prêmio do participante. Juliano finalmente foi
 * selecionado para participar do programa, e pediu que você escrevesse
 * um programa que, dados o número que o apresentador escreveu na lousa,
 * e quantos dígitos Juliano tem que apagar, determina o valor do maior
 * prêmio que Juliano pode ganhar.
 */

#include <stdio.h>

void processar(char* vetor, char* resposta, int n, int k) {
  int i, x = -1;

  for (i = 0; i < n; i++) {
    while (k > 0 && x > -1 && resposta[x] < vetor[i]) {
	  k--;			
	  x--;			
	}
	resposta[++x] = vetor[i];
  }
  resposta[x-k+1] = '\0';
}

int main() {
	int n, d;
	char x[100001];
	char r[100001];

	while (scanf("%d %d\n", &n, &d) && n && d) {
		gets(x);
		processar(x, r, n, d);
		printf("%s\n", r);
	}

	return 0;
}