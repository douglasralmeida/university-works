/**
 *	Maquina de Venda de Bilhetes
 *
 *	@version 1.0	
 *	@author Douglas Rodrigues de Almeida
 */
package Aplicativo;

import java.io.Console;

/**
 * Classe principal do aplicativo
 */
class Principal {
	/**
	 * Veiculo de transporte de passageiros
	 */	
	class Veiculo {
		/**
		 *  Placa do veiculo automotivo, ou matricula do avião ou matrículo da locomotiva
		 */		
		private String idVeiculo;
		/**
		 *  Capacidade de passageiros do veiculo
		 */
		private int capacidade;
		/**
		 * @param idVeiculo
		 * @param capacidade
		 */
		public Veiculo() {		
			
		}
		public Veiculo(String idVeiculo, int capacidade) {
			this();
			this.idVeiculo = idVeiculo;
			this.capacidade = capacidade;
		}
			
	};
	
	public class Bilhete {
		/**
		 * 
		 */
		private String nomePassageiro;
		/**
		 * 
		 */
		public Veiculo veiculo;
		/**
		 * 
		 */
		private int maquinaEmissora;
		/**
		 * 
		 */
		private String dataViagem;
		/**
		 * 
		 */
		private String horaViagem;
		/**
		 * 
		 */
		private String localEmbarque;
		/**
		 * 
		 */
		private int idPoltrona;
		/**
		 * 
		 */
		private String origemViagem;
		/**
		 * 
		 */
		private String destinoViagem;
		/**
		 * 
		 */
		private String docPassageiro;
		/**
		 * 
		 */
		private float valor;

		/**
		 * 
		 */
		public void imprimir() {
		}
	};
	
	/************************************************************/
	/**
	 * 
	 */
	public class Venda {
		/**
		 * 
		 */
		public float valorPago;
		/**
		 * 
		 */
		public int destino;
		/**
		 * 
		 */
		public float valorTroco;
		/**
		 * 
		 */
		public String horario;

		/**
		 * 
		 */
		public void escolherDestino() {
		}

		/**
		 * 
		 */
		public void escolherHorario() {
		}
	};
	
	public enum TipoTrajeto {
		/**
		 * 
		 */
		tpAereo,
		/**
		 * 
		 */
		tpFerroviario,
		/**
		 * 
		 */
		tpRodoviario;
	};
	
	public interface Trajeto {
		/**
		 * 
		 * @param novohorario 
		 */
		public void adicionarHorario(String novohorario);

		/**
		 * 
		 * @param novoshorarios 
		 */
		public void adicionarHorarios(String[] novoshorarios);
		
		public String getCidadea();
		
		public String getCidadeb();

		public Object getPreco();

		public int getQuantPartidaB();

		public int getQuantPartidaA();

		public String[] getPartidaB();

		public String[] getPartidaA();
		
	};
	
	/**
	 * 
	 */
	static public class TrajetoRodoviario implements Trajeto {
		/**
		 * 
		 */
		public float precoPassagem;
		/**
		 * 
		 */
		public String cidadeA;
		/**
		 * 
		 */
		public String cidadeB;
		/**
		 * 
		 */
		public String[] horariosA;
		/**
		 * 
		 */
		public String[] horariosB;
		/**
		 * 
		 */
		public Veiculo veiculo;
		
		@Override
		public void adicionarHorario(String novohorario) {
			// TODO Auto-generated method stub
			
		}
		@Override
		public void adicionarHorarios(String[] novoshorarios) {
			// TODO Auto-generated method stub
			
		}
		@Override
		public String getCidadea() {
			// TODO Auto-generated method stub
			return null;
		}
		@Override
		public String getCidadeb() {
			// TODO Auto-generated method stub
			return null;
		}
		@Override
		public Object getPreco() {
			// TODO Auto-generated method stub
			return null;
		}
		@Override
		public int getQuantPartidaB() {
			// TODO Auto-generated method stub
			return 0;
		}
		@Override
		public int getQuantPartidaA() {
			// TODO Auto-generated method stub
			return 0;
		}
		@Override
		public String[] getPartidaB() {
			// TODO Auto-generated method stub
			return null;
		}
		@Override
		public String[] getPartidaA() {
			// TODO Auto-generated method stub
			return null;
		}
	};

