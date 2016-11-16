/*
**	PLANO DE DOMINAÇÃO
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Aplicativo principal
*/
#include <stdio.h>
#include <stdlib.h>
#include <mundo.h>

int main()
{
	TMundo* Mundo;
	unsigned long long altura;
	unsigned long long largura;

	if (scanf("%llu %llu", &largura, &altura) && altura && largura)
	{
		Mundo = TMundo_Criar(altura, largura);
		if (Mundo)
		{
			TMundo_ReceberEntrada(Mundo);
			TMundo_Processar(Mundo);
			TMundo_ExibirResultado(Mundo);
			TMundo_Destruir(&Mundo);
		}
		else
			exit(EXIT_FAILURE);
	}
	else
		exit(EXIT_FAILURE);

	exit(EXIT_SUCCESS);
}
