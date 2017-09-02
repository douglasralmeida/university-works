#include <math.h>
#include <stdlib.h>
#include "vetor.h"
#include "arquivo.h"
#include "funcoes.h"
#include "audio.h"
#include "graficos.h"
#include "personagem.h"

TPersonagem* PersonagemCriar(void)
{
	TPersonagem* NovoPersonagem;
	
	NovoPersonagem = (TPersonagem*)malloc(sizeof(TPersonagem));
	NovoPersonagem->ID = -1;
	NovoPersonagem->Altura = 0;
	NovoPersonagem->ArquivoPele = NULL;
	NovoPersonagem->Ativo = FALSE;
	NovoPersonagem->DelayParaCaminhar = 0;
	NovoPersonagem->DelayParaProcurar = 0;
	NovoPersonagem->EstaVivo = FALSE;
	NovoPersonagem->Largura = 0;
	NovoPersonagem->MascaraID = -1;
	NovoPersonagem->Nome = NULL;
	NovoPersonagem->PosicaoPernas = 0;
	NovoPersonagem->PosXAnterior = 0;
	NovoPersonagem->PosYAnterior = 0;	
	NovoPersonagem->RecargaProjetil = 0;
	NovoPersonagem->Saude = 3;
	NovoPersonagem->TempoRecarga = 0;
	NovoPersonagem->Trajetoria.Norma = 1.50;
	NovoPersonagem->Trajetoria.Angulo = 90;
	NovoPersonagem->Trajetoria.Sentido = -1;
	NovoPersonagem->Transparencia = 255;
	NovoPersonagem->TransparenciaCont = 6;
	//PersonagemPosicionar(NovoPersonagem, PosicaoInicial);
	
	return NovoPersonagem;
}

void PersonagemDestruir(TPersonagem** PPersonagem)
{
	if ((*PPersonagem)->ArquivoPele != NULL)
		free((*PPersonagem)->ArquivoPele);
	if ((*PPersonagem)->Nome != NULL)
		free((*PPersonagem)->Nome);
	free(*PPersonagem);
	*PPersonagem = NULL;
}

