/*
**	TIPO ABSTRATO DE DADOS PILHA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação de pilha com vetor
*/

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

static bool ExpandirPilha(TPilha* Pilha)
{
	size_t NovaCapacidade;
	void** NovoItens;

	NovaCapacidade = Pilha->Capacidade + Pilha->Expansao;
	NovoItens = realloc(Pilha->Itens, (NovaCapacidade) * sizeof(void*));
	if (NovoItens == NULL)
	{
		printf("Erro (0x35): Erro durante alocacao de memoria.\n");
		return false;
	}
	Pilha->Itens = NovoItens;
	Pilha->Capacidade = NovaCapacidade;

	return true;
}

TPilha* TPilha_Criar(size_t Capacidade)
{
	TPilha* NovaPilha;
	
	NovaPilha = (TPilha*)malloc(sizeof(TPilha));
	if (NovaPilha == NULL)
	{
		printf("Erro (0x31): Erro durante alocacao de memoria.\n");
		return NULL;
	}
	NovaPilha->Itens = malloc((Capacidade) * sizeof(void*));
	if (NovaPilha->Itens == NULL)
	{
		printf("Erro(0x34): Erro durante alocacao de memoria.\n");
		free(NovaPilha);
		return NULL;
	}
	NovaPilha->Capacidade = Capacidade;
	NovaPilha->Expansao = PILHA_EXPANSAO;
	NovaPilha->Frente = 0;
  
	return NovaPilha;
}

void TPilha_Destruir(TPilha** PPilha, TFuncaoDestruir FuncaoDestruir)
{
	if (PPilha != NULL)
	{
		TPilha_Limpar(*PPilha, FuncaoDestruir);
		free((*PPilha)->Itens);
		free(*PPilha);
		*PPilha = NULL;
	}
}

void* TPilha_Desempilhar(TPilha* Pilha)
{
	void* Item;
	
	if (Pilha->Frente == 0)
	{
		printf("Erro (0x26): Erro ao desempilhar. Pilha vazia.\n");
		return NULL;
	}
	else
	{
		Item = Pilha->Itens[Pilha->Frente - 1];
		Pilha->Frente--;
		return Item;
	}
}

bool TPilha_Empilhar(TPilha* Pilha, void* Item)
{
	if (Pilha->Frente == Pilha->Capacidade)
		if (ExpandirPilha(Pilha))
		{
			Pilha->Itens[Pilha->Frente] = Item;
			Pilha->Frente++;
			return true;
		}
		else
		{
			printf("Erro: (0x25): Erro ao empilhar. Pilha cheia.\n");
			return false;
		}	
	else 
	{
		Pilha->Itens[Pilha->Frente] = Item;
		Pilha->Frente++;
		return true;
	}
}

void TPilha_Imprimir(TPilha* Pilha, TFuncaoImprimir FuncaoImprimir)
{
	TPilhaNo NoTemp;
	
	NoTemp = Pilha->Frente;
	while (NoTemp > 0)
	{
		FuncaoImprimir(Pilha->Itens[NoTemp - 1]);
		NoTemp--;
	}
}

void TPilha_Limpar(TPilha* Pilha, TFuncaoDestruir FuncaoDestruir)
{
	TPilhaNo NoTemp;
	
	NoTemp = Pilha->Frente;
	while (NoTemp > 0)
	{
		FuncaoDestruir(&Pilha->Itens[NoTemp - 1]);
		NoTemp--;
	}
	Pilha->Frente = 0;
}

size_t TPilha_Tamanho(TPilha* Pilha)
{
	return Pilha->Frente;
}
