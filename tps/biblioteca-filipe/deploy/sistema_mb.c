/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação do motor de busca
*/

#include <stdlib.h>
#include <string.h>
#include "sistema_es.h"
#include "sistema_mb.h"

TSistemaMotorBuscaItem* TSistemaMotorBuscaItem_Criar(char* Inicio, char* Final, size_t ID)
{
	TSistemaMotorBuscaItem* NovoItem;

	NovoItem = malloc(sizeof(TSistemaMotorBuscaItem));
	NovoItem->NomeInicial = malloc((strlen(Inicio)+1) * sizeof(char));
	NovoItem->NomeFinal = malloc((strlen(Final)+1) * sizeof(char));
	strcpy(NovoItem->NomeInicial, Inicio);
	strcpy(NovoItem->NomeFinal, Final);
	NovoItem->ID = ID;

	return NovoItem;
}

void TSistemaMotorBuscaItem_Destruir(void** PItem)
{
	free((*(TSistemaMotorBuscaItem**)PItem)->NomeInicial);
	free((*(TSistemaMotorBuscaItem**)PItem)->NomeFinal);
	free(*PItem);
	*PItem = NULL;
}

bool TSistemaMotorBuscaItem_Comparar(void* Item1, void* Item2)
{
	return (strcmp(((TSistemaMotorBuscaItem*)Item1)->NomeFinal, ((TSistemaMotorBuscaItem*)Item2)->NomeInicial) < 0);
}

bool TSistemaMotorBuscaItem_Iguais(void* Item1, void* Item2)
{
	return (strcmp(((TSistemaMotorBuscaItem*)Item1)->NomeInicial, ((TSistemaMotorBuscaItem*)Item2)->NomeInicial) <= 0) &&
	(strcmp(((TSistemaMotorBuscaItem*)Item1)->NomeFinal, ((TSistemaMotorBuscaItem*)Item2)->NomeFinal) >= 0);
}

TSistemaMotorBuscaResultado* TSistemaMotorBuscaResultado_Criar()
{
	TSistemaMotorBuscaResultado* NovoResultado;
	
	NovoResultado = malloc(sizeof(TSistemaMotorBuscaResultado));
	NovoResultado->Livro = TLivro_Criar();

	return NovoResultado;
}

void TSistemaMotorBuscaResultado_Destruir(TSistemaMotorBuscaResultado** PResultado)
{
	TLivro_Destruir(&(*PResultado)->Livro);
	free(*PResultado);
	*PResultado = NULL;
}

TSistemaMotorBusca* TSistemaMotorBusca_Criar(char* ArquivoEstante, char* ArquivoIndice, size_t Memoria, size_t QuantIndice)
{
	TSistemaMotorBusca* NovoMotor;
	
	NovoMotor = malloc(sizeof(TSistemaMotorBusca));
	if (!NovoMotor)
		return NULL;
	NovoMotor->ArvorePesquisa = TArvoreB_Criar(Memoria);
	NovoMotor->ArvorePesquisa->FuncaoComparar = TSistemaMotorBuscaItem_Comparar;
	NovoMotor->ArvorePesquisa->FuncaoIguais = TSistemaMotorBuscaItem_Iguais;
	NovoMotor->Estante = malloc((strlen(ArquivoEstante)+1) * sizeof(char));
	NovoMotor->Indice = malloc((strlen(ArquivoIndice)+1) * sizeof(char));
	NovoMotor->IndicePesquisa = NULL;
	NovoMotor->QuantItensIndice = QuantIndice;
	strcpy(NovoMotor->Estante, ArquivoEstante);
	strcpy(NovoMotor->Indice, ArquivoIndice);

	return NovoMotor;
}

void TSistemaMotorBusca_Destruir(TSistemaMotorBusca** PMotor)
{
	TArvoreB_Destruir(&(*PMotor)->ArvorePesquisa, TSistemaMotorBuscaItem_Destruir);
	if ((*PMotor)->IndicePesquisa)
		TSistemaManipuladorES_Destruir(&(*PMotor)->IndicePesquisa);
	free((*PMotor)->Indice);
	free((*PMotor)->Estante);
	free(*PMotor);
	*PMotor = NULL;
}

bool TSistemaMotorBusca_CarregarIndice(TSistemaMotorBusca* Motor)
{
	size_t i;
	char string[102], LivroA[51], LivroB[51];
	TSistemaMotorBuscaItem* MotorItem;
	
	Motor->IndicePesquisa = TSistemaManipuladorES_Criar(Motor->Indice, esmTextoLeitura);
	if (!Motor->IndicePesquisa)
		return false;
	for (i = 0; i < Motor->QuantItensIndice; i++)
	{
		if (TSistemaManipuladorES_ImportarProximo(Motor->IndicePesquisa, string, 102))
		{
			if (string[0] != '#')
			{
				sscanf(string, "%s %s", LivroA, LivroB);
				MotorItem = TSistemaMotorBuscaItem_Criar(LivroA, LivroB, i);
				if (!MotorItem)
					return false;
				TArvoreB_Inserir(Motor->ArvorePesquisa, MotorItem);
			}
		}
		else
			return false;
	}
	
	return true;
}

TSistemaMotorBuscaResultado* TSistemaMotorBusca_PesquisarArquivo(TSistemaMotorBusca* Motor, size_t ID, TSistemaConsulta* Consulta)
{
	char arquivoestante[64];
	size_t i, quantlivros;
	TSistemaManipuladorES* Estante;
	TSistemaMotorBuscaResultado* Resultado;
	
	sprintf(arquivoestante, "%s%lu", Motor->Estante, ID);
	Estante = TSistemaManipuladorES_Criar(arquivoestante, esmBinarioLeitura);
	if (!Estante)
		return NULL;
	quantlivros = TSistemaManipuladorES_ItensQuantidade(Estante, sizeof(TLivro));
	Resultado = TSistemaMotorBuscaResultado_Criar();
	for (i = 0; i < quantlivros; i++)
	{
		TSistemaManipuladorES_ImportarProximo(Estante, Resultado->Livro, sizeof(TLivro));
		if (!strcmp(Resultado->Livro->Titulo, Consulta->Conteudo))
		{
			Resultado->Posicao = i;
			Resultado->Estante = ID;
			TSistemaManipuladorES_Destruir(&Estante);
			return Resultado;
		}
	}
	TSistemaMotorBuscaResultado_Destruir(&Resultado);
	TSistemaManipuladorES_Destruir(&Estante);
	return NULL;
}

TSistemaMotorBuscaResultado* TSistemaMotorBusca_PesquisarIndice(TSistemaMotorBusca* Motor, TSistemaConsulta* Consulta)
{
	TSistemaMotorBuscaItem* Item;
	TSistemaMotorBuscaItem* Chave;
	
	Chave = TSistemaMotorBuscaItem_Criar(Consulta->Conteudo, Consulta->Conteudo, 0);
	Item = TArvoreB_Pesquisar(Motor->ArvorePesquisa, Chave);
	TSistemaMotorBuscaItem_Destruir((void**)&Chave);
	if (Item)
		return TSistemaMotorBusca_PesquisarArquivo(Motor, Item->ID, Consulta);
	else
		return NULL;
}
