#include "rua.h"

TRua* TRua_Criar(int Origem, int Destino, int TempoMedio)
{
	TRua* NovaRua;

	NovaRua = (TRua*)malloc(sizeof(TRua));
	if (NovaRua != NULL)
	{
		NovaRua->Origem = Origem;
		NovaRua->Destino = Destino;
		NovaRua->TempoMedio = TempoMedio;
	}

	return NovaRua;
}

void TRua_Destruir(void** PRua)
{
	free(*PRua);
	PRua = NULL;
}

TRua* TRua_Carregar(FILE* Arquivo)
{
	int destino;
	int origem;
	int tempomedio;

	fscanf("%d %d %d", &origem, &destino, &tempomedio);
	return TRua_Criar(origem, destino, tempomedio);
}