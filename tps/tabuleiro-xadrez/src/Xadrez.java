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
		boolean Podevisitar(int x, int y) {
			return (visitas[x][y] == 0);
		}
		void Visitar(int x, int y) {
			visitas[x][y] = 1;
		}
	}
	/**
	 * Sortea a proxima posicao da peça
	 */	
	private Point Sortearposicao(int limitex, int limitey) {
		Random gerador = new Random();
		int x;
		int y;
		
		x = gerador.nextInt(limitex + 1);
		y = gerador.nextInt(limitey + 1);
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