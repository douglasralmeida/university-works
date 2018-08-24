/* URI1257 - ARRAY HASH
 * 2016
 *
 * Você terá como uma entrada várias linhas, cada uma
 * com uma string. O valor de cada caracter é computado
 * como segue:
 * Valor = (Posição no alfabeto) + (Elemento de entrada) + (Posição do elemento)
 * Todas posições são baseadas em zero. 'A' tem posição 0
 * no alfabeto, 'B' tem posição 1 no alfabeto, ... O cálculo
 * de hash retornado é a soma de todos os caracteres da
 * entrada. Por exemplo, se a entrada for:
 * CBA
 * DDD
 * então cada caractere deverá ser computado como segue:
 * 2 = 2 + 0 + 0 : 'C' no elemento 0 posição 0
 * 2 = 1 + 0 + 1 : 'B' no elemento 0 posição 1
 * 2 = 0 + 0 + 2 : 'A' no elemento 0 posição 2
 * 4 = 3 + 1 + 0 : 'D' no elemento 1 posição 0
 * 5 = 3 + 1 + 1 : 'D' no elemento 1 posição 1
 * 6 = 3 + 1 + 2 : 'D' no elemento 1 posição 2
 * O cálculo final de hash será 2+2+2+4+5+6 = 21.
 */

#include <stdio.h>

int main() {
	unsigned long a[3];
	unsigned short b[3];
	char c;
	
	scanf("%lu", a);
	a[1] = 0;
	while (a[1] < a[0]) {
		scanf("%hu", b);
		getchar_unlocked();
		b[1] = 0;
		a[2] = 0;
		while (b[1] < b[0]) {
			b[2] = 0;
			while ((c = getchar_unlocked()) != '\n' ) {
				a[2] += c - 65 + b[2] + b[1];
				b[2]++;
			}
			b[1]++;
		}
		a[1]++;
    printf("%lu\n", a[2]);
	}

	return 0;
}