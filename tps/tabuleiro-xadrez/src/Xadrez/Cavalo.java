package Xadrez;

import java.awt.Point;

public class Cavalo implements Peca {
	public final Point[] movimentos;
	private Point posicao;
	private Point proxposicao;
	
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

	@Override
	public int getQtMovimentos() {
		return movimentos.length;
	}
	
	@Override
	public Point getPosicao() {
		return posicao;
	}
	
	@Override
	public Point getProxPosicao() {
		return proxposicao;
	}

	@Override
	public void setPosicao(Point posicao) {
		this.posicao = posicao;
	}
	
	@Override
	public void setProxPosicao(int movimento) {
		proxposicao.setLocation(posicao.x + movimentos[movimento].x, posicao.y + movimentos[movimento].y);
	}
}