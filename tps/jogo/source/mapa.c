#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"
#include "funcoes.h"
#include "arquivo.h"
#include "mapa.h"

TMapa* MapaCriar(void)
{
	TMapa* Mapa;
	
	Mapa = (TMapa*)malloc(sizeof(TMapa));
	Mapa->AudiosPassadas = NULL;
	Mapa->Borda.Superior = 0;
	Mapa->Borda.Inferior = 0;
	Mapa->Borda.Direita = 0;
	Mapa->Borda.Esquerda = 0;
	Mapa->Borda.SuperiorDireita = 0;
	Mapa->Borda.SuperiorEsquerda = 0;
	Mapa->Borda.InferiorDireita = 0;
	Mapa->Borda.InferiorEsquerda = 0;
	Mapa->CursorFoco = NULL;
	Mapa->CursorMouse = NULL;
	Mapa->MascaraAltura = 32;
	Mapa->MascaraLargura = 32;
	Mapa->Mascaras = NULL;	
	Mapa->MundoAltura = 0;
	Mapa->MundoLargura = 0;
	Mapa->ObjetosColisao = 0;
	Mapa->PontoVisao.x = 0;
	Mapa->PontoVisao.y = 0;
	Mapa->QuantMascaras = 0;
	Mapa->QuantPassadas = 0;
	Mapa->TamEstruturaX = 0;
	Mapa->TamEstruturaY = 0;
	Mapa->Estrutura = NULL;
	
	return Mapa;
}

void MapaDestruir(TMapa** PMapa)
{
	if ((*PMapa)->AudiosPassadas != NULL)
		MatrizDestruir((void***)&((*PMapa)->AudiosPassadas), (*PMapa)->QuantPassadas);
	if ((*PMapa)->CursorFoco != NULL)
		free((*PMapa)->CursorFoco);
	if ((*PMapa)->CursorMouse != NULL)
		free((*PMapa)->CursorMouse);
	if ((*PMapa)->Mascaras != NULL)
		MatrizDestruir((void***)&((*PMapa)->Mascaras), (*PMapa)->QuantMascaras);
	if ((*PMapa)->Estrutura != NULL)
		MatrizDestruir((void***)&((*PMapa)->Estrutura), (*PMapa)->TamEstruturaY);
	free(*PMapa);
	*PMapa = NULL;
}

