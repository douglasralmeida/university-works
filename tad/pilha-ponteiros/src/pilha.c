/*
**	TIPO ABSTRATO DE DADOS PILHA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao de uma pilha encadeada por ponteiros
*/

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

TPilha* TPilha_Criar()
{
	TPilha* NovaPilha;
	
	NovaPilha = (TPilha*)malloc(sizeof(TPilha));
	if (NovaPilha == NULL)
	{
		printf("Erro (0x31): Erro durante alocacao de memoria.\n");
		return NULL;
	}
 	NovaPilha->Frente = NULL;
  	NovaPilha->Tamanho = 0;
	
	return NovaPilha;
}

void TPilha_Destruir(TPilha** PPilha, TFuncaoDestruir FuncaoDestruir)
{
	if (PPilha != NULL)
	{
		TPilha_Limpar(*PPilha, FuncaoDestruir);
		free(*PPilha);
		PPilha = NULL;
	}
}

void* TPilha_Desempilhar(TPilha* Pilha)
{
	TPilhaNo NoTemp;
	void* Item;

	/*-- pilha vazia? --*/		
	if (Pilha->Frente == NULL)
	{
		printf("Erro (0x32): Pilha vazia.\n");
		return NULL;
	}
	else
	{
		/*-- tira o primeiro item pra fora --*/	
		NoTemp = Pilha->Frente;
		Item = NoTemp->Item;
		Pilha->Frente = Pilha->Frente->Proximo;
		free(NoTemp);
		Pilha->Tamanho--;
		return Item;
	}
}

bool TPilha_Empilhar(TPilha* Pilha, void* Item)
{
	TPilhaNo NoNovo;
	
	NoNovo = (TPilhaNo)malloc(sizeof(struct _TPilhaNo));
	if (NoNovo == NULL)
	{
		printf("Erro (0x33): Erro durante alocacao de memoria.\n");
		return false;
	}
	NoNovo->Item = Item;
	NoNovo->Proximo = Pilha->Frente;
	/*-- novos itens sempre irao para o início da pilha --*/	
	Pilha->Frente = NoNovo;
	Pilha->Tamanho++;
	return true;
}

void TPilha_Imprimir(TPilha* Pilha, TFuncaoImprimir FuncaoImprimir)
{
	TPilhaNo NoTemp;

	NoTemp = Pilha->Frente;
	while (NoTemp != NULL)
	{
		FuncaoImprimir(NoTemp->Item);
		NoTemp = NoTemp->Proximo;
	}
}

void TPilha_Limpar(TPilha* Pilha, TFuncaoDestruir FuncaoDestruir)
{
	TPilhaNo No;
	TPilhaNo NoTemp;
	
	No = Pilha->Frente;
	/*-- varre a fila e destroi tudo --*/
	while (No != NULL)
	{
		FuncaoDestruir(&(No->Item));
		NoTemp = No->Proximo;
		free(No);
		No = NoTemp;
	}
	Pilha->Frente = NULL;
	Pilha->Tamanho = 0;
}

size_t TPilha_Tamanho(TPilha* Pilha)
{
	return Pilha->Tamanho;
}
