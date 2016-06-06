#include "usuario.h"

TUsuario* TUsuario_Criar(char* Nome, size_t Prioridade)
{
	TUsuario* NovoUsuario;
	
	NovoUsuario = (TUsuario*)malloc(sizeof(TUsuario));
	strcpy(NovoUsuario->Nome, Nome);
	NovoUsuario->Prioridade = Prioridade;
	
	return NovoUsuario;
}

void TUsuario_Destruir(void** PUsuario)
{
	free(*PUsuario);
	PUsuario = NULL;
}

bool TUsuario_Iguais(void* Usuario1, void* Usuario2)
{
	TUsuario* U1;
	TUsuario* U2;
	
	U1 = (TUsuario*)Usuario1;
	U2 = (TUsuario*)Usuario2;
	
	return (!strcmp(U1->Nome, U2->Nome));
}