int MapaAbrir(TMapa* Mapa, char* ArquivoMapa)
{
	FILE* Arquivo;
	int i;
	int j;
	int TempInt;
	int QuadrantesInformados;
	int TemSanguePadrao;
	int ColisaoPadrao;
	int PassadaPadrao;
	int MascaraPadrao;
	
	Arquivo = ArquivoAbrir(REC_MAPA, ArquivoMapa);
	if (Arquivo != NULL)
	{
		if (!SecaoChecar(":ARQUIVOMAPA", Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (LerPropriedadeInteiro("Versao", &TempInt, Arquivo))
		{
			if (TempInt != 1)
			{
				ArquivoFechar(Arquivo);
				return FALSE;
			}
		}
		else
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!SecaoChecar(":DEFINICOES", Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("AlturaMapa", &(Mapa->TamEstruturaY), Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("AudiosPassadas", &(Mapa->QuantPassadas), Arquivo))
		{	
			ArquivoFechar(Arquivo);
			return FALSE;
		}	
		Mapa->CursorMouse = CVetorCriar(MAX_VETORCHAR);
		if (Mapa->CursorMouse == NULL)
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeString("CursorArquivo", Mapa->CursorMouse, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		Mapa->CursorFoco = (TPonto*)malloc(sizeof(TPonto));
		if (Mapa->CursorFoco == NULL)
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadePonto("CursorFoco", Mapa->CursorFoco, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}	
		if (!LerPropriedadeInteiro("LarguraMapa", &(Mapa->TamEstruturaX), Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("NumeroMascaras", &(Mapa->QuantMascaras), Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("QuadrantesInformados", &QuadrantesInformados, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("QuadranteFinal", &(Mapa->QuadraFinal), Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}

		if (!SecaoChecar(":MASCARAS", Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;	
		}
		//o nome do arquivo pode ter no maximo 32 caracteres
		Mapa->Mascaras = CMatrizCriar(Mapa->QuantMascaras, MAX_VETORCHAR);
		if (!Mapa->Mascaras)
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		for (i = 0; i < Mapa->QuantMascaras; i++)
			LerLinhaStr(Mapa->Mascaras[i], Arquivo);
	
		if (!SecaoChecar(":PASSADAS", Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;	
		}		
		Mapa->AudiosPassadas = CMatrizCriar(Mapa->QuantPassadas, MAX_VETORCHAR);
		if (!Mapa->AudiosPassadas)
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		for (i = 0; i < Mapa->QuantPassadas; i++)
			LerLinhaStr(Mapa->AudiosPassadas[i], Arquivo);

		if (!SecaoChecar(":BORDAS", Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("BordaS", &Mapa->Borda.Superior, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("BordaI", &Mapa->Borda.Inferior, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("BordaE", &Mapa->Borda.Esquerda, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("BordaD", &Mapa->Borda.Direita, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("BordaSE", &Mapa->Borda.SuperiorEsquerda, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("BordaSD", &Mapa->Borda.SuperiorDireita, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("BordaID", &Mapa->Borda.InferiorDireita, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("BordaIE", &Mapa->Borda.InferiorEsquerda, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}

		if (!SecaoChecar(":QUADRANTEPADRAO", Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("Colisao", &ColisaoPadrao, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("Mascara", &MascaraPadrao, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("TemSangue", &TemSanguePadrao, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("Passada", &PassadaPadrao, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		Mapa->Estrutura = (TMapaItem**)malloc(Mapa->TamEstruturaY * sizeof(TMapaItem*));
		if (Mapa->Estrutura == NULL)
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		for (i = 0; i < Mapa->TamEstruturaY; i++)
		{
			Mapa->Estrutura[i] = (TMapaItem*)malloc(Mapa->TamEstruturaX * sizeof(TMapaItem));
			if (Mapa->Estrutura[i] == NULL)
			{
				ArquivoFechar(Arquivo);
				return FALSE;
			}
			for (j = 0; j < Mapa->TamEstruturaX; j++)
			{
				Mapa->Estrutura[i][j].AudioPassada = PassadaPadrao;
				Mapa->Estrutura[i][j].BitmapMascara = MascaraPadrao;
				Mapa->Estrutura[i][j].Colisao = ColisaoPadrao;
				Mapa->Estrutura[i][j].TemSangue = TemSanguePadrao;
			}			
		}
		MapaItemAbrir(Mapa, QuadrantesInformados, Arquivo);
		Mapa->MundoAltura = Mapa->TamEstruturaY * Mapa->MascaraAltura;
		Mapa->MundoLargura = Mapa->TamEstruturaX * Mapa->MascaraLargura;
		ArquivoFechar(Arquivo);
		
		return TRUE;		
	}
	else	
		return FALSE;
}

int MapaAudioPassada(TMapa* Mapa, TPonto Ponto)
{
	int x;
	int y;
	
	x = ((int)(Ponto.x - Mapa->PontoVisao.x)) / Mapa->MascaraLargura;
	y = ((int)(Ponto.y - Mapa->PontoVisao.y)) / Mapa->MascaraAltura;
	
	return Mapa->Estrutura[y][x].AudioPassada;
}

void MapaConstruir(TMapa* Mapa, TPonto Escape, TBitmapBuffer* Buffer)
{
	int i;	int j;
	int** MascEstrutura;

	MascEstrutura = IMatrizCriar(Mapa->TamEstruturaY, Mapa->TamEstruturaX);
	for (i = 0; i < Mapa->TamEstruturaY; i++)
		for (j = 0; j < Mapa->TamEstruturaX; j++)
		{
			//Borda superior-esquerda
			if ((i == 0) && (j == 0))
				MascEstrutura[i][j] = Mapa->Borda.SuperiorEsquerda;
			//Borda superuir-direita
			else if ((i == 0) && (j == Mapa->TamEstruturaX - 1))
				MascEstrutura[i][j] = Mapa->Borda.SuperiorDireita;
			//Borda superior
			else if (i == 0)
				MascEstrutura[i][j] = Mapa->Borda.Superior;
			//Borda inferior-esquerda
			else if ((i == Mapa->TamEstruturaY - 1) && (j == 0))
				MascEstrutura[i][j] = Mapa->Borda.InferiorEsquerda;
			//Borda inferior direita
			else if ((i == Mapa->TamEstruturaY - 1) && (j == Mapa->TamEstruturaX - 1))
				MascEstrutura[i][j] = Mapa->Borda.InferiorDireita;
			//Borda inferior
			else if (i == Mapa->TamEstruturaY - 1)
				MascEstrutura[i][j] = Mapa->Borda.Inferior;
			//Borda esquerda
			else if (j == 0)
				MascEstrutura[i][j] = Mapa->Borda.Esquerda;
			//Borda direita
			else if (j == Mapa->TamEstruturaX -1)
				MascEstrutura[i][j] = Mapa->Borda.Direita;
			//Escape
			else if ((j * 32 == (int)Escape.x) && (i * 32 == (int)Escape.y))
				MascEstrutura[i][j] = Mapa->QuadraFinal;
			else
				MascEstrutura[i][j] = Mapa->Estrutura[i][j].BitmapMascara;
		}	
	
	BitmapBufferConstruirMundo(Buffer, MascEstrutura, Mapa->TamEstruturaY, Mapa->TamEstruturaX);
	MatrizDestruir((void***)&MascEstrutura, Mapa->TamEstruturaY);
}

int MapaContarObjInterativos(TMapa* Mapa)
{
	return Mapa->ObjetosColisao + 2 * Mapa->TamEstruturaY + 2 * (Mapa->TamEstruturaX - 2);
}

void MapaDesenhar(TMapa* Mapa, TBitmapBuffer* Buffer)
{
	TelaRegiaoDesenhar(Buffer->Mundo, &Mapa->PontoVisao, TELA_LARGURA, TELA_ALTURA);	
}

void MapaMovimentar(TMapa* Mapa, TPonto* PontoFora)
{
	Mapa->PontoVisao.x += PontoFora->x;
	if (Mapa->PontoVisao.x > Mapa->MundoLargura - Application.ScreenWidth)
		Mapa->PontoVisao.x = Mapa->MundoLargura - Application.ScreenWidth;
	else if (Mapa->PontoVisao.x < 0)
		Mapa->PontoVisao.x = 0;
	
	Mapa->PontoVisao.y += PontoFora->y;
	if (Mapa->PontoVisao.y > Mapa->MundoAltura - Application.ScreenHeight)
		Mapa->PontoVisao.y = Mapa->MundoAltura - Application.ScreenHeight;
	else if (Mapa->PontoVisao.y < 0)
		Mapa->PontoVisao.y = 0;
}

int MapaLimite(TMapa* Mapa, int i, int j)
{
	return ((i == 0) || (j == 0) || (i == Mapa->TamEstruturaY - 1) || (j == Mapa->TamEstruturaX - 1));
}

int MapaItemAbrir(TMapa* Mapa, int Quantidade, FILE* Arquivo)
{
	int i;
	int ColisaoTemp;
	int MascaraTemp;
	int TemSangueTemp;
	int PassadaTemp;
	TPonto Pos;
	int x, y;
	
	for (i = 0; i < Quantidade; i++)
	{
		if (!SecaoChecar(":QUADRANTE", Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadePonto("Posicao", &Pos, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("Colisao", &ColisaoTemp, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("Mascara", &MascaraTemp, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("TemSangue", &TemSangueTemp, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("Passada", &PassadaTemp, Arquivo))
		{
			ArquivoFechar(Arquivo);
			return FALSE;
		}
		x = (int)Pos.x;
		y = (int)Pos.y;
		Mapa->Estrutura[x][y].AudioPassada = PassadaTemp;
		Mapa->Estrutura[x][y].BitmapMascara = MascaraTemp;
		Mapa->Estrutura[x][y].Colisao = ColisaoTemp;
		Mapa->Estrutura[x][y].TemSangue = TemSangueTemp;
		Mapa->ObjetosColisao += ColisaoTemp;
	}
	
	return TRUE;
}