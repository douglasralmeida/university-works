import java.awt.Point;
import java.util.Random;

/**
 *	TP1 de PM
 *	Tabuleiro de Xadrez
 *	@author Douglas Rodrigues 
 */

public class Xadrez {
	public class TTabuleiro {
		private int altura;
		private int largura;
		private byte[][] visitas;
		Point posicaoatual;
		/**
		 * Construtor do Tabuleiro
		 * @param largurainicial: Largura inicial do tabuleiro
		 * @param alturainicial: Altura inicial do tabuleiro
		 */
		public TTabuleiro(int largurainicial, int alturainicial) {
			altura = alturainicial;
			largura = largurainicial;
			
			visitas = new byte[altura][largura];
		}
		/**
		 * Checa se um casa pode ser visitada
		 * @param x: posição x
		 * @param y: posição y
		 */
		boolean PodeVisitar(Point casa) {
			return (visitas[casa.x][casa.y] == 0);
		}
		void Visitar(Point casa, byte jogada) {
			visitas[casa.x][casa.y] = jogada;
		}
	}
	Point SortearProximaCasa(Point casaatual) {
		Random gerador = new Random();
		int x = 0;
		int y = 0;
		int p;
		
		p = gerador.nextInt(4);
		switch (p) {
		case 0:
			
			break;
		case 1:
			
			break;
		case 2:
			
			break;
			
		case 3:
			
			break;
		}
		
		return new Point(x, y);
	}
	/**
	 * Sortea a proxima posicao da peça
	 */	
	private Point SortearInicio(int limitex, int limitey) {
		Random gerador = new Random();
		int x;
		int y;
		
		x = gerador.nextInt(limitex);
		y = gerador.nextInt(limitey);
		return new Point(x, y);
	}
	/**
	 * Funcao Main
	 * @param args: Argumentos do aplicativo
	 */	
	public static void main(String[] args) {
		System.out.println("<matriz_representativa>");
		System.out.println("<casas_visitadas>");
		System.out.println("<tempo_gasto>");
	}
}