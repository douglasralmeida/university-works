/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Estrutura de dados do motor de busca
*/

#ifndef SISTEMA_MB_H
#define SISTEMA_MB_H

#include "boolutils.h"
#include "arvoreb.h"
#include "livro.h"
#include "sistema_consulta.h"
#include <stdio.h>

typedef struct _TSistemaMotorBuscaItem {
	char* NomeInicial;
	char* NomeFinal;
	size_t ID;
} TSistemaMotorBuscaItem;

typedef struct _TSistemaMotorBusca {
	TArvoreB* ArvorePesquisa;
	char* Estante;
	char* Indice;
	TSistemaManipuladorES* IndicePesquisa;
	size_t QuantItensIndice;
} TSistemaMotorBusca;

TSistemaMotorBuscaItem* TSistemaMotorBuscaItem_Criar(char* Inicio, char* Final, size_t ID);

void TSistemaMotorBuscaItem_Destruir(TSistemaMotorBuscaItem** PSistemaMotorBuscaItem);

TSistemaMotorBusca* TSistemaMotorBusca_Criar(char* ArquivoIndice, char* ArquivoEstante, size_t Memoria, size_t QuantIndice);

void TSistemaMotorBusca_Destruir(TSistemaMotorBusca** PMotor);

bool TSistemaMotorBusca_CarregarIndice(TSistemaMotorBusca* Motor);

TLivro* TSistemaMotorBusca_PesquisarArquivo(TSistemaMotorBusca* Motor, size_t ID, TSistemaConsulta* Consulta);

TLivro* TSistemaMotorBusca_PesquisarIndice(TSistemaMotorBusca* Motor, TSistemaConsulta* Consulta);

#endif
