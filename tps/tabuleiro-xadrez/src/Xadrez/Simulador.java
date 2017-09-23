/**
 *	Simulador do tabuleiro de xadrez
 *
 *	@version 1.0	
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
 * Simulador de movimentos das pecas do xadrez 
 */
class Simulador {
	/**
	 * Interface para uma peca qualquer do tabuleiro 
	 */
	interface Peca {
		Point getMovimento(int i);
		Point getPosicao();
		int getQtMovimentos();
		void setPosicao(Point posicao);
	}
	
	/**
	 * Representa a peca 'cavalo' do xadrez 
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
		 * @param i ID do movimento
		 * @return  um ponto (x,y) que representa a translacao do movimento
		 */
		@Override
		public Point getMovimento(int i) {
			return movimentos[i];
		}

		/**
		 * Obtem a quantidade de movimentos possiveis do cavlo
		 * @return a quantidade de movimentos do cavalo 
		 */
		@Override
		public int getQtMovimentos() {
			return movimentos.length;
		}

		/**
		 * Obtem a posicao do cavalo no tabuleiro
		 * @return um ponto (x,y) que representa a posicao do cavalo
		 */
		@Override
		public Point getPosicao() {
			return posicao;
		}
		
		/**
		 * Altera a posicao do cavalo
		 * @param posicao ponto (x,y) que representa a nova posicao do cavalo
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
		 * @param largurainicial largura inicial do tabuleiro
		 * @param alturainicial  altura inicial do tabuleiro
		 */
		public Tabuleiro(int largurainicial, int alturainicial) {
			numvisitas = 0;			
			casas = new int[largurainicial][alturainicial];
			altura = alturainicial;
			largura = largurainicial;
		}
		
		/**
		 * Testa se a posicao ja foi ocupada
		 * @param   p ponto (x,y) que representa a posicao do tabuleiro a ser testada
		 * @return  valor booleano indicando se a posicao ja foi ocupada
		 */
		public boolean ehPosicaoOcupavel(Point p) {
			return (casas[p.x][p.y] == 0);
		}
		
		/**
		 * Verifica se o tabuleiro foi completamente percorrido
		 * @return valor booleano indicando se o tabuleiro ja foi percorrido
		 */
		public boolean foiPercorrido() {
			return (numvisitas == (getAltura() * getLargura()));
		}
		
		/**
		 * Obtem a altura do tabuleiro
		 * @return inteiro indicando a altura do tabuleiro
		 */
		public int getAltura() {
			return altura;
		}
		
		/**
		 * Obtem a largura do tabuleiro
		 * @return inteiro indicando a largura do tabuleiro
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
		 *  Insere uma peca no tabuleiro na posicao indicada
		 *  @param peca    peca que sera inserida
		 *  @param posicao ponto (x,y) indicando a posicao onde sera inserida a peca
		 */
		void inserir(Peca peca, Point posicao) {
			casas[posicao.x][posicao.y] = ++numvisitas;
			peca.setPosicao(posicao);
		}
		
		/**
		 * Movimenta uma peca no tabuleiro para a posicao indicada
		 * @param peca      peca que esta sendo movimentada
		 * @param movimento ID (>=0) valido do movimento a ser utilizado
		 */
		void movimentar(Peca peca, int movimento) {
			casas[peca.getPosicao().x + peca.getMovimento(movimento).x][peca.getPosicao().y + peca.getMovimento(movimento).y] = ++numvisitas;
			peca.setPosicao(new Point(peca.getPosicao().x + peca.getMovimento(movimento).x, peca.getPosicao().y + peca.getMovimento(movimento).y));
		}
		
		/**
		 * Checa se um posicao do tabuleiro pode ser visitada
		 * @peca peca a ser testada
		 * @movimento id do movimento
		 * @return  valor booleando indicando se a posicao pode ser visitada
		 */
		boolean podeMovimentar(Peca peca, int movimento) {
			Point translacao = peca.getMovimento(movimento);
			Point p = new Point(peca.getPosicao().x + translacao.x, peca.getPosicao().y + translacao.y);
			
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
	 * Escolhe um movimento aleatoriamente daqueles possiveis de uma peca do tabuleiro
	 * @peca   peca que sera movimentada
	 * @return ID (>=0) do movimento escolhido
	 */
	private int escolheProxMovAleatorio(Peca peca) {
		int i, quantmovimentos, proxmovimento;		
		List<Integer> movimentospossiveis;

		quantmovimentos = peca.getQtMovimentos();
		movimentospossiveis = new ArrayList<>();
		for (i = 0; i < quantmovimentos; i++) {
			if (tab.podeMovimentar(peca, i))
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
	 * Realiza um passeio completo com a peca pelo tabuleiro usando backtracking
	 * <p>
	 * Um passeio completo passa por todas as casas do tabuleiro somente uma unica vez.
	 * @param peca peca que esta sendo movimentada
	 * @return     valor booleando indicando que o passeio foi completado
	 */
	boolean passear(Peca peca) {
		int i = 0; //seletor de movimentos
		boolean encontroucaminho = false;
		Point posicaoatual;
		
		posicaoatual = peca.getPosicao();
		do {
			if (tab.podeMovimentar(peca, i)) {
				tab.movimentar(peca, i);
				if (!tab.foiPercorrido()) {
					encontroucaminho = passear(peca);
					if (!encontroucaminho) {
						tab.casas[peca.getPosicao().x][peca.getPosicao().y] = 0; //backtracking
						peca.setPosicao(posicaoatual);
						tab.numvisitas--;
					}
				}
				else
					return true;
			}
			i++;
		} while (!encontroucaminho && i < peca.getQtMovimentos());
		return encontroucaminho;
	}

	/**
	 * Sortea aleatoriamente a posicao inicial para uma peca
	 * @return ponto (x,y) indicando a posicao escolhida
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
	 * Realiza uma simulacao com movimentos aleatorios usando uma peca
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
	 * Soluciona o problema de passar por todas as casas do tabuleiro uma uma unica vez
	 */
	private void solucionaDesafio() {
		Point casainicial;
		Peca pecaatual;
		
		pecaatual = new Cavalo();
		casainicial = new Point(0, 0);
		tab.inserir(pecaatual, casainicial);
		passear(pecaatual);
		tempoTotal = Duration.between(tempoInicial, Instant.now());
	}
	
	/**
	 * Funcao Main
	 */
	public static void main(String[] args) {
		Simulador s;
				
		s = new Simulador();
		s.solucionaDesafio();
		//s.simula();
		s.imprime();
	}
}