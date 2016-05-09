#include "bignum.h"


TBigNum* TBigNum_Criar()
{
	TBigNum* NovoNumero;
	
	NovoNumero = (TBigNum)malloc(sizeof(TBigNum));
	if (NovoNumero == NULL)
	{
		printf("Erro: Erro durante alocacao de memoria.\n");
		return NULL;
	}
	NovoNumero->Algarismos = TLista_Criar();
	if (NovoNumero->Algarismos == NULL)
	{
		printf("Erro: Erro durante alocacao de memoria.\n");
		free(NovoNumero);
		return NULL;
	}

	return NovoNumero;
}

void TBigNum_Destruir(TBigNum** PNumero)
{
	if (PNumero != NULL)
	{
		if (*PNumero->Algarismos != NULL)
			TLista_Destruir(&(*PNumero->Algarismos));
		free(*PNumero);
		PNumero = NULL;
	}	
}

void TBigNum_CarregarDeArquivo(TBigNum* Numero, FILE* Arquivo)
{
	char c;
	TListaItem NovoAlgarismo;

	TLista_Limpar(Numero->Algarismos);
	c = fgetc(Arquivo);
	while ((c != '\n') && (c != ' '))
	{
		NovoAlgarismo->Valor = atoi(c);
		TLista_Adicionar(Numero->Algarismos, NovoAlgarismo;
		c = fgetc(Arquivo);
	}
}

TBigNum* TBigNum_Soma(TBigNum* NumeroX, TBigNum* NumeroY)
{
	int i, mais_um, n, tam_x, tam_y;
	TBigNum* NovoNumero;
	TListaNo* NoXTemp, NoYTemp;
	TListaItem* Algarismo;
	TListItem NovoAlgarismo;

	mais_um = 0;
	tam_x = TBigNum_Tamanho(NumeroX);
	tam_y = TBigNum_Tamanho(NumeroY);
	n = min(tam_x, tam_y);
	NoXTemp = NULL;
	NoYTemp = NULL;
	NovoNumero = TBigNum_Criar();
	for (i = 0; i < n; i++) 
	{
		TLista_Item(NumeroX->Algarismo, NoXTemp, Algarismo, -1);
		NovoAlgarismo.Valor = Algarismo->Valor + mais_um;
		TLista_Item(NumeroY->Algarismo, NoYTemp, Algarismo, -1);
		NovoAlgarismo.Valor += Algarismo->Valor;
		mais_um = NovoAlgarismo.Valor / 10;
		NovoAlgarismo.Valor = NovoAlgarismo.Valor % 10;
		TLista_Inserir(NovoNumero->Algarismos, NovoAlgarismo, NovoNumero->Algarismos->Ultimo);
	}
	if (n < tam_x)
	{
		
	}
	else if (n < tam_y)
	{
		
	}
	else if (mais_um > 0)
	{
		
	}
	
	return NovoNumero;
}

TBigNum* TBigNum_Subtrai(TBigNum* NumeroX, TBigNum* NumeroY)
{

}

void TBigNum_SalvarNoArquivo(TBigNum* Numero, FILE* Arquivo)
{
	TList_SalvarNoArquivo(Numero->Algarismos, Arquivo);
}

unsigned int TBigNum_Tamanho(TBigNum* Numero)
{
	return TList_Tamanho(Numero->Algarismos);
}
