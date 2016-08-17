/*
 *	ALGORITMOS DE CASAMENTO DE CADEIA DE CARACTERES
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Implementação de algoritmos para casamento de cadeia de caracteres
 */

#include "caracteres.h"

unsigned long PesquisarCarac_ForcaBruta(char* Texto, unsigned long TamanhoTexto, char* Padrao, unsigned long TamanhoPadrao)
{
	unsigned long i, j, k;

	for (i = 1; i <= (TamanhoTexto - TamanhoPadrao + 1); i++)
	{
		k = i;
		j = 1;
		while ((Texto[k-1] == Padrao[j-1]) && (j <= TamanhoPadrao))
		{
			j++;
			k++;
			if (j > TamanhoPadrao)
				return i;
		}
	}
	return 0;
}

unsigned long PesquisarCarac_BMH(char* Texto, unsigned long TamanhoTexto, char* Padrao, unsigned long TamanhoPadrao)
{
	long i, j, k;
	long mascara[MAXCHAR];

	/* processamento do padrao */
	for (j = 0; j < MAXCHAR; j++)
		mascara[j] = TamanhoPadrao;
	for (j = 1; j < TamanhoPadrao; j++)
		mascara[(int)Padrao[j-1]] = TamanhoPadrao - j;
	i = TamanhoPadrao;

	/* pesquisa */
	while (i <= TamanhoTexto)
	{
		k = i;
		j = TamanhoPadrao;
		while ((Texto[k-1] == Padrao[j-1]) && (j > 0))
		{
			k--;
			j--;
		}
		if (j == 0)
			return k + 1;
		i += mascara[Texto[i-1]];
	}

	return 0;
}

unsigned long PesquisarCarac_BMHS(char* Texto, unsigned long TamanhoTexto, char* Padrao, unsigned long TamanhoPadrao)
{
	long i, j, k;
	long mascara[MAXCHAR];
	
	/* processamento do padrao */
	for (j = 0; j < MAXCHAR; j++)
		mascara[j] = TamanhoPadrao + 1;
	for (j = 1; j <= TamanhoPadrao; j++)
		mascara[(int)Padrao[j-1]] = TamanhoPadrao - j + 1;
	i = TamanhoPadrao;
	
	/* pesquisa */
	while (i <= TamanhoTexto)
	{
		k = i;
		j = TamanhoPadrao;
		while ((Texto[k-1] == Padrao[j-1]) && (j > 0))
		{
			k--;
			j--;
		}
		if (j == 0)
			return k + 1;
		i += mascara[Texto[i]];
	}
	
	return 0;
}