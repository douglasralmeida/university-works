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

class Simulador {
	interface Peca {
		Point getMovimento(int i);
		Point getPosicao();
		Point getProxPosicao();
		int getQtMovimentos();
		void setPosicao(Point posicao);
		void setProxPosicao(int movimento);
	}
	
	class Cavalo implements Peca {
		public final Point[] movimentos;
		private Point posicao;
		private Point proxposicao;
		
		/**
		 * Construtor do Cavalo
		 */
		public Cavalo() {
			movimentos = new Point[] {
					new Point(1, 2),
					new Point(2, 1),
					new Point(2, -1),
					new Point(1, -2),
					new Point(-1, -2),
					new Point(-2, -1),
					new Point(-2, 1),
					new Point(-1, 2)
			};
			this.posicao = new Point(-1, -1);
			this.proxposicao = new Point(-1, -1);
		}
		
		/**
		 * Obtem um movimento possivel 
		 */
		@Override
		public Point getMovimento(int i) {
			return movimentos[i];
		}

		/**
		 * Obtem a quantidade de movimentos possiveis 
		 */
		@Override
		public int getQtMovimentos() {
			return movimentos.length;
		}

		/**
		 * Obtem a posicao da peça no tabuleiro 
		 */
		@Override
		public Point getPosicao() {
			return posicao;
		}
		
		/**
		 * Obtem a próxima posição da peça para ser movimentada
		 */
		@Override
		public Point getProxPosicao() {
			return proxposicao;
		}

		/**
		 * Altera a posição da peça 
		 */
		@Override
		public void setPosicao(Point posicao) {
			this.posicao = posicao;
		}
		
		/**
		 * Altera a próxima posição da peça
		 * @param movimento: id do movimento possível 
		 */
		@Override
		public void setProxPosicao(int movimento) {
			proxposicao.setLocation(posicao.x + movimentos[movimento].x, posicao.y + movimentos[movimento].y);
		}
	}
	
	class Tabuleiro {
		private int altura;
		private int largura;
		private int numvisitas;
		private int[][] casas;
		
		/**
		 * Construtor do Tabuleiro
		 * @param largurainicial: Largura inicial do tabuleiro
		 * @param alturainicial: Altura inicial do tabuleiro
		 */
		public Tabuleiro(int largurainicial, int alturainicial) {
			numvisitas = 0;			
			casas = new int[largurainicial][alturainicial];
			altura = alturainicial;
			largura = largurainicial;
		}
		
		/**
		 * Obtem a altura do tabuleiro
		 */
		public int getAltura() {
			return altura;
		}
		
		/**
		 * Obtem a largura do tabuleiro
		 */
		public int getLargura() {
			return largura;
		}
		
		/**
		 * Imprime o tabuleiro na tela
		 */
		void imprimir() {
			int i, j;
			
			for (i = getAltura() - 1; i >= 0; i--) {
				for (j = 0; j < getLargura(); j++) {
					if (casas[i][j] < 10)
						System.out.print(' ');
					System.out.print(casas[i][j]);
					System.out.print(' ');
				}
				System.out.print('\n');
			}
		}
		
		/**
		 * Imprime detalhes do tabuleiro na tela
		 */
		void imprmirDetalhes() {
			System.out.println(numvisitas);
		}
		
		/**
		 *  Insere uma peça no tabuleiro na posição indicada
		 *  @param peca: peca que será inserida
		 *  @param posicao: posicao onde será inserida
		 */
		void inserir(Peca peca, Point posicao) {
			casas[posicao.x][posicao.y] = numvisitas+1;
			peca.setPosicao(posicao);
			numvisitas++;
		}
		
		/**
		 * Movimenta uma peca no tabuleiro para a posicao indicada
		 * @param peca: peca que está sendo movimentada
		 */
		void movimentar(Peca peca) {
			casas[peca.getProxPosicao().x][peca.getProxPosicao().y] = numvisitas+1;
			peca.setPosicao(peca.getProxPosicao());
			numvisitas++;
		}
		
		/**
		 * Checa se um casa do tabuleiro pode ser visitada
		 * @param p: posicao da casa
		 */		
		boolean podeMovimentar(Point p) {				
			return ((p.x < getLargura()) &&
					(p.y < getAltura()) &&
					(p.x >= 0) &&
					(p.y >= 0) &&
					(casas[p.x][p.y] == 0));
		}
	}
	
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