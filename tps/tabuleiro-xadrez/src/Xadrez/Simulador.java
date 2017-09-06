package Xadrez;

import java.awt.Point;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class Simulador {
	private Tabuleiro tab;
	
	/**
	 * Construtor do simulador
	 */
	public Simulador() {
		tab = new Tabuleiro(8, 8);
	}
	/**
	 * Sortea a posicao inicial da peça
	 */	
	private Point SortearInicio() {
		Random gerador = new Random();
		int x;
		int y;
		
		x = gerador.nextInt(tab.getLargura());
		y = gerador.nextInt(tab.getAltura());
		return new Point(x, y);
	}
	
	/**
	 * Escolhe um movimento aleatorio daqueles possiveis
	 */
	private boolean EscolheProxMovimento(Peca peca) {
		int i, quantmovimentos, proxmovimento;		
		List<Integer> movimentospossiveis;

		quantmovimentos = peca.getQtMovimentos();
		movimentospossiveis = new ArrayList<>();
		for (i = 0; i < quantmovimentos; i++) {
			if (tab.PodeMovimentar(new Point(peca.getMovimento(i).x + peca.getPosicao().x, peca.getMovimento(i).y + peca.getPosicao().y)))
				movimentospossiveis.add(i);
		}
		if (movimentospossiveis.size() > 0) {
			Collections.shuffle(movimentospossiveis);
			proxmovimento = movimentospossiveis.get(0);
			peca.setProxPosicao(proxmovimento);
			return true;
		}
		else
			return false;
	}
	
	/**
	 * Realiza uma simulacao de movimentos aleatorios
	 */
	private void Simular() {
		Peca pecaatual;
		Point casainicial;
		
		pecaatual = new Cavalo();
		casainicial = SortearInicio();
		tab.Inserir(pecaatual, casainicial);
		while (EscolheProxMovimento(pecaatual)) {
			tab.Movimentar(pecaatual);
		}
		tab.Imprimir();
		tab.ImprmirDetalhes();
	}
	
	public static void main(String[] args) {
		Simulador S;
		
		S = new Simulador();
		S.Simular();		
		System.out.println("<tempo_gasto>");
	}
}