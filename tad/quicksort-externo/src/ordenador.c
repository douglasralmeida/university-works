/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação do ordenador externo usando quicksort
*/
#include "memoria.h"
#include "ordenador.h"

#define EI 0
#define ES 1
#define LI 2
#define LS 3

void QSortEscreverMaior(TOrdenador* Ordenador, void* Registro)
{
	fseek(Ordenador->ArquivoLeEscreveSup, (Ordenador->Variaveis[ES]-1) * Ordenador->TamRegistro, SEEK_SET);
	fwrite(Registro, Ordenador->TamRegistro, 1, Ordenador->ArquivoLeEscreveSup);
	Ordenador->Variaveis[ES]--;
	free(Registro);
}

void QSortEscreverMenor(TOrdenador* Ordenador, void* Registro)
{
	fwrite(Registro, Ordenador->TamRegistro, 1, Ordenador->ArquivoEscreveInf);
	Ordenador->Variaveis[EI]++;
	free(Registro);
}

void QSortLeInferior(TOrdenador* Ordenador, bool* lerdireito)
{
	Ordenador->Registro = malloc(Ordenador->TamRegistro);
	fread(Ordenador->Registro, Ordenador->TamRegistro, 1, Ordenador->ArquivoLeInf);
	Ordenador->Variaveis[LI]++;
	*lerdireito = true;
}

void QSortLeSuperior(TOrdenador* Ordenador, bool* lerdireito)
{
	Ordenador->Registro = malloc(Ordenador->TamRegistro);
	fseek(Ordenador->ArquivoLeEscreveSup, (Ordenador->Variaveis[LS]-1) * Ordenador->TamRegistro, SEEK_SET);
	fread(Ordenador->Registro, Ordenador->TamRegistro, 1, Ordenador->ArquivoLeEscreveSup);
	Ordenador->Variaveis[LS]--;
	*lerdireito = false;
}

void QSortParticao(TOrdenador* Ordenador, int Esq, int Dir, int *i, int *j)
{	
	bool lerladodireito  = true;
	void* LimInferior;
	void* LimSuperior;
	void* RegEscolhido;
	TMemoria* Memoria;

	/* -- só definir variáveis --*/
	LimInferior = malloc(Ordenador->TamRegistro);
	Ordenador->FuncaoCopiar(Ordenador->LimiteInferior, LimInferior);
	LimSuperior = malloc(Ordenador->TamRegistro);
	Ordenador->FuncaoCopiar(Ordenador->LimiteSuperior, LimSuperior);
	Memoria = TMemoria_Criar(Ordenador->MaxItensPorVez);
	Memoria->FuncaoComparar = Ordenador->FuncaoComparar;
	Ordenador->Variaveis[EI] = Esq;
	Ordenador->Variaveis[ES] = Dir;
	Ordenador->Variaveis[LI] = Esq;
	Ordenador->Variaveis[LS] = Dir;
	*j = Dir + 1;
	*i = Esq - 1;
	fseek(Ordenador->ArquivoLeInf, (Esq - 1) * Ordenador->TamRegistro, SEEK_SET);
	fseek(Ordenador->ArquivoEscreveInf, (Esq - 1) * Ordenador->TamRegistro, SEEK_SET);

	while (Ordenador->Variaveis[LS] >= Ordenador->Variaveis[LI])
	{
		if (Memoria->ItensCont < Memoria->Capacidade - (size_t)1)
		{
			if (lerladodireito)
				QSortLeSuperior(Ordenador, &lerladodireito);
			else
				QSortLeInferior(Ordenador, &lerladodireito);
			TMemoria_EscreverNaOrdem(Memoria, Ordenador->Registro);
			continue;
		}
		if (Ordenador->Variaveis[LS] == Ordenador->Variaveis[ES])
			QSortLeSuperior(Ordenador, &lerladodireito);
		else if (Ordenador->Variaveis[LI] == Ordenador->Variaveis[EI])
			QSortLeInferior(Ordenador, &lerladodireito);
		else if (lerladodireito)
			QSortLeSuperior(Ordenador, &lerladodireito);
		else
			QSortLeInferior(Ordenador, &lerladodireito);
		if (Ordenador->FuncaoComparar(LimSuperior, Ordenador->Registro))
		{
			*j = Ordenador->Variaveis[ES];
			QSortEscreverMaior(Ordenador, Ordenador->Registro);			
			continue;
		}
		if (Ordenador->FuncaoComparar(Ordenador->Registro, LimInferior))
		{
			*i = Ordenador->Variaveis[EI];
			QSortEscreverMenor(Ordenador, Ordenador->Registro);
			continue;
		}
		TMemoria_EscreverNaOrdem(Memoria, Ordenador->Registro);
		if (Ordenador->Variaveis[EI] - Esq < Dir - Ordenador->Variaveis[ES])
		{
			RegEscolhido = TMemoria_LerPrimeiro(Memoria);
			Ordenador->FuncaoCopiar(RegEscolhido, LimInferior);
			QSortEscreverMenor(Ordenador, RegEscolhido);
		}
		else
		{
			RegEscolhido = TMemoria_LerUltimo(Memoria);
			Ordenador->FuncaoCopiar(RegEscolhido, LimSuperior);
			QSortEscreverMaior(Ordenador, RegEscolhido);		
		}
	}
	while (Ordenador->Variaveis[EI] <= Ordenador->Variaveis[ES]) 
	{
		RegEscolhido = TMemoria_LerPrimeiro(Memoria);
		QSortEscreverMenor(Ordenador, RegEscolhido);
	}
	fflush(Ordenador->ArquivoLeInf);
	fflush(Ordenador->ArquivoEscreveInf);
	fflush(Ordenador->ArquivoLeEscreveSup);
	Ordenador->Registro = NULL;
	free(LimInferior);
	free(LimSuperior);
	TMemoria_Destruir(&Memoria);
}

