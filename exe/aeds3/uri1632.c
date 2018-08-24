/* URI1632 - VARIAÇÕES
 * 2016
 * 
 * A internet já não é tão segura quanto ela já foi. Um dos sinais disso
 * é o aumento de ataque de hackers a diversos sites. Para piorar, quando
 * um hacker rouba a senha de um usuário em um determinado site, ele tem
 * também acesso a todas as outras contas deste usuário em outros sites,
 * pois a maioria dos usuários hoje em dia usa a mesma senha em todos os
 * sites que acessa.
 * Uma das soluções propostas para resolver este problema é usar diferentes
 * senhas para cada site, ou até mesmo diferentes variações da mesma senha.
 * Por exemplo, para variar a senha “batata”, é possível usar a senha “bAtaTa”,
 * “B4tat4”, “baTATA”, etc. Ou seja, para cada caractere do alfabeto, é possível
 * formar uma variação colocando tal caractere em maiúsculo ou minúsculo. Inclusive,
 * para aumentar o número total de variações, para os caracteres A, E, I, O e S
 * é possível usar também os números 4, 3, 1, 0 e 5, respectivamente.
 * Seu amigo precisa aumentar o número de variações de sua senha, e pediu sua
 * ajuda. Dada a senha que ele escolheu, diga o número de diferentes variações
 * que é possível montar.
 */

#include <stdio.h>
#include <stdlib.h>
 
char** array_criar(int n) {
	char** novoarray;
	int i;

	novoarray = malloc(n * sizeof(char*));
	for (i = 0; i < n; i++) {
		novoarray[i] = malloc(17 * sizeof(char));
		scanf("%16s", novoarray[i]);
	}
	
	return novoarray;
}

unsigned long calcular(char* palavra) {
	int i = 0;
	unsigned long resultado = 1;
	
	while (1) {
		switch (palavra[i]) {
			case 'a':
			case 'A':
			case 'e':
			case 'E':
			case 'i':
			case 'I':
			case 'o':
			case 'O':
			case 's':
			case 'S':
				resultado *= 3;
				break;
			case '\0':
				return resultado;
			default:
				resultado *= 2;
		}
		i++;
	}
	
	return resultado;
}

void analisar(int n, char** palavras) {
	int i;
	unsigned long resultado = 0;
	 
	for (i = 0; i < n; i++) {
		resultado = calcular(palavras[i]);
		printf("%lu\n", resultado);
		free(palavras[i]);
	}
}

int main() {
	int quant;
	char** palavras;

	scanf("%d", &quant);
	palavras = array_criar(quant);
	analisar(quant, palavras);
	free(palavras);

	return 0;
}