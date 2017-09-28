/**
 *	Maquina de Venda de Bilhetes
 *
 *	@version 1.0	
 *	@author Douglas Rodrigues de Almeida
 */
package Aplicativo;

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
		 */
		public class TrajetoRodoviario {
		};

		/**
		 * 
		 */
		public class TrajetoFerroviario {
		};

		/**
		 * 
		 */
		public class TrajetoAereo {
		};

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
		/**
		 * 
		 */
		public TipoTrajeto tipo;
		/**
		 * 
		 */
		public TipoTrajeto tipotrajeto;

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
	};
	
	public class Maquina {
		/**
		 * 
		 */
		private ModeloTrajeto trajeto;
		/**
		 * 
		 */
		public ModeloTrajeto trajeto;
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
	};

	private static Object Principal;;	
	
	/**
	 * Funcao Main
	 * @param args
	 */
	public static void main(String[] args) {
		Principal p = new Principal();
		
		Veiculo Onibus = new p.Veiculo("D001", 36);
		
		System.out.println("Onibus. ID: " + Onibus.idVeiculo + " Capacidade: " + Onibus.capacidade);
		
		System.out.println("Tá funcionando!");
	}

}