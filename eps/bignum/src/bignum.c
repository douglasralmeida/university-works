#include "sysutils.h"
#include "item.h"
#include "list.h"
#include "bignum.h"


TBigNum* TBigNum_Criar()
{
	TBigNum* NovoNumero;
	
	NovoNumero = (TBigNum*)malloc(sizeof(TBigNum));
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
		if ((*PNumero)->Algarismos != NULL)
			TLista_Destruir(&(*PNumero)->Algarismos);
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
		NovoAlgarismo.Valor = (short)(c - '0');
		TLista_Adicionar(Numero->Algarismos, NovoAlgarismo);
		c = fgetc(Arquivo);
	}
}

bool TBigNum_EZero(TBigNum* Numero)
{
	TListaItem i;
	
	if (TBigNum_Tamanho(Numero) == 1)
	{
		TLista_Item(Numero->Algarismos, Numero->Algarismos->Ultimo, &i, 0);
		if (i.Valor == 0)
			return true;
	}
	
	return false;
}

TBigNum* TBigNum_Somar(TBigNum* NumeroX, TBigNum* NumeroY)
{
	unsigned int i, n;
	unsigned short mais_um; 
	unsigned int tam_x, tam_y;
	TBigNum* NovoNumero;
	TListaNo* NoXTemp;
	TListaNo* NoYTemp;
	TListaItem Algarismo, NovoAlgarismo;

	mais_um = 0;
	tam_x = TBigNum_Tamanho(NumeroX);
	tam_y = TBigNum_Tamanho(NumeroY);
	n = Min(tam_x, tam_y);
	NoXTemp = NULL;
	NoYTemp = NULL;
	NovoNumero = TBigNum_Criar();
	for (i = 0; i < n; i++) 
	{
		TLista_Item(NumeroX->Algarismos, NoXTemp, &Algarismo, -1);
		NovoAlgarismo.Valor = Algarismo.Valor + mais_um;
		TLista_Item(NumeroY->Algarismos, NoYTemp, &Algarismo, -1);
		NovoAlgarismo.Valor += Algarismo.Valor;
		mais_um = NovoAlgarismo.Valor / 10;
		NovoAlgarismo.Valor = NovoAlgarismo.Valor % 10;
		TLista_Inserir(NovoNumero->Algarismos, NovoAlgarismo, NULL);
	}
	if (n < tam_x)
	{
		for (i = 0; i < tam_x - n; i++)
		{
			TLista_Item(NumeroX->Algarismos, NoXTemp, &Algarismo, -1);
			NovoAlgarismo.Valor = Algarismo.Valor + mais_um;
			mais_um = NovoAlgarismo.Valor / 10;
			NovoAlgarismo.Valor = NovoAlgarismo.Valor % 10;
			TLista_Inserir(NovoNumero->Algarismos, NovoAlgarismo, NULL);
		}
	}
	else if (n < tam_y)
	{
		for (i = 0; i < tam_y - n; i++)
		{
			TLista_Item(NumeroY->Algarismos, NoYTemp, &Algarismo, -1);
			NovoAlgarismo.Valor = Algarismo.Valor + mais_um;
			mais_um = NovoAlgarismo.Valor / 10;
			NovoAlgarismo.Valor = NovoAlgarismo.Valor % 10;
			TLista_Inserir(NovoNumero->Algarismos, NovoAlgarismo, NULL);
	
		}
	}
	else if (mais_um > 0)
	{
		NovoAlgarismo.Valor = 1;
		mais_um = 0;
		TLista_Inserir(NovoNumero->Algarismos, NovoAlgarismo, NULL);
	}
	
	return NovoNumero;
}
/*
TBigNum* TBigNum_Subtrai(TBigNum* NumeroX, TBigNum* NumeroY)
{

}*/

void TBigNum_SalvarNoArquivo(TBigNum* Numero, FILE* Arquivo)
{
	TLista_SalvarNoArquivo(Numero->Algarismos, Arquivo);
}

unsigned int TBigNum_Tamanho(TBigNum* Numero)
{
	return TLista_Tamanho(Numero->Algarismos);
}
