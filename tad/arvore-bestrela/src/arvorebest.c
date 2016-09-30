/*
 *	TIPO ABSTRATO DE DADOS ARVORE B ESTRELA
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Implementação de uma arvore b*
 */

#include <stdio.h>
#include <stdlib.h>
#include "arvorebest.h"

TArvoreBENo TArvoreBENo_Criar(unsigned short Ordem, void* Item, TArvoreBENo* No1, TArvoreBENo* No2)
{
	TArvoreBENo NovoNo;

	NovoNo = malloc(sizeof(struct _TArvoreBENo));
	if (!NovoNo)
		return NULL;
	NovoNo->Contador = 0;
	NovoNo->Itens = malloc(Ordem * sizeof(void*));
	NovoNo->Subarvores = malloc((Ordem+1) * sizeof(TArvoreBENo*));

	return NovoNo;
}

bool TArvoreBENo_Inserir(TArvoreBENo NoAtual, unsigned short Ordem, void* Item, TArvoreBMNo NoRetorno, void* ItemRetorno)
{
	unsigned short i;
	
	if (!NoAtual)
		return true;
	while (i < NoAtual->Contador && FuncaoCompara(Item, NoAtual->Itens[i-1]))
		i++;

	/*-- INSERIR AQUI UMA FUNCAO DE VERIFICAR SE OS ITENS SAO IGUAIS --*/
	
	if FuncaoCompara(NoAtual->Itens[i-1], Item)
		i--;
		
	if (TArvoreBENo_Inserir(NoAtual->Subarvores[i], Ordem, Item, NoRetorno, ItemRetorno))
		return;
}

TArvoreBEstrela* TArvoreBEstrela_Criar(unsigned short Ordem)
{
	TArvoreBEstrela* NovaArvore;
	
	NovaArvore = malloc(sizeof(TArvoreBEstrela));
	if (!NovaArvore)
		return NULL;
	if (Ordem)
		NovaArvore->Ordem = Ordem;
	else
	{
		free(NovaArvore);
		return NULL;
	}
	NovaArvore->Raiz = NULL;
	
	return NovaArvore;
}

void TArvoreBEstrela_Destruir(TArvoreBEstrela** PArvore, TFuncaoDestruir FuncaoDestruir)
{
	/*-- destruir todos os nós antes --*/	
	
	free(*PArvore);
	PArvore = NULL;
}

void TArvoreBEstrela_Inserir(TArvoreBEstrela* Arvore, void* Item)
{
	bool novaraiz;
	TArvoreBENo* NovaRaiz;
	
	novaraiz = TArvoreBENo_Inserir(Arvore->Raiz, Arvore->Ordem, Item, SubarvoreRetornada, itemretornado);
	if (novaraiz)
	{
		NovaRaiz = TArvoreBENo_Criar(Arvore->Ordem, itemretornado, Arvore->Raiz, SubarvoreRetornada);
		Arvore->Raiz = NovaRaiz;
	}	
}
