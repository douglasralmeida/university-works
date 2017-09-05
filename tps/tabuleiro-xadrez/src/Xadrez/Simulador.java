package Xadrez;

import java.awt.Point;
import java.util.Random;

public class Simulador {
	private Tabuleiro T;
	
	public Simulador() {
		T = new Tabuleiro(8, 8);
	}
	/**
	 * Sortea a proxima posicao da peça
	 */		
	private Point SortearProximaCasa(Point casaatual) {
		Random gerador = new Random();
		int x = 0;
		int y = 0;
		int p;
		
		p = gerador.nextInt(8);
		switch (p) {
		case 0:
			x = casaatual.x + 1;
			y = casaatual.y + 2;
			break;
		case 1:
			x = casaatual.x + 2;
			y = casaatual.y + 1;			
			break;
		case 2:
			x = casaatual.x + 2;
			y = casaatual.y - 1;
			break;
		case 3:
			x = casaatual.x + 1;
			y = casaatual.y - 2;
			break;
		case 4:
			x = casaatual.x - 1;
			y = casaatual.y - 2;
			break;
		case 5:
			x = casaatual.x - 2;
			y = casaatual.y - 1;
			break;
		case 6:
			x = casaatual.x - 2;
			y = casaatual.y + 1;
			break;
		case 7:
			x = casaatual.x - 1;
			y = casaatual.y + 2;
			break;			
		}
		return new Point(x, y);
	}
	/**
	 * Sortea a posicao inicial da peça
	 */	
	private Point SortearInicio() {
		Random gerador = new Random();
		int x;
		int y;
		
		x = gerador.nextInt(T.getLargura());
		y = gerador.nextInt(T.getAltura());
		return new Point(x, y);
	}
	/**
	 * Funcao Main
	 * @param args: Argumentos do aplicativo
	 */
	private void Simular() {
		Point CasaAtual;
		Point ProximaCasa;
		int x = 256;
		
		CasaAtual = SortearInicio();
		if (T.PodeVisitar(CasaAtual)){
			T.Visita(CasaAtual);				
		}
		while (x > 0) {
			ProximaCasa = SortearProximaCasa(CasaAtual);
			if (T.PodeVisitar(ProximaCasa)) {
				T.Visita(ProximaCasa);
				CasaAtual = ProximaCasa;
			}
			x--;
		}
		T.Imprimir();
		T.ImprmirDetalhes();
	}
	
	public static void main(String[] args) {
		Simulador S;
		
		S = new Simulador();
		S.Simular();		
		System.out.println("<tempo_gasto>");
	}
}