/**
 *	TP1 de PM
 *	Tabuleiro de Xadrez
 *
 *	@author Douglas Rodrigues 
 */
package Xadrez;

import java.awt.Point;
import java.util.Random;

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
		largura = largurainicial;
		altura = alturainicial;
	}
	
	public int getAltura() {
		return altura;
	}
	
	public int getLargura() {
		return largura;
	}
	
	public void setAltura(int altura) {
		this.altura = altura;
	}
	
	public void setLargura(int largura) {
		this.largura = largura;
	}
	
	/**
	 * Imprime o tabuleiro
	 */
	void Imprimir() {
		int i, j;
		
		for (i = getAltura() - 1; i >= 0; i--) {
			for (j = 0; j < getLargura(); j++) {
				if (casas[i][j] < 10)
					System.out.print(0);
				System.out.print(casas[i][j]);
				System.out.print(' ');
			}
			System.out.print('\n');
		}
	}
	
	void ImprmirDetalhes() {
		System.out.println(numvisitas);
	}
	
	/**
	 * Checa se um casa pode ser visitada
	 * @param casa: posicao da casa
	 */		
	boolean PodeVisitar(Point casa) {
		return ((casa.x < getLargura()) &&
				(casa.y < getAltura()) &&
				(casa.x >= 0) &&
				(casa.y >= 0) &&
				(casas[casa.x][casa.y] == 0));
	}
	
	void Visita(Point casa) {
		casas[casa.x][casa.y] = numvisitas+1;
		numvisitas++;
	}
}