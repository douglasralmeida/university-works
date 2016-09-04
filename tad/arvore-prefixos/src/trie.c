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
	NovoNo->Sufixo = true;
	
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

void TArvoreDigital_Carregar(TArvoreDigital* Arvore, FILE* Arquivo)
{
	char c;
	int i;
	TArvoreDigitalNo NoAtual;
	
	NoAtual = Arvore->Raiz;
	while ((c = fgetc(Arquivo)) != EOF)
	{
		if (c == ' ')
		{
			NoAtual->Sufixo = false;
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
		NoAtual->Sufixo = false;
}