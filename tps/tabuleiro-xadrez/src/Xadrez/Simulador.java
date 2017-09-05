package Xadrez;

import java.awt.Point;
import java.util.Random;

public class Simulador {
	private Tabuleiro T;
	
	public Simulador() {
		T = new Tabuleiro(8, 8);
	}
	/**
	 * Sortea a posicao inicial da peça
	 */	
	private Point SortearInicio() {
		Random gerador = new Random();
		int x;
		int y;
		
		x = gerador.nextInt(T.getLargura());
		y = gerador.nextInt(T.getAltura());
		return new Point(x, y);
	}
	private boolean EscolheProxMovimento(Peca peca) {
		int movimentospossiveis;
		int proxmovimento;
		Point novaposicao;
		Random gerador;
		/* TODO */
		gerador = new Random();
		movimentospossiveis = peca.getQtMovimentos();
		proxmovimento = gerador.nextInt(movimentospossiveis);
		peca.setProxPosicao(proxmovimento);
		novaposicao = peca.getProxPosicao();
		
		return false;
	}
	/**
	 * Funcao Main
	 * @param args: Argumentos do aplicativo
	 */
	private void Simular() {
		Peca pecaatual;
		Point casainicial;
		int x = 1024;
		
		pecaatual = new Cavalo();
		casainicial = SortearInicio();
		T.Inserir(pecaatual, casainicial);
		while (x > 0) {
			if (T.PodeMovimentar(pecaatual)) {
				T.Movimentar(pecaatual);
			}
			x--;
		}
		T.Imprimir();
		T.ImprmirDetalhes();
	}
	
	public static void main(String[] args) {
		Simulador S;
		
		S = new Simulador();
		S.Simular();		
		System.out.println("<tempo_gasto>");
	}
}