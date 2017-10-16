/**
 *	Maquina de Venda de Bilhetes
 *
 *	@version 1.0	
 *	@author Douglas Rodrigues de Almeida
 */
package Aplicativo;

import java.io.Console;

class Veiculo {
	String matricula;
	int capacidade;
}

enum TipoTrajeto {
	ttAero,
	ttRodoviario,
	ttFerroviario
}

class Trajeto {
	String cidadea;
	String cidadeb;
	float preco;
	String partidaA[];
	int quantPartidaA;
	String partidaB[];
	int quantPartidaB;
	TipoTrajeto tipo;
	Veiculo veiculo;
	public Trajeto() {
		partidaA = new String[256];
		partidaB = new String[256];
	}
	public Trajeto(String cidadeA, String cidadeB) {
		this();
		
		cidadea = cidadeA;
		cidadeb = cidadeB;
	}
	
	public void adicionarHorarios(boolean cidadeA, String[] horarios) {
		int i = 0;
		int j;
		String[] partida;
		
		if (cidadeA) {
			partida = partidaA;
			quantPartidaA += horarios.length;
		}
		else {
			partida = partidaB;
			quantPartidaB += horarios.length;
		}
		
		for (j = 0; j < horarios.length; j++) {
			partida[i] = horarios[j];
			i++;
		}
	}
}

class Bilhete {
	String nomePassageiro;
}

class Maquina {
	Trajeto trajeto;
	Bilhete bilhetes[];
	public void iniciarVenda() {
		int i, quantidade;
		String escolha = null;
		char opcao;
		Boolean destinoA;
		String[] horarios;
		
		if (System.console() != null) {	
			System.out.printf("VENDA\n======\nDestinos: A - %s | B - %s\n", trajeto.cidadea, trajeto.cidadeb);
			escolha = System.console().readLine("Escolha o destino (A ou B ou S para sair): ");
			opcao = escolha.charAt(0);
			if (opcao == 'A' || opcao == 'a')
				destinoA = true;
			else if (opcao == 'b' || opcao == 'b')
				destinoA = false;
			else {
				System.out.println("Venda cancelada.");
				return;
			}
			if (destinoA) {
				horarios = trajeto.partidaA;
				quantidade = trajeto.quantPartidaA;
			}
			else {
				horarios = trajeto.partidaB;
				quantidade = trajeto.quantPartidaB;
			}
			System.out.print("Horários: ");
			for (i = 0; i < quantidade; i++)
				System.out.printf("%s ", horarios[i]);
			
			escolha = System.console().readLine("\nDigite um horario valido: ");
			for (i = 0; i < quantidade; i++)
				System.out.printf("%s ", horarios[i]);
			
			System.out.printf("\nPreço da passagem: %.2f\n", trajeto.preco);
			escolha = System.console().readLine("\nConfirme a compra (S ou N): ");
			opcao = escolha.charAt(0);
			if (opcao == 'S' || opcao == 's') {
				System.out.println("Venda concluída.");	
			}
			else {
				System.out.println("Venda cancelada.");
			}
		}
		
	}
}
/**
 * Classe principal do aplicativo
 */
public class Principal {

	static Maquina CriarBHZBRA() {
		Maquina maquina;
		Trajeto trajeto;
		String[] horariosA = {"7:45", "10:00", "15:00", "17:45", "21:00"};
		String[] horariosB = {"7:30", "10:45", "13:00", "14:45", "21:15", "22:00"};
		
		trajeto = new Trajeto("Belo Horizonte", "Brasilia");
		trajeto.adicionarHorarios(true, horariosA);
		trajeto.adicionarHorarios(false, horariosB);
		trajeto.preco = (float) 250;
		maquina = new Maquina();
		maquina.trajeto = trajeto;
		
		return maquina;
	}
	
	/**
	 * Funcao Main
	 * @param args
	 */
	public static void main(String[] args) {
		Maquina maquina_OnibusBHZBRA = CriarBHZBRA();
		maquina_OnibusBHZBRA.iniciarVenda();
		
		
	}
}
