package Xadrez;

import java.awt.Point;

public interface Peca {
	int getQtMovimentos();
		
	Point getPosicao();
	
	Point getProxPosicao();

	void setPosicao(Point posicao);
	
	void setProxPosicao(int movimento);
}
