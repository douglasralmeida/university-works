/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação do ordenador externo
*/
#include "memoria.h"
#include "ordenador.h"

void QSortParticao(TOrdenador* Ordenador, TMemoria* Memoria, int Esq, int Dir, int *i, int *j)
{
	int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq, NRArea = 0, Linf = INT_MIN, Lsup = INT_MAX;
	bool OndeLer = true;
	TipoRegistro UltLido, R;
	
	fseek (*ArqLi, (Li - 1) * sizeof(TipoRegistro), SEEK_SET);
	fseek (*ArqEi, (Ei - 1) * sizeof(TipoRegistro), SEEK_SET);
	*i = Esq - 1;  *j = Dir + 1;
	while (Ls >= Li)
	{
		if (NRArea < TAMAREA - 1) 
		{
			if (OndeLer)
				LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
			else
				LeInf(ArqLi, &UltLido, &Li, &OndeLer);
			InserirArea(&Area, &UltLido, &NRArea);
			continue;
		}
		if (Ls == Es) 
			LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
		else if (Li == Ei)
			LeInf(ArqLi, &UltLido, &Li, &OndeLer);
		else if (OndeLer)
			LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
		else
			LeInf(ArqLi, &UltLido, &Li, &OndeLer);
		if (UltLido.Chave > Lsup) 
		{
			*j = Es;
			EscreveMax(ArqLEs, UltLido, &Es);
			continue;
		}
		if (UltLido.Chave < Linf) 
		{
			*i = Ei;
			EscreveMin(ArqEi, UltLido, &Ei);
			continue;
		}
		InserirArea(&Area, &UltLido, &NRArea);
		if (Ei - Esq < Dir - Es) 
		{
			RetiraMin(&Area, &R, &NRArea);
			EscreveMin(ArqEi, R, &Ei);
			Linf = R.Chave;
		}
		else
		{
			RetiraMax(&Area, &R, &NRArea);
			EscreveMax(ArqLEs, R, &Es);
			Lsup = R.Chave;
		}
	}
	while (Ei <= Es) 
	{
		RetiraMin(&Area, &R, &NRArea);
		EscreveMin(ArqEi, R, &Ei);
	}
}

void QSortIniciar(TOrdenador* Ordenador, int Esq, int Dir)
{
	int i, j;
	TMemoria* Memoria;
	
	if (Dir - Esq < 1)
		return;
		
	Memoria = TMemoria_Criar(Ordenador->MaxItensPorVez);
	QSortParticao(Ordenador, Memoria, Esq, Dir, &i, &j);
	if (i - Esq < Dir - j) 
	{
		/* ordene primeiro o subarquivo menor */
		QSortIniciar(Ordenador, Esq, i);
		QSortIniciar(Ordenador, j, Dir);
	}
	else 
	{
		QSortIniciar(Ordenador, j, Dir);
		QSortIniciar(Ordenador, Esq, i);
	}
}

TOrdenador* TOrdenador_Criar(TArquivo* Dados, TFuncaoComparar FuncaoComparar, size_t MaxItensPorVez)
{
	TOrdenador* NovoOrdenador;

	NovoOrdenador = malloc(sizeof(TOrdenador));
	NovoOrdenador->ArquivoDados = Dados;
	NovoOrdenador->FuncaoComparar = FuncaoComparar;
	NovoOrdenador->TamanhoMemoria = MaxItensPorVez;

	return NovoOrdenador;
}

void TOrdenador_Destruir(TOrdenador** POrdenador)
{
	free(*POrdenador);
	POrdenador = NULL;
}

void TOrdenador_Ordenar(TOrdenador* Ordenador)
{
	QSortIniciar(Ordenador);
}