void QSortIniciar(TOrdenador* Ordenador, int Esq, int Dir)
{
	int i, j;
	
	if (Dir - Esq > 0)
	{
		QSortParticao(Ordenador, Esq, Dir, &i, &j);
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
}

TOrdenador* TOrdenador_Criar(char* NomeArquivo, TFuncaoComparar FuncaoComparar, TFuncaoCopiar FuncaoCopiar, size_t MaxItensPorVez)
{
	TOrdenador* NovoOrdenador;

	NovoOrdenador = malloc(sizeof(TOrdenador));
	if (!NovoOrdenador)
		return NULL;
	NovoOrdenador->ArquivoLeEscreveSup = fopen(NomeArquivo, "r+b");
	if (!NovoOrdenador->ArquivoLeEscreveSup)
	{
		free(NovoOrdenador);
		return NULL;
	}
	NovoOrdenador->ArquivoLeInf = fopen(NomeArquivo, "r+b");
	if (!NovoOrdenador->ArquivoLeInf)
	{
		fclose(NovoOrdenador->ArquivoLeEscreveSup);
		free(NovoOrdenador);
		return NULL;
	}
	NovoOrdenador->ArquivoEscreveInf = fopen(NomeArquivo, "r+b");
	if (!NovoOrdenador->ArquivoEscreveInf)
	{
		fclose(NovoOrdenador->ArquivoLeEscreveSup);
		fclose(NovoOrdenador->ArquivoLeInf);
		free(NovoOrdenador);
		return NULL;
	}
	NovoOrdenador->FuncaoComparar = FuncaoComparar;
	NovoOrdenador->FuncaoCopiar = FuncaoCopiar;
	NovoOrdenador->LimiteInferior = NULL;
	NovoOrdenador->LimiteSuperior = NULL;
	NovoOrdenador->MaxItensPorVez = MaxItensPorVez;
	NovoOrdenador->Quantidade = 0;
	NovoOrdenador->Registro = NULL;
	NovoOrdenador->TamRegistro = 0;

	return NovoOrdenador;
}

void TOrdenador_Destruir(TOrdenador** POrdenador)
{
	fclose((*POrdenador)->ArquivoLeEscreveSup);
	fclose((*POrdenador)->ArquivoLeInf);
	fclose((*POrdenador)->ArquivoEscreveInf);
	free(*POrdenador);
	*POrdenador = NULL;
}

void TOrdenador_Ordenar(TOrdenador* Ordenador)
{
	QSortIniciar(Ordenador, 1, Ordenador->Quantidade);
}
