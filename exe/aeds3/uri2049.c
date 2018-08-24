/* URI2049 - NUMEROS DE AHMOC 
 * 2016
 *
 * O Departamento de Arqueologia da Universidade Baylor dedica boa
 * parte de sua pesquisa aos painéis dos índios Ahmoc.
 * Surpreendentemente os índios já conheciam os algarismos hindus,
 * mas não o usavam para cálculos (afinal não existia comércio naquela
 * civilização). Os arqueólogos de Baylor suspeitam que os painéis repletos
 * de números fossem apenas decorativos. Também suspeitam que alguns
 * padrões que se repetiam eram assinaturas dos artistas, a fim de
 * garantir a autenticidade do painel. Sua tarefa neste problema será
 * verificar se os painéis são verdadeiros, ou seja, se, de fato, contêm
 * a assinatura do artista que o arqueólogo suspeita ser o autor.
 * Para cada instância solucionada, você deverá imprimir um
 * identificador "Instancia h" em que h é um número inteiro,
 * sequencial e crescente a partir de 1. Na linha seguinte, você
 * deverá imprimir "verdadeira" se a sequência de números contém
 * a assinatura do artista ou "falsa" em caso contrário. Uma linha
 * em branco deve separar a saída de cada instância.
 */

#include <stdio.h>
#include <string.h>

int Pesquisa(const char* texto, const char* padrao, unsigned long tampadrao) {
  unsigned long mascara[10];
  unsigned long i;
  unsigned long result = 0;

  for (i = 0; i < 10; i++)
    mascara[i] = 0;
  for (i = 1; i <= tampadrao; i++)
	mascara[padrao[i-1]-48] |= 1 << (tampadrao - i);
  i = 0;
  while (texto[i] != '\0') {
    result = ((result >> 1) | (1 << (tampadrao - 1))) & mascara[texto[i]-48];
	if ((result & 1) != 0)
	  return 1;
	i++;
  }

  return 0;
}

int main() {
  char padrao[8];
  char texto[300001];
  unsigned long i = 1;
  unsigned long tamanho_padrao;

  while (1) {
    scanf("%7s", padrao);
	if ((padrao[0] == '0') && (padrao[1] == '\0'))
	  break;
	getchar();
	tamanho_padrao = strlen(padrao);
	gets(texto);
	if (i > 1)
	  printf("\n");
	  printf("Instancia %lu\n", i);
	  if (Pesquisa(texto, padrao, tamanho_padrao))
	    printf("verdadeira\n");
	  else
	    printf("falsa\n");
	  i++;
	}
	
  return 0;
}