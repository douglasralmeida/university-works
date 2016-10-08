/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Estrutura de dados do sistema da biblioteca
*/

#ifndef SISTEMA_H
#define SISTEMA_H

#include "core.h"
#include "fila.h"

typedef struct _TSistema {
	TFila* Consultas;
	size_t MaxItensMemoria;
	char* NomeEstante;
	char* NomeIndice;
	char* NomeLivrosOrdenados;
	char* NomeTemp;
	unsigned long QuantEstantes;
	unsigned long QuantLivros;
	unsigned long QuantLivrosEstantes;
} TSistema;


/* aloca */
TSistema* TSistema_Criar(void);

/* desaloca */
void TSistema_Destruir(TSistema** PSistema);

/* ordena os livros em ordem alfabética */
bool TSistema_OrdenarLivros(TSistema* Sistema);

/* simula as consultas de livros */
void TSistema_ProcessarConsultas(TSistema* Sistema);

/* recebe os dados de consulta do prompt de comando */
bool TSistema_ReceberConsultas(TSistema* Sistema, unsigned long NumConsultas);

/* recebe os dados do prompt de comando */
bool TSistema_ReceberEntrada(TSistema* Sistema);

/* recebe os livros do prompt de comando */
bool TSistema_ReceberLivros(TSistema* Sistema);

/* salva os livros em um arquivo */
bool TSistema_SalvarLivros(TSistema* Sistema);

/* executa simulação com ordenação de itens e pesquisa */
void TSistema_Simular(TSistema* Sistema);

#endif
