/*
 *	TIPO ABSTRATO DE DADOS ARVORE DIGITAL
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Implementação de uma arvore digital
 */

#include <stdio.h>
#include <stdlib.h>
#include "boolutils.h"
#include "trie.h"

TArvoreDigitalNo TArvoreDigitalNo_Criar()
{
	int i;
	TArvoreDigitalNo NovoNo;
	
	NovoNo = malloc(sizeof(struct _TArvoreDigitalNo));
	if (!NovoNo)
		return NULL;
	NovoNo->Alfabeto = malloc(TAMANHO_ALFABETO * sizeof(TArvoreDigitalNo));
	if (!NovoNo->Alfabeto)
	{
		free(NovoNo);
		return NULL;
	}
	for (i = 0; i < TAMANHO_ALFABETO; i++)
		NovoNo->Alfabeto[i] = NULL;
	NovoNo->Contador = 0;
	NovoNo->Prefixo = true;
	
	return NovoNo;
}

void TArvoreDigitalNo_Destruir(TArvoreDigitalNo* PArvoreDigitalNo)
{
	int i;
	
	for (i = 0; i < TAMANHO_ALFABETO; i++)
		if ((*PArvoreDigitalNo)->Alfabeto[i])
			TArvoreDigitalNo_Destruir((*PArvoreDigitalNo)->Alfabeto + i);
	free((*PArvoreDigitalNo)->Alfabeto);
	free(*PArvoreDigitalNo);
	PArvoreDigitalNo = NULL;
}

TArvoreDigital* TArvoreDigital_Criar()
{
	TArvoreDigital* NovaArvore;
	
	NovaArvore = malloc(sizeof(TArvoreDigital));
	if (!NovaArvore)
		return NULL;
	NovaArvore->Raiz = TArvoreDigitalNo_Criar();
	if (!NovaArvore->Raiz)
	{
		free(NovaArvore);
		return NULL;
	}
	
	return NovaArvore;
}

void TArvoreDigital_Destruir(TArvoreDigital** PArvore)
{
	TArvoreDigitalNo_Destruir(&(*PArvore)->Raiz);
	free(*PArvore);
	PArvore = NULL;
}

void TArvoreDigital_Adicionar(TArvoreDigital* Arvore, char* Palavra)
{
	char* c;
	int i;
	TArvoreDigitalNo NoAtual;
	
	NoAtual = Arvore->Raiz;
	c = Palavra;
	while (*c != '\0')
	{
		if (*c < 123 && *c > 96)
		{
			i = *c - 97; /*o primeiro vetor representa o caractere 'a'...o ultimo, o caractere 'z'*/
			if (NoAtual->Alfabeto[i] == NULL)
				NoAtual->Alfabeto[i] = TArvoreDigitalNo_Criar();
			NoAtual = NoAtual->Alfabeto[i];
		}
		c++;
	}
	if (NoAtual != Arvore->Raiz)
		NoAtual->Prefixo = false; /*prefixo da arvore que tambem representa uma palavra*/
}

void TArvoreDigital_CarregarArquivo(TArvoreDigital* Arvore, FILE* Arquivo)
{
	char c;
	int i;
	TArvoreDigitalNo NoAtual;
	
	NoAtual = Arvore->Raiz;
	while ((c = fgetc(Arquivo)) != EOF)
	{
		if (c == ' ')
		{
			NoAtual->Prefixo = false; /*prefixo da arvore que tambem representa uma palavra*/
			NoAtual = Arvore->Raiz;
		}
		else
		{
			if (c < 123 && c > 96)
			{
				i = c - 97; /*o primeiro vetor representa o caractere 'a'...o ultimo, o caractere 'z'*/
				if (NoAtual->Alfabeto[i] == NULL)
					NoAtual->Alfabeto[i] = TArvoreDigitalNo_Criar();
				NoAtual = NoAtual->Alfabeto[i];
			}
		}
	}
	if (NoAtual != Arvore->Raiz)
		NoAtual->Prefixo = false; /*prefixo da arvore que tambem representa uma palavra*/
}

void TArvoreDigital_CarregarString(TArvoreDigital* Arvore, char* Entrada)
{
	char* c;
	int i;
	TArvoreDigitalNo NoAtual;
	
	NoAtual = Arvore->Raiz;
	c = Entrada;
	while (*c != '\0')
	{
		if (*c == ' ')
		{
			NoAtual->Prefixo = false; /*prefixo da arvore que tambem representa uma palavra*/
			NoAtual = Arvore->Raiz;
		}
		else
		{
			if (*c < 123 && *c > 96)
			{
				i = *c - 97; /*o primeiro vetor representa o caractere 'a'...o ultimo, o caractere 'z'*/
				if (NoAtual->Alfabeto[i] == NULL)
					NoAtual->Alfabeto[i] = TArvoreDigitalNo_Criar();
				NoAtual = NoAtual->Alfabeto[i];
			}
		}
		c++;
	}
	if (NoAtual != Arvore->Raiz)
		NoAtual->Prefixo = false; /*prefixo da arvore que tambem representa uma palavra*/
}

