/*
**	TIPO ABSTRATO DE DADOS FILA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação de fila com vetor
*/

#include <stdio.h>
#include "filaprior.h"



TFila* TFila_Criar(size_t Capacidade)
{
	TFila* NovaFila;
	
	NovaFila = (TFila*)malloc(sizeof(TFila));
	if (NovaFila == NULL)
	{
		printf("Erro (0x21): Erro durante alocacao de memoria.\n");
		return NULL;
	}
	NovaFila->Itens = malloc((Capacidade) * sizeof(void*));
	if (NovaFila->Itens == NULL)
	{
		printf("Erro(0x24): Erro durante alocacao de memoria.\n");
		free(NovaFila);
		return NULL;
	}
	NovaFila->Capacidade = Capacidade;
	NovaFila->Expansao = FILA_EXPANSAO;
	NovaFila->Frente = 0;
	NovaFila->Tras = 0;
	NovaFila->Tamanho = 0;
  
	return NovaFila;

}

void TFila_Destruir(TFila** PFila, TFuncaoDestruir FuncaoDestruir)
{
	if (PFila != NULL)
	{
		TFila_Limpar(*PFila, FuncaoDestruir);
		free((*PFila)->Itens);
		free(*PFila);
		*PFila = NULL;
	}
}

void* TFila_Desenfileirar(TFila* Fila)
{

}

bool TFila_Enfileirar(TFila* Fila, void* Item)
{

}

void TFila_Imprimir(TFila* Fila, TFuncaoImprimir FuncaoImprimir)
{

}

void TFila_Limpar(TFila* Fila, TFuncaoDestruir FuncaoDestruir)
{
	size_t i;
	
	for(i = 0; i <= Fila->Tamanho; i++)
		FuncaoDestruir(&(Fila->Item[i]));
	Fila->Tamanho = 0;
	Fila->Frente = 0;
	Fila->Tras = 0;
}

size_t TFila_Tamanho(TFila* Fila)
{
	return Fila->Tamanho;
}
