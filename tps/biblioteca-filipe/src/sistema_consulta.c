/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação das consultas do sistema
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistema_consulta.h"

TSistemaConsulta* TSistemaConsulta_Criar(char* Consulta)
{
	TSistemaConsulta* NovaConsulta;

	NovaConsulta = malloc(sizeof(TSistemaConsulta));
	if (!NovaConsulta)
		return NULL;
	strcpy(NovaConsulta->Conteudo, Consulta);
	
	return NovaConsulta;
}

void TSistemaConsulta_Destruir(void** PConsulta)
{
	free(*PConsulta);
	*PConsulta = NULL;
}

void TSistemaConsulta_SalvarNoArquivo(TSistemaConsulta* Consulta)
{
	
}