int PersonagemAbrir(TPersonagem* Personagem, char* ArquivoPerson)
{	
	FILE* Arquivo;
	int TempInt;
	char* Caminho;
	
	Caminho = ReceberRecDirCompleto(REC_PERSON, ArquivoPerson);
	Arquivo = fopen(Caminho, "r");
	free(Caminho);
	if (Arquivo != NULL)
	{
		if (SecaoChecar(":ARQUIVOPERSONAGEM", Arquivo) == FALSE)
		{
			fclose(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeInteiro("Versao", &TempInt, Arquivo))
		{
			if (TempInt != 1)
			{
				fclose(Arquivo);
				return FALSE;
			}
		}
		else
		{
			fclose(Arquivo);
			return FALSE;
		}
		
		Personagem->ArquivoPele = CVetorCriar(33);
		if (!Personagem->ArquivoPele)
		{
			fclose(Arquivo);
			return FALSE;
		}
		if (!LerPropriedadeString("ArquivoPele", Personagem->ArquivoPele, Arquivo))
		{
			fclose(Arquivo);
			return FALSE;
		}
		fclose(Arquivo);
		return TRUE;
	}
	else
		return FALSE;
}

void PersonagemAtingir(TPersonagem* Personagem)
{
	Personagem->Saude--;
	Personagem->Transparencia = 0;
	Personagem->TransparenciaCont = 5;
}

void PersonagemAtivar(TPersonagem* Personagem, TAudioBuffer* BufferAudio)
{
	Personagem->Ativo = TRUE;
	if (Personagem->ID != JOGADORID)
		TocarSomVoz(BufferAudio, 0);
}

void PersonagemAtualizar(TPersonagem* Personagem, TColisor* Colisor)
{
	Colisor->Mascaras[Personagem->MascaraID].Vertices[0].x = Personagem->Posicao.PontoInicial.x;
	Colisor->Mascaras[Personagem->MascaraID].Vertices[0].y = Personagem->Posicao.PontoInicial.y;
	Colisor->Mascaras[Personagem->MascaraID].Vertices[1].x = Personagem->Posicao.PontoFinal.x;
	Colisor->Mascaras[Personagem->MascaraID].Vertices[1].y = Personagem->Posicao.PontoInicial.y;
	Colisor->Mascaras[Personagem->MascaraID].Vertices[2].x = Personagem->Posicao.PontoInicial.x;
	Colisor->Mascaras[Personagem->MascaraID].Vertices[2].y = Personagem->Posicao.PontoFinal.y;
	Colisor->Mascaras[Personagem->MascaraID].Vertices[3].x = Personagem->Posicao.PontoFinal.x;
	Colisor->Mascaras[Personagem->MascaraID].Vertices[3].y = Personagem->Posicao.PontoFinal.y;	
}

void PersonagemConfigAngulo(TPersonagem* Personagem, float DirecaoX, float DirecaoY, TPonto* PontoVisao)
{
	float AnguloPersonagem;
	TPonto PersonagemNaJanela;
	PersonagemNaJanela.x = Personagem->Posicao.PontoInicial.x - PontoVisao->x;
	PersonagemNaJanela.y = Personagem->Posicao.PontoInicial.y - PontoVisao->y;
	
	AnguloPersonagem = atan2(DirecaoY - PersonagemNaJanela.y, DirecaoX - PersonagemNaJanela.x) / M_PI * 180;
	if (AnguloPersonagem < 0)
	{
		Personagem->Trajetoria.Angulo = AnguloPersonagem * -1;
		Personagem->Trajetoria.Sentido = 1;
	}
	else
	{
		Personagem->Trajetoria.Angulo = AnguloPersonagem;
		Personagem->Trajetoria.Sentido = -1;	
	}
	PersonagemRotacionar(Personagem);
}

void PersonagemDesenhar(TPersonagem* Personagem, int PersonagemTipo, TBitmapBuffer* Buffer, TPonto* PontoVisao)
{
	float angulo;
	TPonto PontonaJanela;
	ALLEGRO_BITMAP* PernasBitmap;
	ALLEGRO_BITMAP* PersonagemBitmap;
	TPonto PontoTemp;
	
	//Transparencia ao ser atingido
	if (Personagem->TransparenciaCont < 6)
	{
		Personagem->Transparencia += 8;
		if (Personagem->Transparencia >= 255)
		{
			Personagem->Transparencia = 0;
			Personagem->TransparenciaCont--;
			if (Personagem->TransparenciaCont == 0)
			{
				Personagem->Transparencia = 255;
				Personagem->TransparenciaCont = 6;
			}
		}
	}
	
	if (Personagem->EstaVivo)
	{
		//Calcular o angulo
		PontonaJanela.x = Personagem->Posicao.PontoInicial.x - PontoVisao->x;
		PontonaJanela.y = Personagem->Posicao.PontoInicial.y - PontoVisao->y;
		angulo = 90 - (Personagem->Trajetoria.Angulo * Personagem->Trajetoria.Sentido);
		angulo = angulo * M_PI / 180;
		
		//Desenhar as pernas
		PontoTemp.x = Personagem->PosicaoPernas / 10 * 32;
		PontoTemp.y = 0;
		PernasBitmap = al_create_bitmap(32, 32);
		AlvoDesenhoConfig(PernasBitmap);
		TelaRegiaoDesenhar(Buffer->Pernas, &PontoTemp, 32, 32);
		AlvoDesenhoRestaurar();
		BitmapRotativoDesenhar(PernasBitmap, &PontonaJanela, angulo);
		
		//Desenhar o personagem
		PontoTemp.x = 0;
		PontoTemp.y = 0;
		PersonagemBitmap = al_create_bitmap(32, 32);
		AlvoDesenhoConfig(PersonagemBitmap);
		TelaDesenhar(Buffer->Personagens[PersonagemTipo], &PontoTemp);
		//Desenhar a arma
		PontoTemp.x = -17;
		TelaDesenhar(Buffer->Armas[0], &PontoTemp);
		
		AlvoDesenhoRestaurar();
		BitmapRotativoTransparenteDesenhar(PersonagemBitmap, &PontonaJanela, Personagem->Transparencia, angulo);
		al_destroy_bitmap(PernasBitmap);
		al_destroy_bitmap(PersonagemBitmap);
	}
}

void PersonagemMatar(TPersonagem* Personagem)
{
	Personagem->Ativo = FALSE;
	Personagem->EstaVivo = FALSE;
}

int PersonagemMovimentar(TPersonagem* Personagem, ALLEGRO_KEYBOARD_STATE* AlEstadoTecla)
{
	int HouveMovimento = TRUE;
	TVetor Velocidade;
	
	Velocidade.Norma = Personagem->Trajetoria.Norma;
	Velocidade.Angulo = Personagem->Trajetoria.Angulo;
	Velocidade.Sentido = Personagem->Trajetoria.Sentido;	
	if ((al_key_down(AlEstadoTecla, ALLEGRO_KEY_DOWN)) || (al_key_down(AlEstadoTecla, ALLEGRO_KEY_S))) //PRA TRAS
	{
		VetorInverter(&Velocidade);
	}
	else if ((al_key_down(AlEstadoTecla, ALLEGRO_KEY_UP)) || (al_key_down(AlEstadoTecla, ALLEGRO_KEY_W))) //PRA FRENTE
	{
		
	}
	else if ((al_key_down(AlEstadoTecla, ALLEGRO_KEY_LEFT)) || (al_key_down(AlEstadoTecla, ALLEGRO_KEY_A)))//ESQUERDA DO PERSONAGEM
	{
		VetorGirar90AH(&Velocidade);
	}
	else if ((al_key_down(AlEstadoTecla, ALLEGRO_KEY_RIGHT)) || (al_key_down(AlEstadoTecla, ALLEGRO_KEY_D)))//DIREITA DO PERSONAGEM
	{
		VetorGirar90H(&Velocidade);
	}
	else
		HouveMovimento = FALSE;
	if (HouveMovimento)
	{
		Personagem->PosicaoPernas++;
		if (Personagem->PosicaoPernas > 79)
			Personagem->PosicaoPernas = 0;
		PosicaoMovimentar(&Personagem->Posicao.PontoInicial, &Velocidade);
		PersonagemPosicionar(Personagem, Personagem->Posicao.PontoInicial);
		//ChecarLimites(&Personagem->Posicao);
	}
	return HouveMovimento;
}

void PersonagemRotacionar(TPersonagem* Personagem)
{
	float x = 17;
	float y = 0;
	float rad_angulo;

	rad_angulo = AnguloParaRadiano(Personagem->Trajetoria.Angulo * Personagem->Trajetoria.Sentido);
	Personagem->PontoFrontal.x = x * cos(rad_angulo) - y * sin(rad_angulo) + Personagem->Posicao.PontoInicial.x + 16;
	Personagem->PontoFrontal.y = x * sin(rad_angulo) - y * cos(rad_angulo) + Personagem->Posicao.PontoInicial.y + 16;
}

void PersonagemPosicionar(TPersonagem* Personagem, TPonto NovaPosicao)
{	
	Personagem->Posicao.PontoInicial.x = NovaPosicao.x;
	Personagem->Posicao.PontoInicial.y = NovaPosicao.y;
	Personagem->Posicao.PontoFinal.x = NovaPosicao.x + Personagem->Largura;
	Personagem->Posicao.PontoFinal.y = NovaPosicao.y + Personagem->Altura;
	
	PersonagemRotacionar(Personagem);
}

int PersonagemProcurarJogador(TPersonagem* Personagem, TQuadra* JogadorQuadra, TPonto* PontoVisao)
{
	int i;
	int j;
	TQuadra QuadraProcura;
	const int AlturaQuadra = 32;
	const int LarguraQuadra = 32;
	TPonto JogadorNaJanela;
	
	if (Personagem->DelayParaProcurar < 60)
	{
		//um pouco de lerdeza....
		Personagem->DelayParaProcurar++;
	}
	else
	{
		for (i = 0; i < TELA_LARGURA; i = i + AlturaQuadra)
			for (j = 0; j < TELA_ALTURA; j = j + LarguraQuadra)
			{
				QuadraProcura.PontoInicial.x = i;
				QuadraProcura.PontoInicial.y = j;
				QuadraProcura.PontoFinal.x = i + LarguraQuadra;
				QuadraProcura.PontoFinal.y = i + AlturaQuadra;
				
				if (ExisteSobreposicaoQuadras(&QuadraProcura, JogadorQuadra))
				{
					JogadorNaJanela.x = JogadorQuadra->PontoInicial.x - PontoVisao->x;
					JogadorNaJanela.y = JogadorQuadra->PontoInicial.y - PontoVisao->y;	
					PersonagemConfigAngulo(Personagem, (float)JogadorNaJanela.x, (float)JogadorNaJanela.y, PontoVisao);
					return TRUE;
				}
			}
	}
	
	return FALSE;
}

void PersonagemRecarregarProjetil(TPersonagem* Personagem)
{
	if (Personagem->RecargaProjetil < Personagem->TempoRecarga)
		Personagem->RecargaProjetil++;
}

int PersonagemVisivel(TPersonagem* Personagem, TPonto* PontoVisao)
{
	return ((Personagem->Posicao.PontoFinal.x > PontoVisao->x + 4) &&
			(Personagem->Posicao.PontoFinal.y > PontoVisao->y + 4) &&
			(Personagem->Posicao.PontoInicial.x < PontoVisao->x + TELA_LARGURA - 4) &&
			(Personagem->Posicao.PontoInicial.y < PontoVisao->y + TELA_ALTURA - 4));
}

TPersonagem* PersonagemPorMascara(TPersonagens* Personagens, unsigned int MascaraID)
{
	int i;
	
	if (Personagens->Jogador != NULL)
		if (Personagens->Jogador->MascaraID == MascaraID)
			return Personagens->Jogador;
	if (Personagens->Chefao != NULL)
		if (Personagens->Chefao->MascaraID == MascaraID)
			return Personagens->Chefao;
	if (Personagens->Inimigos != NULL)
	{
		for (i = 0; i < Personagens->QuantInimigos; i++)
			if (Personagens->Inimigos[i].MascaraID == MascaraID)
				return &Personagens->Inimigos[i];
	}
	
	return NULL;
}