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
	
	private void Imprime(){
		tab.Imprimir();
		tab.ImprmirDetalhes();
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
	 * Realiza uma simulacao de movimentos aleatorios
	 */
	private void Simula() {
		Peca pecaatual;
		Point casainicial;
		
		pecaatual = new Cavalo();
		casainicial = SortearInicio();
		tab.Inserir(pecaatual, casainicial);
		while (EscolheProxMovimento(pecaatual)) {
			tab.Movimentar(pecaatual);
		}
	}
	
	/**
	 * Funcao Main
	 */
	public static void main(String[] args) {
		Simulador S;
		Instant tempoInicial;
		Duration tempoTotal;
		
		tempoInicial = Instant.now();	
		S = new Simulador();
		S.Simula();
		tempoTotal = Duration.between(tempoInicial, Instant.now());
		S.Imprime();
		System.out.println(tempoTotal);
	}
}