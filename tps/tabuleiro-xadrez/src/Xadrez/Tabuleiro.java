/**
 *	Tabuleiro do Xadrez
 *
 *	@author Douglas Rodrigues 
 */
package Xadrez;

import java.awt.Point;

public class Tabuleiro {
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