	/**
	 * 
	 */
	public class TrajetoFerroviario implements Trajeto {
		@Override
		public void adicionarHorario(String novohorario) {
		// TODO Auto-generated method stub
			
		}
		@Override
		public void adicionarHorarios(String[] novoshorarios) {
		// TODO Auto-generated method stub
				
		}
		@Override
		public String getCidadea() {
			// TODO Auto-generated method stub
			return null;
		}
		@Override
		public String getCidadeb() {
			// TODO Auto-generated method stub
			return null;
		}
		@Override
		public Object getPreco() {
			// TODO Auto-generated method stub
			return null;
		}
		@Override
		public int getQuantPartidaB() {
			// TODO Auto-generated method stub
			return 0;
		}
		@Override
		public int getQuantPartidaA() {
			// TODO Auto-generated method stub
			return 0;
		}
		@Override
		public String[] getPartidaB() {
			// TODO Auto-generated method stub
			return null;
		}
		@Override
		public String[] getPartidaA() {
			// TODO Auto-generated method stub
			return null;
		}
	};

	/**
	 * 
	 */
	public class TrajetoAereo implements Trajeto {

		@Override
		public void adicionarHorario(String novohorario) {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void adicionarHorarios(String[] novoshorarios) {
				// TODO Auto-generated method stub
				
		}

		@Override
		public String getCidadea() {
			// TODO Auto-generated method stub
			return null;
		}

		@Override
		public String getCidadeb() {
			// TODO Auto-generated method stub
			return null;
		}

		@Override
		public Object getPreco() {
			// TODO Auto-generated method stub
			return null;
		}

		@Override
		public int getQuantPartidaB() {
			// TODO Auto-generated method stub
			return 0;
		}

		@Override
		public int getQuantPartidaA() {
			// TODO Auto-generated method stub
			return 0;
		}

		@Override
		public String[] getPartidaB() {
			// TODO Auto-generated method stub
			return null;
		}

		@Override
		public String[] getPartidaA() {
			// TODO Auto-generated method stub
			return null;
		}
	};

	static public class Maquina {
		/**
		 * 
		 */
		public Trajeto trajeto;
		/**
		 * 
		 */
		private Bilhete[] bilhetes;
		/**
		 * 
		 */
		public Bilhete[] bilhete;
		/**
		 * 
		 */
		public Venda compra;
		/**
		 * 
		 */
		private int totalPassagensVendidas;
		/**
		 * 
		 */
		private float totalArrecadado;
		/**
		 * 
		 */
		private Bilhete[] bilhetesVendidos;
		/**
		 * 
		 */
		private int numSerie;

		/**
		 * 
		 * @param venda 
		 * @param bilhete 
		 */
		public void comprarBilhete(Venda venda, Bilhete bilhete) {
		
		}

		/**
		 * 
		 */
		public void encerrarVendas() {
		
		}
		
		public void iniciarVenda() {
			int i, quantidade;
			String escolha = null;
			char opcao;
			Boolean destinoA;
			String[] horarios;

			if (System.console() != null) {	
				System.out.printf("VENDA\n======\nDestinos: A - %s | B - %s\n", trajeto.getCidadea(), trajeto.getCidadeb());
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
					horarios = trajeto.getPartidaA();
					quantidade = trajeto.getQuantPartidaA();
				}
				else {
					horarios = trajeto.getPartidaB();
					quantidade = trajeto.getQuantPartidaB();

				}
				System.out.print("Horários: ");
				for (i = 0; i < quantidade; i++)
					System.out.printf("%s ", horarios[i]);
				escolha = System.console().readLine("\nDigite um horario valido: ");
				for (i = 0; i < quantidade; i++)
					System.out.printf("%s ", horarios[i]);
				System.out.printf("\nPreço da passagem: %.2f\n", trajeto.getPreco());
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
	};
	
	static Maquina CriarBHZBRA() {
		Maquina maquina;
		TrajetoRodoviario trajeto;
		String[] horariosA = {"7:45", "10:00", "15:00", "17:45", "21:00"};
		String[] horariosB = {"7:30", "10:45", "13:00", "14:45", "21:15", "22:00"};
		
		trajeto = new TrajetoRodoviario();
		trajeto.adicionarHorarios(horariosA);
		trajeto.adicionarHorarios(horariosB);

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