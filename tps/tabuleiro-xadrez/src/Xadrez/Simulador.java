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

/**
 * Simulador de movimentos das peças do xadrez 
 */
class Simulador {
	/**
	 * Interface para uma peça qualquer do tabuleiro 
	 */
	interface Peca {
		Point getMovimento(int i);
		Point getPosicao();
		int getQtMovimentos();
		void setPosicao(Point posicao);
	}
	
	/**
	 * Representa a peça 'cavalo' do xadrez 
	 */
	class Cavalo implements Peca {
		private Point[] movimentos;
		private Point posicao;
		
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
		 * Altera a posição da peça
		 * @param posicao: Nova posição da peça
		 */
		@Override
		public void setPosicao(Point posicao) {
			this.posicao = posicao;
		}
	}
	
	/**
	 * Representa o tabuleiro do xadrez 
	 */
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
		 * Testa se a posicao ja foi ocupada
		 * @param p: Posição a ser testada
		 */
		public boolean ehPosicaoOcupavel(Point p) {
			return (casas[p.x][p.y] == 0);
		}
		
		/**
		 * Verifica se o tabuleiro foi completamente percorido
		 */
		public boolean foiPercorrido() {
			return (numvisitas == getAltura() * getLargura());
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
			casas[posicao.x][posicao.y] = ++numvisitas;
			peca.setPosicao(posicao);
		}
		
		/**
		 * Movimenta uma peca no tabuleiro para a posicao indicada
		 * @param peca: peca que está sendo movimentada
		 * @param movimento: ID válido do movimento a ser utilizado
		 */
		void movimentar(Peca peca, int movimento) {
			casas[peca.getPosicao().x + peca.getMovimento(movimento).x][peca.getPosicao().y + peca.getMovimento(movimento).y] = ++numvisitas;
			peca.setPosicao(new Point(peca.getPosicao().x + peca.getMovimento(movimento).x, peca.getPosicao().y + peca.getMovimento(movimento).y));
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
					(ehPosicaoOcupavel(p)));
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
	private int escolheProxMovAleatorio(Peca peca) {
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
			return proxmovimento;
		}
		else
			return -1;
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
	 * Realiza um passeio completo com a peça pelo tabuleiro
	 * @param peca: peca que está sendo movimentada
	 */
	boolean passeioCompleto(Peca peca) {
		int i = 0;
		boolean encontroucaminho = false;
		Point proxmovimento, proxposicao;
		
		do {
			proxmovimento = peca.getMovimento(i);
			proxposicao = new Point(proxmovimento.x + peca.getPosicao().x, proxmovimento.y + peca.getPosicao().y);
			if (tab.podeMovimentar(proxposicao)) {
				tab.movimentar(peca, i);
				if (!tab.foiPercorrido()) {
					encontroucaminho = passeioCompleto(peca);
					if (!encontroucaminho) {
						tab.casas[proxposicao.x][proxposicao.y] = 0;
						tab.numvisitas--;
					}
				}
				else
					encontroucaminho = true;
			}
			i++;
		} while (!(encontroucaminho || i == peca.getQtMovimentos()));
		return encontroucaminho;
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
		Point casainicial;
		Peca pecaatual;
		int proxmovimento;
		
		pecaatual = new Cavalo();
		casainicial = sortearInicio();
		tab.inserir(pecaatual, casainicial);
		do {
			proxmovimento = escolheProxMovAleatorio(pecaatual);
			if (proxmovimento >= 0)
				tab.movimentar(pecaatual, proxmovimento);
		} while (proxmovimento >= 0);
		tempoTotal = Duration.between(tempoInicial, Instant.now());		
	}
	
	/**
	 * Soluciona o problema de passar por todas as casas uma única vez
	 */
	private void soluciona() {
		Point casainicial;
		Peca pecaatual;
		
		pecaatual = new Cavalo();
		casainicial = new Point(0, 0);
		tab.inserir(pecaatual, casainicial);
		passeioCompleto(pecaatual);
		tempoTotal = Duration.between(tempoInicial, Instant.now());
	}
	
	/**
	 * Funcao Main
	 */
	public static void main(String[] args) {
		Simulador simaleatorio;
		Simulador desafio;
		
		simaleatorio = new Simulador();
		simaleatorio.simula();
		simaleatorio.imprime();
		
		desafio = new Simulador();
		desafio.soluciona();
		desafio.imprime();
	}
}