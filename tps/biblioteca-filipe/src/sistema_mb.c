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
	return false;
}

bool TSistemaMotorBuscaItem_Iguais(void* Item1, void* Item2)
{
	return false;
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
	TArvoreB_Destruir(NovoMotor->ArvorePesquisa, TSistemaMotorBuscaItem_Destruir);
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
	char String[102], LivroA[51], LivroB[51];
	TSistemaMotorBuscaItem* MotorItem;
	
	Motor->IndicePesquisa = TSistemaManipuladorES(Motor->Indice, esmTextoLeitura);
	if (!Motor->IndicePesquisa)
		return false;
	for (i = 0; i < Motor->QuantItensIndice; i++)
	{
		if (TSistemaManipuladorES_ImportarProximo(Motor->IndicePesquisa, string, 0))
		{
			sscanf("%s %s", LivroA, LivroB);
			MotorItem = TSistemaMotorBuscaItem_Criar(LivroA, LivroB, i);
			if (!MotorItem)
				return false;
			TArvore_Inserir(Motor->ArvorePesquisa, MotorItem);
		}
		else
			return false;
	}
	
	return true;
}

TLivro* TSistemaMotorBusca_PesquisarArquivo(TSistemaMotorBusca* Motor, size_t ID, TSistemaConsulta* Consulta)
{
	char arquivoestante[64];
	size_t i, quantlivros;
	TLivro* Livro;
	TSistemaManipuladorES* Estante;
	
	sprintf(arquivoestante, "%s%lu", Motor->Estante, ID);
	Estante = TSistemaManipuladorES_Criar(arquivoestante, esmBinarioLeitura);
	if (!Estante)
		return NULL;
	Livro = TLivro_Criar();
	quantlivros = TSistemaManipuladorES_ItensQuantidade(Estante, sizeof(TLivro));
	for (i = 0; i < quantlivros; i++)
	{
		TSistemaManipuladorES_ImportarProximo(Estante, Livro, sizeof(TLivro));
		if (!strcmp(Livro->Titulo, Consulta->Conteudo))
		{
			TSistemaManipuladorES_Destruir(&Estante);
			return Livro;
		}
	}

	TSistemaManipuladorES_Destruir(&Estante);
	return NULL;
}

TLivro* TSistemaMotorBusca_PesquisarIndice(TSistemaMotorBusca* Motor, TSistemaConsulta* Consulta)
{
	TSistemaMotorBuscaItem* ItemEncontrado;
	TSistemaMotorBuscaItem* Chave;
	
	Chave = TSistemaMotorBuscaItem_Criar(Consulta->Conteudo, Consulta->Conteudo, 0);
	Item = TArvoreB_Pesquisar(Motor->ArvorePesquisa, Chave);
	TSistemaMotorBuscaItem_Destruir(&Chave);
	if (Item)
		return TSitemaMotorBusca_PesquisarArquivo(Motor, Item->ID, Consulta);
	else
		return NULL;
}
