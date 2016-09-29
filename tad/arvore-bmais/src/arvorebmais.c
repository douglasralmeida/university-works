/*
 *	TIPO ABSTRATO DE DADOS ARVORE B ESTRELA
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Implementação de uma arvore b*
 */

#include <stdio.h>
#include <stdlib.h>
#include "arvorebmais.h"

TArvoreBMNo TArvoreBMNo_Criar(TArvoreBMNoTipo Tipo, unsigned short Ordem, void* Item, TArvoreBMNo No1, TArvoreBMNo No2)
{
	TArvoreBMNo NovoNo;

	NovoNo = malloc(sizeof(struct _TArvoreBMNo));
	if (!NovoNo)
		return NULL;
	switch (Tipo)
	{
		case bmnoInterno:
			NovoNo->Conteudo.Interno.Contador = 1;
			NovoNo->Conteudo.Interno.Chaves = malloc(Ordem * sizeof(void*));
			NovoNo->Conteudo.Interno.Chaves[0] = Item;
			NovoNo->Conteudo.Interno.Subarvores = malloc((Ordem+1) * sizeof(TArvoreBMNo));
			NovoNo->Conteudo.Interno.Subarvores[0] = No1;
			NovoNo->Conteudo.Interno.Subarvores[1] = No2;
		break;
		case bmnoExterno:
			NovoNo->Conteudo.Externo.Contador = 1;
			NovoNo->Conteudo.Externo.Itens = malloc((Ordem+1) * sizeof(void*));
			NovoNo->Conteudo.Externo.Itens[0] = Item; 
		break;
	}	

	return NovoNo;
}

bool TArvoreBMNo_PesquisarFolha(TArvoreBMNo Folha);
{
	unsigned long i = 1;
	
	while (i < Folha->Contador && FuncaoCompara(Item, Folha->Chaves[i-1]))
		i++;

  	if (Reg.Chave == Ap->r[i-1].Chave) 
 	{
		printf(" Erro: Registro ja esta presente\n");
		return false;
  	}
	
	return true;
}

bool TArvoreBMNo_Inserir(TArvoreBMNo NoAtual, unsigned short Ordem, void* Item, TArvoreBMNo NoRetorno, void* ItemRetorno)
{
	if (!NoAtual)
		return true;
	switch (Tipo)
	{
		case bmnoInterno:
			
		break;
		case bmnoExterno:
			if ArvoreBMNo_PesquisarFolha()
				return false;
 		break;
	}
	
	return false;
}

TArvoreBMais* TArvoreBMais_Criar(unsigned short Ordem)
{
	TArvoreBMais* NovaArvore;
	
	NovaArvore = malloc(sizeof(TArvoreBMais));
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

void TArvoreBMais_Destruir(TArvoreBMais** PArvore, TFuncaoDestruir FuncaoDestruir)
{
	/*-- destruir todos os nós antes--*/	
	free(*PArvore);
	*PArvore = NULL;
}

bool TArvoreBMais_Inserir(TArvoreBMais* Arvore, void* Item)
{
	bool novaraiz;
	void* itemretornado;
	TArvoreBMNo NovaRaiz;
	TArvoreBMNo SubarvoreRetornada;
	
	novaraiz = TArvoreBMNo_Inserir(Arvore->Raiz, Arvore->Ordem, Item, SubarvoreRetornada, itemretornado);
	if (novaraiz)
	{
		if (Arvore->Raiz)
			NovaRaiz = TArvoreBMNo_Criar(bmnoInterno, Arvore->Ordem, itemretornado, Arvore->Raiz, SubarvoreRetornada);
		else
			NovaRaiz = TArvoreBMNo_Criar(bmoExterno, Ordem, Item, NULL, NULL);
		
		Arvore->Raiz = NovaRaiz;
	}
}

void* TArvoreBMais_Pesquisar(TArvoreBMais* Arvore, void* Chave)
{
	
}
