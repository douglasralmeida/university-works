/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação do ordenador externo
*/

#include "ordenador.h"

TOrdenador* TOrdenador_Criar(TArquivo* Dados, TFuncaoComparar FuncaoComparar, size_t TamanhoMemoria)
{
	TOrdenador* NovoOrdenador;

	NovoOrdenador = malloc(sizeof(TOrdenador));
	NovoOrdenador->ArquivoDados = Dados;
	NovoOrdenador->FuncaoComparar = FuncaoComparar;
	NovoOrdenador->TamanhoMemoria = TamanhoMemoria;

	return NovoOrdenador;
}

void TOrdenador_Destruir(TOrdenador** POrdenador)
{
	free(*POrdenador);
	POrdenador = NULL;
}

void TOrdenador_Ordenar(TOrdenador* Ordenador)
{
	//OrdenacaoExterna();
}
