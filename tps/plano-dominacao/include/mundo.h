/*
**	PLANO DE DOMINAÇÃO
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação do TAD Mundo
*/
#ifndef MUNDO_H
#define MUNDO_H

typedef unsigned long long TPopulacao;

typedef struct _TMundo
{
	TPopulacao* Cidades;	
	unsigned long long Altura;
	unsigned long long Largura;
	unsigned long long PopulacaoTotal;
} TMundo;

TMundo* TMundo_Criar(unsigned long long Altura, unsigned long long Largura);

void TMundo_Destruir(TMundo** PMundo);

void TMundo_ExibirResultado(TMundo* Mundo);

void TMundo_Processar(TMundo* Mundo);

void TMundo_ReceberEntrada(TMundo* Mundo);

#endif
