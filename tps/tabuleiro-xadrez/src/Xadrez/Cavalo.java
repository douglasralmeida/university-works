/**
 *	Peça Cavalo do tabuleiro do xadrez
 *
 *	@author Douglas Rodrigues 
 */
package Xadrez;

import java.awt.Point;

public class Cavalo implements Peca {
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