void TArvoreDigital_CarregarTela(TArvoreDigital* Arvore)
{
	char c;
	int i;
	TArvoreDigitalNo NoAtual;
	
	NoAtual = Arvore->Raiz;
	while( (c = getchar()) != '\n' && c != '\0' && c != EOF)
	{
		if (c == ' ')
		{
			NoAtual->Prefixo = false; /*prefixo da arvore que tambem representa uma palavra*/
			NoAtual = Arvore->Raiz; 
		}
		else
		{
			if (c < 123 && c > 96)
			{
				i = c - 97; /*o primeiro vetor representa o caractere 'a'...o ultimo, o caractere 'z'*/
				if (NoAtual->Alfabeto[i] == NULL)
					NoAtual->Alfabeto[i] = TArvoreDigitalNo_Criar();
				NoAtual = NoAtual->Alfabeto[i];
			}
		}	
	}
	if (NoAtual != Arvore->Raiz)
		NoAtual->Prefixo = false; /*prefixo da arvore que tambem representa uma palavra*/
}

void TArvoreDigital_ContarPalavrasArquivo(TArvoreDigital* Arvore, FILE* Arquivo)
{
	bool proxpalavra;
	char c;
	int i;
	TArvoreDigitalNo NoAtual;

	NoAtual = Arvore->Raiz;
	proxpalavra = false;
	while ((c = fgetc(Arquivo)) != EOF)
	{
		if (c == ' ')
		{
			if (!proxpalavra && !NoAtual->Prefixo) /*palavra encontrada, aumenta seu contador*/
				NoAtual->Contador++;
			proxpalavra = false; 
			NoAtual = Arvore->Raiz;
		} else if (!proxpalavra && c < 123 && c > 96)
		{
			i = c - 97; /*o primeiro vetor representa o caractere 'a'...o ultimo, o caractere 'z'*/
			NoAtual = NoAtual->Alfabeto[i];
			if (!NoAtual) /*se palavra nao encontrada, pula para a proxima palavra*/
				proxpalavra = true;
		}
	}
	if (!proxpalavra && !NoAtual->Prefixo)
		NoAtual->Contador++; /*palavra encontrada, aumenta seu contador*/
}

void TArvoreDigital_ContarPalavrasString(TArvoreDigital* Arvore, char* Entrada)
{
	bool proxpalavra;
	char* c;
	int i;
	TArvoreDigitalNo NoAtual;

	NoAtual = Arvore->Raiz;
	proxpalavra = false;
	c = Entrada;
	while (*c != '\0')
	{
		if (*c == ' ')
		{
			if (!proxpalavra && !NoAtual->Prefixo) /*palavra encontrada, aumenta seu contador*/
				NoAtual->Contador++;
			proxpalavra = false;
			NoAtual = Arvore->Raiz;
		} else if (!proxpalavra && *c < 123 && *c > 96)
		{
			i = *c - 97; /*o primeiro vetor representa o caractere 'a'...o ultimo, o caractere 'z'*/
			NoAtual = NoAtual->Alfabeto[i];
			if (!NoAtual) /*se palavra nao encontrada, pula para a proxima palavra*/
				proxpalavra = true; 
		}
		c++;
	}
	if (!proxpalavra && !NoAtual->Prefixo) /*palavra encontrada, aumenta seu contador*/
		NoAtual->Contador++;
}

void TArvoreDigital_ContarPalavrasTela(TArvoreDigital* Arvore)
{
	bool proxpalavra;
	char c;
	int i;
	TArvoreDigitalNo NoAtual;

	NoAtual = Arvore->Raiz;
	proxpalavra = false;
	while( (c = getchar()) != '\n' && c != '\0' && c != EOF)
	{
		if (c == ' ')
		{
			if (!proxpalavra && !NoAtual->Prefixo) /*palavra encontrada, aumenta seu contador*/
				NoAtual->Contador++;
			proxpalavra = false;
			NoAtual = Arvore->Raiz;
		} else if (!proxpalavra && c < 123 && c > 96)
		{
			i = c - 97; /*o primeiro vetor representa o caractere 'a'...o ultimo, o caractere 'z'*/
			NoAtual = NoAtual->Alfabeto[i];
			if (!NoAtual) /*se palavra nao encontrada, pula para a proxima palavra*/
				proxpalavra = true;
		}
	}
	if (!proxpalavra && !NoAtual->Prefixo) /*palavra encontrada, aumenta seu contador*/
		NoAtual->Contador++;
}

void TArvoreDigital_ExibirContador(TArvoreDigital* Arvore, char* Palavra)
{
	char* c;
	int i;
	TArvoreDigitalNo NoAtual;

	NoAtual = Arvore->Raiz;
	c = Palavra;
	while (*c != '\0')
	{
		i = *c - 97; /*o primeiro vetor representa o caractere 'a'...o ultimo, o caractere 'z'*/
		NoAtual = NoAtual->Alfabeto[i];
		if (!NoAtual) /*se palavra nao encontrada, nao faz nada*/
			return;
		c++;
	}
	if (!NoAtual->Prefixo) /*palavra encontrada, exibe seu contador*/
		printf("%llu ", NoAtual->Contador);		
}
