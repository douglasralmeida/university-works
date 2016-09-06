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
	NovoNo->Repeticao = 0;
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

void TArvoreDigitalNo_ExibirContador(TArvoreDigitalNo No)
{
	int i;
	unsigned long j;

	if (!No->Prefixo)
	{
		for (j = 0; j < No->Repeticao; j++)
			printf("%lu", No->Contador);
	}
	for (i = 0; i < TAMANHO_ALFABETO; i++)
	{	
		if (No->Alfabeto[i] != NULL)
			TArvoreDigitalNo_ExibirContador(No->Alfabeto[i]);
	}
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
			i = *c - 97;
			if (NoAtual->Alfabeto[i] == NULL)
				NoAtual->Alfabeto[i] = TArvoreDigitalNo_Criar();
			NoAtual = NoAtual->Alfabeto[i];
		}
		c++;
	}
	if (NoAtual != Arvore->Raiz)
	{
		NoAtual->Repeticao++;
		NoAtual->Prefixo = false;
	}
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
			NoAtual->Repeticao++;
			NoAtual->Prefixo = false;
			NoAtual = Arvore->Raiz;
		}
		else
		{
			if (c < 123 && c > 96)
			{
				i = c - 97;
				if (NoAtual->Alfabeto[i] == NULL)
					NoAtual->Alfabeto[i] = TArvoreDigitalNo_Criar();
				NoAtual = NoAtual->Alfabeto[i];
			}
		}
	}
	if (NoAtual != Arvore->Raiz)
	{
		NoAtual->Repeticao++;
		NoAtual->Prefixo = false;
	}
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
			NoAtual->Repeticao++;		
			NoAtual->Prefixo = false;
			NoAtual = Arvore->Raiz;
		}
		else
		{
			if (*c < 123 && *c > 96)
			{
				i = *c - 97;
				if (NoAtual->Alfabeto[i] == NULL)
					NoAtual->Alfabeto[i] = TArvoreDigitalNo_Criar();
				NoAtual = NoAtual->Alfabeto[i];
			}
		}
		c++;
	}
	if (NoAtual != Arvore->Raiz)
	{
		NoAtual->Repeticao++;
		NoAtual->Prefixo = false;
	}
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
			NoAtual->Repeticao++;
			NoAtual->Prefixo = false;
			NoAtual = Arvore->Raiz;
		}
		else
		{
			if (c < 123 && c > 96)
			{
				i = c - 97;
				if (NoAtual->Alfabeto[i] == NULL)
					NoAtual->Alfabeto[i] = TArvoreDigitalNo_Criar();
				NoAtual = NoAtual->Alfabeto[i];
			}
		}	
	}
	if (NoAtual != Arvore->Raiz)
	{
		NoAtual->Repeticao++;
		NoAtual->Prefixo = false;
	}	
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
			if (!proxpalavra && !NoAtual->Prefixo)
				NoAtual->Contador++;
			proxpalavra = false;
			NoAtual = Arvore->Raiz;
		} else if (!proxpalavra && c < 123 && c > 96)
		{
			i = c - 97;
			NoAtual = NoAtual->Alfabeto[i];
			if (!NoAtual)
				proxpalavra = true;
		}
	}
	if (!proxpalavra && !NoAtual->Prefixo)
		NoAtual->Contador++;
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
			if (!proxpalavra && !NoAtual->Prefixo)
				NoAtual->Contador++;
			proxpalavra = false;
			NoAtual = Arvore->Raiz;
		} else if (!proxpalavra && *c < 123 && *c > 96)
		{
			i = *c - 97;
			NoAtual = NoAtual->Alfabeto[i];
			if (!NoAtual)
				proxpalavra = true;
		}
		c++;
	}
	if (!proxpalavra && !NoAtual->Prefixo)
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
			if (!proxpalavra && !NoAtual->Prefixo)
				NoAtual->Contador++;
			proxpalavra = false;
			NoAtual = Arvore->Raiz;
		} else if (!proxpalavra && c < 123 && c > 96)
		{
			i = c - 97;
			NoAtual = NoAtual->Alfabeto[i];
			if (!NoAtual)
				proxpalavra = true;
		}
	}
	if (!proxpalavra && !NoAtual->Prefixo)
		NoAtual->Contador++;
}

void TArvoreDigital_ExibirContador(TArvoreDigital* Arvore)
{
	TArvoreDigitalNo_ExibirContador(Arvore->Raiz);
}
