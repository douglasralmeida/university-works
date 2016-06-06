#include "servidor_impressao.h"

TImpressao* TImpressao_Criar(TUsuario* Usuario)
{
	TImpressao* NovaImpressao;
	
	NovaImpressao = (TUsuario*)malloc(sizeof(TUsuario));
	NovaImpressao->Usuario = Usuario;
	
	return NovaImpressao;
}

void TImpressao_Destruir(void** PImpressao)
{
	free(*PImpressao);
	PImpressao = NULL;
}

TImpressora* TImpressora_Criar(size_t Capacidade, size_t Escalonador, char* Nome)
{
	TImpressora* NovaImpressora;
	TFuncaoComparar FuncImpComparar;
	TFuncaoDestruir FuncImpDestruir;
	
	FuncImpDestruir = &TImpressao_Destruir;
	NovaImpressora = (TImpressora*)malloc(sizeof(TImpressora));
	NovaImpressora->Capacidade = Capacidade;
	NovaImpressora->Escalonador = Escalonador;
	strcopy(NovaImpressora->Nome, Nome);
	switch (Escalonador)
		case 1:
			FuncImpComparar = NULL;
		break;
		case 2:
			FuncImpComparar = &TImpressao_Comparar1;
		break;
		case 3:
			FuncImpComparar = &TImpressao_Comparar2;
		break;
		
	NovaImpressora->FilaImpressao = TFilaPrioridade_Criar(1024, FuncImpComparar, FuncImpDestruir);
	
	return NovaImpressora;
}

void TImpressora_Destruir(TImpressora** PImpressora)
{
	TFilaPrioridade_Destruir(&(*PImpressora)->FilaImpressao);
	free(*PUsuario);
	PUsuario = NULL;	
}

void TImpressora_Imprimir(void)
{
	
}