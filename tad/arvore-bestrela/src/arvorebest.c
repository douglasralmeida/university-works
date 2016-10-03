/*
 *	TIPO ABSTRATO DE DADOS ARVORE B ESTRELA
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Implementação de uma arvore b*
 */

#include <stdio.h>
#include <stdlib.h>
#include "arvorebest.h"

TArvoreBENo TArvoreBENo_Criar(unsigned short Ordem, void* Item, TArvoreBENo No1, TArvoreBENo No2)
{
	TArvoreBENo NovoNo;

	NovoNo = malloc(sizeof(struct _TArvoreBENo));
	if (!NovoNo)
		return NULL;
	NovoNo->Contador = 0;
	NovoNo->Itens = malloc(Ordem * sizeof(void*));
	NovoNo->Subarvores = malloc((Ordem+1) * sizeof(TArvoreBENo*));
	if (Item)
	{
		NovoNo->Contador++;
		NovoNo->Itens[0] = Item;
		NovoNo->Subarvores[0] = No1;
		NovoNo->Subarvores[1] = No2;
	}

	return NovoNo;
}

void TArvoreBENo_Destruir(TArvoreBENo* PNo, TFuncaoDestruir FuncaoDestruir)
{
	int i;
	
	if ((*PNo) == NULL)
		return;
	for (i = 0; i < (*PNo)->Contador; i++)
		FuncaoDestruir((*PNo)->Itens + i);
	for (i = 0; i <= (*PNo)->Contador; i++)
		TArvoreBENo_Destruir((*PNo)->Subarvores + i, FuncaoDestruir);
	
	free(*PNo);
	PNo = NULL;

}

void TArvoreBENo_Fixar(TArvoreBENo NoAtual, void* Item, TArvoreBENo Subarvore)
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

bool TArvoreBENo_Inserir(TArvoreBENo NoAtual, unsigned short Ordem, void* Item, TArvoreBENo NoRetorno, void* ItemRetorno)
{
	unsigned short i;
	TArvoreBENo NoTemp;
	
	/*-- não tem nada aqui, entao vamos gerar uma nova raiz --*/
	if (!NoAtual)
		return true;
	/*-- varre o nó atual em busca da saída para a próxima subarvore --*/
	while (i < NoAtual->Contador && FuncaoComparar(Item, NoAtual->Itens[i-1]))
		i++;

	/*-- INSERIR AQUI UMA FUNCAO DE VERIFICAR SE OS ITENS SAO IGUAIS --*/
	
	/*-- passou da saída, volta uma casa --*/
	if (FuncaoComparar(NoAtual->Itens[i-1], Item))
		i--;
	/*-- a saída é por aqui, vai para i-esima subarvore do nó atual --*/ 
	if (!TArvoreBENo_Inserir(NoAtual->Subarvores[i], Ordem, Item, NoRetorno, ItemRetorno))
		return false;
	/*-- não achou a saída, então fica por aqui mesmo --*/
	if (NoAtual->Contador < Ordem * 2)
	{
		TArvoreBENo_Fixar(NoAtual, ItemRetorno, NoRetorno);
		return false;
	}
	/*-- nó esta cheio, terá que ser dividido --*/
	NoTemp = TArvoreBENo_Criar(Ordem, NULL, NULL, NULL);
	if (i < Ordem - 1)
	{
		TArvoreBENo_Fixar(NoTemp, NoAtual->Itens[2*Ordem-1], NoAtual->Subarvores[2*Ordem]);
		NoAtual->Contador--;
		TArvoreBENo_Fixar(NoAtual, ItemRetorno, NoRetorno);
	}
	else
		TArvoreBENo_Fixar(NoTemp, ItemRetorno, NoRetorno);
	for (i = Ordem + 2; i <= 2*Ordem; i++)
	{
		TArvoreBENo_Fixar(NoTemp, NoAtual->Itens[i-1], NoAtual->Subarvores[i]);
		NoAtual->Contador = Ordem;
		NoTemp->Itens[0] = NoAtual->Itens[Ordem+1];
		ItemRetorno = NoAtual->Itens[Ordem];
		NoRetorno = NoTemp;
	}
	
	return true;
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
	TArvoreBENo_Destruir(&(*PArvore)->Raiz, FuncaoDestruir);
	free(*PArvore);
	PArvore = NULL;
}

void TArvoreBEstrela_Inserir(TArvoreBEstrela* Arvore, void* Item)
{
	void* itemretornado = NULL;
	bool novaraiz;
	TArvoreBENo NovaRaiz, SubarvoreRetornada = NULL;
	
	novaraiz = TArvoreBENo_Inserir(Arvore->Raiz, Arvore->Ordem, Item, SubarvoreRetornada, itemretornado);
	if (novaraiz)
	{
		NovaRaiz = TArvoreBENo_Criar(Arvore->Ordem, itemretornado, Arvore->Raiz, SubarvoreRetornada);
		Arvore->Raiz = NovaRaiz;
	}	
}
