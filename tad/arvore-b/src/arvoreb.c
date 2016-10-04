/*
 *	TIPO ABSTRATO DE DADOS ARVORE B
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Implementação de uma arvore b
 */

#include <stdio.h>
#include <stdlib.h>
#include "arvoreb.h"

TArvoreBNo TArvoreBNo_Criar(unsigned short Ordem, void* Item, TArvoreBNo No1, TArvoreBNo No2)
{
	TArvoreBNo NovoNo;

	NovoNo = malloc(sizeof(struct _TArvoreBNo));
	if (!NovoNo)
		return NULL;
	NovoNo->Contador = 0;
	NovoNo->Itens = malloc(2 * Ordem * sizeof(void*));
	NovoNo->Subarvores = malloc((2 * Ordem + 1) * sizeof(TArvoreBNo*));
	if (Item)
	{
		NovoNo->Contador++;
		NovoNo->Itens[0] = Item;
		NovoNo->Subarvores[0] = No1;
		NovoNo->Subarvores[1] = No2;
	}

	return NovoNo;
}

void TArvoreBNo_Destruir(TArvoreBNo* PNo, TFuncaoDestruir FuncaoDestruir)
{
	int i;
	
	if (*PNo == NULL)
		return;
	for (i = 0; i < (*PNo)->Contador; i++)
		FuncaoDestruir((*PNo)->Itens + i);
	for (i = 0; i <= (*PNo)->Contador; i++)
		TArvoreBNo_Destruir((*PNo)->Subarvores + i, FuncaoDestruir);
	free((*PNo)->Itens);
	free((*PNo)->Subarvores);
	free(*PNo);
	*PNo = NULL;
}

void TArvoreBNo_Fixar(TFuncaoComparar FuncaoComparar, TArvoreBNo NoAtual, void* Item, TArvoreBNo Subarvore)
{
	bool naoacharposicao;
	int i;
	
	i = NoAtual->Contador;
	naoacharposicao = (i > 0);
	while (naoacharposicao)
	{
		if (FuncaoComparar(NoAtual->Itens[i-1], Item))
		{
			naoacharposicao = false;
			break;
		}
		NoAtual->Itens[i] = NoAtual->Itens[i-1];
		NoAtual->Subarvores[i+1] = NoAtual->Subarvores[i];
		i--;
		if (i < 1)
			naoacharposicao = false;
	}
	NoAtual->Itens[i] = Item;
	NoAtual->Subarvores[i+1] = Subarvore;
	NoAtual->Contador++;
}

bool TArvoreBNo_Inserir(TArvoreB* Arvore, TArvoreBNo NoAtual, void** Item, TArvoreBNo* NoRetorno, void** ItemRetorno)
{
	unsigned short i = 1;
	TArvoreBNo NoTemp;
	
	/*-- não tem nada aqui, entao vamos gerar uma nova raiz --*/
	if (!NoAtual)
	{
		*ItemRetorno = *Item;
		*NoRetorno = NULL;
		return true;
	}
	/*-- varre o nó atual em busca da saída para a próxima subarvore --*/
	while (i < NoAtual->Contador && Arvore->FuncaoComparar(*Item, NoAtual->Itens[i-1]))
		i++;

	/*-- INSERIR AQUI UMA FUNCAO DE VERIFICAR SE OS ITENS SAO IGUAIS --*/
	
	/*-- passou da saída, volta uma casa --*/
	if (Arvore->FuncaoComparar(NoAtual->Itens[i-1], *Item))
		i--;
	/*-- a saída é por aqui, vai para i-esima subarvore do nó atual --*/ 
	if (!TArvoreBNo_Inserir(Arvore, NoAtual->Subarvores[i], Item, NoRetorno, ItemRetorno))
		return false;
	/*-- não achou a saída, então fica por aqui mesmo --*/
	if (NoAtual->Contador < Arvore->Ordem * 2)
	{
		TArvoreBNo_Fixar(Arvore->FuncaoComparar, NoAtual, *ItemRetorno, *NoRetorno);
		return false;
	}
	/*-- nó esta cheio, terá que ser dividido --*/
	NoTemp = TArvoreBNo_Criar(Arvore->Ordem, NULL, NULL, NULL);
	if (i < Arvore->Ordem - 1)
	{
		TArvoreBNo_Fixar(Arvore->FuncaoComparar, NoTemp, NoAtual->Itens[2*Arvore->Ordem-1], NoAtual->Subarvores[2*Arvore->Ordem]);
		NoAtual->Contador--;
		TArvoreBNo_Fixar(Arvore->FuncaoComparar, NoAtual, *ItemRetorno, *NoRetorno);
	}
	else
		TArvoreBNo_Fixar(Arvore->FuncaoComparar, NoTemp, *ItemRetorno, *NoRetorno);
	for (i = Arvore->Ordem + 2; i <= 2*Arvore->Ordem; i++)
	{
		TArvoreBNo_Fixar(Arvore->FuncaoComparar, NoTemp, NoAtual->Itens[i-1], NoAtual->Subarvores[i]);
		NoAtual->Contador = Arvore->Ordem;
		NoTemp->Subarvores[0] = NoAtual->Subarvores[Arvore->Ordem+1];
		*ItemRetorno = NoAtual->Itens[Arvore->Ordem];
		*NoRetorno = NoTemp;
	}
	
	return true;
}

TArvoreB* TArvoreB_Criar(unsigned short Ordem)
{
	TArvoreB* NovaArvore;
	
	NovaArvore = malloc(sizeof(TArvoreB));
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

void TArvoreB_Destruir(TArvoreB** PArvore, TFuncaoDestruir FuncaoDestruir)
{
	/*-- destruir todos os nós antes --*/	
	TArvoreBNo_Destruir(&(*PArvore)->Raiz, FuncaoDestruir);
	free(*PArvore);
	*PArvore = NULL;
}

void TArvoreB_Inserir(TArvoreB* Arvore, void* Item)
{
	void* itemretornado = NULL;
	bool novaraiz;
	TArvoreBNo NovaRaiz, SubarvoreRetornada = NULL;
	
	novaraiz = TArvoreBNo_Inserir(Arvore, Arvore->Raiz, &Item, &SubarvoreRetornada, &itemretornado);
	if (novaraiz)
	{
		NovaRaiz = TArvoreBNo_Criar(Arvore->Ordem, itemretornado, Arvore->Raiz, SubarvoreRetornada);
		Arvore->Raiz = NovaRaiz;
	}	
}
