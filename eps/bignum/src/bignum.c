/*
**	TAD BIGNUM
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao de TAD para manipulacao de inteiros de tamanho arbitrario
**	
**/

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
		printf("Erro (0x21): Erro durante alocacao de memoria.\n");
		return NULL;
	}
	NovoNumero->Algarismos = TLista_Criar();
	if (NovoNumero->Algarismos == NULL)
	{
		printf("Erro (0x22): Erro durante alocacao de memoria.\n");
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

void TBigNum_ApagarZeroEsquerda(TBigNum* Numero)
{
	unsigned int i, n;
	TListaItem Algarismo;
	
	n = TBigNum_Tamanho(Numero);
	Algarismo = TLista_Item(Numero->Algarismos, 1);
	for (i = 1; i < n; i++)
	{
		Algarismo = TLista_Item(Numero->Algarismos, 1);
		if (Algarismo.Valor == 0)
		{
			TLista_Remover(Numero->Algarismos, Numero->Algarismos->Primeiro);
		}
		else
			return;
	}
}

bool TBigNum_CarregarDeArquivo(TBigNum* Numero, FILE* Arquivo)
{
	char c;
	TListaItem NovoAlgarismo;

	TLista_Limpar(Numero->Algarismos);
	c = fgetc(Arquivo);
	if (c == EOF)
		return false;
	while ((c != '\n') && (c != ' ') && (c != EOF))
	{
		NovoAlgarismo.Valor = (short)(c - '0');
		TLista_Adicionar(Numero->Algarismos, NovoAlgarismo);
		c = fgetc(Arquivo);
	}
	
	return true;
}

TRelacao TBigNum_Comparar(TBigNum* NumeroX, TBigNum* NumeroY)
{
	unsigned int i;
	unsigned int menor_tam, tam_x, tam_y;
	TListaItem AlgarismoX, AlgarismoY;
	
	tam_x = TBigNum_Tamanho(NumeroX);
	tam_y = TBigNum_Tamanho(NumeroY);
	menor_tam = MenorValor(tam_x, tam_y);	
	if (tam_x > tam_y)
	{
		for (i = 0; i < tam_x - tam_y; i++)
		{
			AlgarismoX = TLista_Item(NumeroX->Algarismos, i + 1);
			if (AlgarismoX.Valor != 0)
				return relacMaior;
		}
	}
	else if (tam_x < tam_y)
	{
		for (i = 0; i < tam_y - tam_x; i++)
		{
			AlgarismoY = TLista_Item(NumeroX->Algarismos, i + 1);
			if (AlgarismoX.Valor != 0)
				return relacMenor;
		}
	}
	for (i = 0; i < menor_tam; i++)
	{
		AlgarismoX = TLista_Item(NumeroX->Algarismos, tam_x - menor_tam + i + 1);
		AlgarismoY = TLista_Item(NumeroY->Algarismos, tam_y - menor_tam + i + 1);
		if	(AlgarismoX.Valor < AlgarismoY.Valor)
			return relacMenor;
		else if (AlgarismoX.Valor > AlgarismoY.Valor)
			return relacMaior;
	}
	
	return relacIgual;
}

bool TBigNum_EZero(TBigNum* Numero)
{
	TListaItem i;
	
	if (TBigNum_Tamanho(Numero) == 1)
	{
		i = TLista_Item(Numero->Algarismos, 1);
		if (i.Valor == 0)
			return true;
	}
	return false;
}

void TBigNum_Imprimir(TBigNum* Numero)
{
	TLista_Imprimir(Numero->Algarismos);
}

bool TBigNum_SalvarNoArquivo(TBigNum* Numero, FILE* Arquivo)
{
	return TLista_SalvarNoArquivo(Numero->Algarismos, Arquivo);
}

TBigNum* TBigNum_Somar(TBigNum* NumeroX, TBigNum* NumeroY)
{
	unsigned int i;
	unsigned short mais_um; 
	unsigned int menor_tam, tam_x, tam_y;
	TBigNum* NovoNumero;
	TListaItem Algarismo, NovoAlgarismo;

	mais_um = 0;
	tam_x = TBigNum_Tamanho(NumeroX);
	tam_y = TBigNum_Tamanho(NumeroY);
	menor_tam = MenorValor(tam_x, tam_y);
	NovoNumero = TBigNum_Criar();
	for (i = 0; i < menor_tam; i++)
	{
		Algarismo = TLista_Item(NumeroX->Algarismos, tam_x - i);
		NovoAlgarismo.Valor = Algarismo.Valor + mais_um;
		Algarismo = TLista_Item(NumeroY->Algarismos, tam_y - i);
		NovoAlgarismo.Valor += Algarismo.Valor;
		mais_um = NovoAlgarismo.Valor / 10;
		NovoAlgarismo.Valor = NovoAlgarismo.Valor % 10;
		TLista_Inserir(NovoNumero->Algarismos, NovoAlgarismo, NULL);
	}
	if (menor_tam < tam_x)
	{
		for (i = tam_x - menor_tam; i > 0; i--)
		{
			Algarismo = TLista_Item(NumeroX->Algarismos, i);
			NovoAlgarismo.Valor = Algarismo.Valor + mais_um;
			mais_um = NovoAlgarismo.Valor / 10;
			NovoAlgarismo.Valor = NovoAlgarismo.Valor % 10;
			TLista_Inserir(NovoNumero->Algarismos, NovoAlgarismo, NULL);
		}
	}
	else if (menor_tam < tam_y)
	{
		for (i = tam_y - menor_tam; i > 0; i--)
		{
			Algarismo = TLista_Item(NumeroY->Algarismos, i);
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

TBigNum* TBigNum_Subtrair(TBigNum* NumeroX, TBigNum* NumeroY)
{
	unsigned int i;
	unsigned short menos_um, ant_menos_um; 
	unsigned int menor_tam, maior_tam;
	TBigNum* MaiorNumero;
	TBigNum* MenorNumero;	
	TBigNum* NovoNumero;
	TListaItem Algarismo, NovoAlgarismo;

	menos_um = 0;
	if (TBigNum_Comparar(NumeroX, NumeroY) == relacMaior)
	{
		MaiorNumero = NumeroX;
		MenorNumero = NumeroY;
		maior_tam = TBigNum_Tamanho(NumeroX);
		menor_tam = TBigNum_Tamanho(NumeroY);
	}
	else
	{
		MaiorNumero = NumeroY;
		MenorNumero = NumeroX;
		maior_tam = TBigNum_Tamanho(NumeroY);
		menor_tam = TBigNum_Tamanho(NumeroX);
	}
	NovoNumero = TBigNum_Criar();
	for (i = 0; i < menor_tam; i++)
	{
		Algarismo = TLista_Item(MaiorNumero->Algarismos, maior_tam - i);
		NovoAlgarismo.Valor = Algarismo.Valor;
		Algarismo = TLista_Item(MenorNumero->Algarismos, menor_tam - i);
		ant_menos_um = menos_um;
		if (NovoAlgarismo.Valor < (Algarismo.Valor + menos_um))
		{
			menos_um = 1;
			NovoAlgarismo.Valor += 10;
		}
		else
		{
			menos_um = 0;
		}
 		NovoAlgarismo.Valor -= (Algarismo.Valor + ant_menos_um);
		TLista_Inserir(NovoNumero->Algarismos, NovoAlgarismo, NULL);
	}
	for (i = maior_tam - menor_tam; i > 0; i--)
	{
		Algarismo = TLista_Item(MaiorNumero->Algarismos, i);
		NovoAlgarismo.Valor = Algarismo.Valor;
		ant_menos_um = menos_um;
		if (NovoAlgarismo.Valor < (1 + menos_um))
		{
			menos_um = 1;
			NovoAlgarismo.Valor += 10;
		}
		else
		{
			menos_um = 0;
		}
		NovoAlgarismo.Valor -= ant_menos_um;
		TLista_Inserir(NovoNumero->Algarismos, NovoAlgarismo, NULL);
	}	
	
	TBigNum_ApagarZeroEsquerda(NovoNumero);
	return NovoNumero;
}

unsigned int TBigNum_Tamanho(TBigNum* Numero)
{
	return TLista_Tamanho(Numero->Algarismos);
}
