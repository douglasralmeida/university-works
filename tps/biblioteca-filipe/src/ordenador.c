/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementação do ordenador externo
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
	Ordenador->RegistroLido = malloc(Ordenador->TamRegistro);
	fread(Ordenador->RegistroLido, Ordenador->TamRegistro, 1, Ordenador->ArquivoLeInf);
	Ordenador->Variaveis[LI]++;
	*lerdireito = true;
}

void QSortLeSuperior(TOrdenador* Ordenador, bool* lerdireito)
{
	Ordenador->RegistroLido = malloc(Ordenador->TamRegistro);
	fseek(Ordenador->ArquivoLeEscreveSup, (Ordenador->Variaveis[LS]-1) * Ordenador->TamRegistro, SEEK_SET);
	fread(Ordenador->RegistroLido, Ordenador->TamRegistro, 1, Ordenador->ArquivoLeEscreveSup);
	Ordenador->Variaveis[LS]--;
	*lerdireito = false;
}

void QSortParticao(TOrdenador* Ordenador, TMemoria* Memoria, int Esq, int Dir, int *i, int *j)
{	
	bool lerladodireito  = true;

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
		if (Memoria->Capacidade > Memoria->ItensCont + 1)
		{
			if (lerladodireito)
				QSortLeSuperior(Ordenador, &lerladodireito);
			else
				QSortLeInferior(Ordenador, &lerladodireito);
			TMemoria_Escrever(Memoria, Ordenador->RegistroLido);
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
		if (Ordenador->FuncaoComparar(Ordenador->LimiteSuperior, Ordenador->RegistroLido))
		{
			*j = Ordenador->Variaveis[ES];
			QSortEscreverMaior(Ordenador, Ordenador->RegistroLido);
			Ordenador->RegistroLido = NULL;
			continue;
		}
		if (Ordenador->FuncaoComparar(Ordenador->RegistroLido, Ordenador->LimiteInferior))
		{
			*i = Ordenador->Variaveis[EI];
			QSortEscreverMenor(Ordenador, Ordenador->RegistroLido);
			Ordenador->RegistroLido = NULL;
			continue;
		}
		TMemoria_Escrever(Memoria, Ordenador->RegistroLido);
		if (Ordenador->Variaveis[EI] - Esq < Dir - Ordenador->Variaveis[ES]) 
		{
			Ordenador->RegistroEscolhido = TMemoria_LerPrimeiro(Memoria);
			Ordenador->FuncaoCopiar(Ordenador->RegistroEscolhido, Ordenador->LimiteInferior);
			QSortEscreverMenor(Ordenador, Ordenador->RegistroEscolhido);
			Ordenador->RegistroEscolhido = NULL;			
		}
		else
		{
			Ordenador->RegistroEscolhido = TMemoria_LerUltimo(Memoria);
			Ordenador->FuncaoCopiar(Ordenador->RegistroEscolhido, Ordenador->LimiteSuperior);
			QSortEscreverMaior(Ordenador, Ordenador->RegistroEscolhido);
			Ordenador->RegistroEscolhido = NULL;				
		}
	}
	while (Ordenador->Variaveis[EI] <= Ordenador->Variaveis[ES]) 
	{
		Ordenador->RegistroEscolhido = TMemoria_LerPrimeiro(Memoria);
		QSortEscreverMenor(Ordenador, Ordenador->RegistroEscolhido);
		Ordenador->RegistroEscolhido = NULL;
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
	TMemoria_Destruir(&Memoria);
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
	NovoOrdenador->RegistroEscolhido = NULL;
	NovoOrdenador->RegistroLido = NULL;
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
	fflush(Ordenador->ArquivoLeInf);
}
