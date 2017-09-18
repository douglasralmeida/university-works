/**
 *	Simulador do tabuleiro de xadrez
 *
 *	@author Douglas Rodrigues 
 */
package Xadrez;

import java.awt.Point;
import java.time.Duration;
import java.time.Instant;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class Simulador {
	private Tabuleiro tab;
	private Instant tempoInicial;
	private Duration tempoTotal;
	
	/**
	 * Construtor do simulador
	 */
	public Simulador() {
		tempoInicial = Instant.now();
		tab = new Tabuleiro(8, 8);
	}
	
	/**
	 * Escolhe um movimento aleatorio daqueles possiveis
	 * @peca: Peça que será movimentada
	 */
	private boolean escolheProxMovimento(Peca peca) {
		int i, quantmovimentos, proxmovimento;		
		List<Integer> movimentospossiveis;

		quantmovimentos = peca.getQtMovimentos();
		movimentospossiveis = new ArrayList<>();
		for (i = 0; i < quantmovimentos; i++) {
			if (tab.podeMovimentar(new Point(peca.getMovimento(i).x + peca.getPosicao().x, peca.getMovimento(i).y + peca.getPosicao().y)))
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
	 * Imprime o tabuleiro e os detalhes da simulacao na tela
	 */
	private void imprime(){
		tab.imprimir();
		tab.imprmirDetalhes();
		System.out.println(tempoTotal.toMillis() + " ms");
	}
	
	/**
	 * Sortea a posicao inicial da peça
	 */	
	private Point sortearInicio() {
		Random gerador = new Random();
		int x;
		int y;
		
		x = gerador.nextInt(tab.getLargura());
		y = gerador.nextInt(tab.getAltura());
		return new Point(x, y);
	}	
	
	/**
	 * Realiza uma simulacao com movimentos aleatorios
	 */
	private void simula() {
		Point casaInicial;
		Peca pecaAtual;		
		
		pecaAtual = new Cavalo();
		casaInicial = sortearInicio();
		tab.inserir(pecaAtual, casaInicial);
		while (escolheProxMovimento(pecaAtual)) {
			tab.movimentar(pecaAtual);
		}
		tempoTotal = Duration.between(tempoInicial, Instant.now());		
	}
	
	/**
	 * Funcao Main
	 */
	public static void main(String[] args) {
		Simulador s;
		
		s = new Simulador();
		s.simula();		
		s.imprime();
	}
}