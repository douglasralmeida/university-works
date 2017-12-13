package sistema;

import javax.swing.JOptionPane;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

import agendamento.Agendas;
import entidades.Servicos;
import janelas.JanelaPrincipal;
import pagamentos.Pagamentos;
import pessoa.Pessoas;

/**
 * Aplicação do Sistema de Agendamento
 */
public class Aplicacao {

	static Agendas agendas = new Agendas();
	static Pessoas pessoas = new Pessoas();
	static Servicos servicos = new Servicos();
	static Pagamentos formasPagamento = new Pagamentos();
	
	public static void exibirMsgErro(String msg) {
		JOptionPane.showMessageDialog(null, msg, "Erro", JOptionPane.ERROR_MESSAGE);	
	}
	
	public static Agendas getAgendas() {
		return agendas;
	}
	
	public static Pagamentos getFormasPagamento() {
		return formasPagamento;
	}
	
	public static Pessoas getPessoas() {
		return pessoas;
	}
	
	public static Servicos getServicos() {
		return servicos;
	}
	
	/**
	 * Confira a aparência da aplicação tal qual utilizada pelo sistema operacional
	 */
	private static void setAppTheme() {
		try {
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch (ClassNotFoundException | InstantiationException | IllegalAccessException
				| UnsupportedLookAndFeelException e1) {
			e1.printStackTrace();
			return;
		}
	}
	
	/**
	 * Função Main
	 */
	public static void main(String[] args) {
		setAppTheme();
		new JanelaPrincipal();
	}

}
