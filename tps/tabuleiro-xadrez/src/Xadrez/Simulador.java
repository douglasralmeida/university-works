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
		int i, j, quantmovimentos, proxmovimento;
		Point novaposicao;
		Point[] movimentospossiveis;
		Random gerador;
		
		gerador = new Random();
		j = 0;
		quantmovimentos = peca.getQtMovimentos();
		movimentospossiveis = new Point[quantmovimentos];
		for (i = 0; i < quantmovimentos; i++) {
			if (T.PodeMovimentar(peca.getMovimento(i))) {
			  movimentospossiveis[j] = peca.getQtMovimentos(i);
			  j++;
			 }
		}
		if (j > 0)
			proxmovimento = gerador.nextInt(j);
		else
			return false;
		;;;;;;
		peca.setProxPosicao(proxmovimento);
		novaposicao = peca.getProxPosicao();		
		return true;
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