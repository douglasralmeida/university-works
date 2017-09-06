package Xadrez;

import java.awt.Point;

public interface Peca {
	Point getMovimento(int i);
	
	Point getPosicao();
	
	Point getProxPosicao();

	int getQtMovimentos();
	
	void setPosicao(Point posicao);
	
	void setProxPosicao(int movimento);
}
