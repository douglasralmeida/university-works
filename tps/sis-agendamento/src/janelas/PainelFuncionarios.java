package janelas;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.net.URL;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JToolBar;
import javax.swing.ListSelectionModel;
import javax.swing.table.DefaultTableModel;

import componentes.AppPanel;
import pessoa.Atendente;
import sistema.Aplicacao;

public class PainelFuncionarios extends AppPanel
						        implements ActionListener {
	
	private static final long serialVersionUID = -435738107568975424L;
	DefaultTableModel data = new DefaultTableModel();
	String[] nomeColunas = {"Nome do funcionário", "Atividade", "Serviço"};
	JTable tabela;
	JPanel painel = new JPanel(new BorderLayout());
	JFrame parent = null;
	
	public PainelFuncionarios(JFrame parent) {
		super("Gestão de Funcionários");
		this.parent = parent;
		add(painel, BorderLayout.CENTER);
		criarBarraFerramentas();
		atualizarLista();
		criarControles();
	}
	
	private void criarBarraFerramentas() {
		JToolBar barraFerramentas = new JToolBar();
		JButton botao = null;
		
		barraFerramentas.setFloatable(false);
		botao = criarBotaoFerramenta("botaoNovo", "AD_FUNCIONARIO", "Novo funcionário");
		barraFerramentas.add(botao);
		botao = criarBotaoFerramenta("botaoEditar", "EDIT_FUNCIONARIO", "Editar funcionário");
		botao.setEnabled(false);
		barraFerramentas.add(botao);
		botao = criarBotaoFerramenta("botaoExcluir", "EXC_FUNCIONARIO", "Excluir funcionário");
		botao.setEnabled(false);
		barraFerramentas.add(botao);
		barraFerramentas.addSeparator();
		
		painel.add(barraFerramentas, BorderLayout.NORTH);
	}

	private JButton criarBotaoFerramenta(String img, String cmd, String dica) {
		String enderecoImagem = "/imagens/" + img + ".png";
		URL urlImagem = getClass().getResource(enderecoImagem);
		JButton botao = new JButton();
		
		botao.setActionCommand(cmd);
	    botao.setToolTipText(dica);
	    botao.addActionListener(this);
	    if (urlImagem != null) {
	        botao.setIcon(new ImageIcon(urlImagem, dica));
	    } else {
	        botao.setText(dica);
	        System.err.println("Recurso não encontrado: " + img);
	    }
	    
	    return botao;
	}

	private void criarControles() {
		tabela = new JTable(data);
		data.setColumnIdentifiers(nomeColunas);
		JScrollPane listaScroll = new JScrollPane(tabela);
		tabela.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		painel.add(listaScroll, BorderLayout.CENTER);
	}

	private void atualizarLista() {
		int i;
		int max = data.getRowCount();
		Atendente pessoa;
		
		for (i = 0; i < max; i++)
			data.removeRow(i);
		max = Aplicacao.getPessoas().getSize();
		for (i = 0; i < max; i++) {
			if (Aplicacao.getPessoas().getPessoa(i) instanceof Atendente) {
				pessoa = (Atendente) Aplicacao.getPessoas().getPessoa(i);
				String[] item = {pessoa.getNome(), pessoa.getClass().getSimpleName(), pessoa.getServico().toString()};
				data.addRow(item);
			}
		}
		data.fireTableDataChanged();
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getActionCommand() == "AD_FUNCIONARIO") {
			JanelaFuncionario janelaFuncionario = new JanelaFuncionario(parent);
			janelaFuncionario.addWindowListener(new WindowListener() {

				@Override
				public void windowActivated(WindowEvent arg0) {
				}

				@Override
				public void windowClosed(WindowEvent arg0) {
					atualizarLista();
				}

				@Override
				public void windowClosing(WindowEvent arg0) {
				}

				@Override
				public void windowDeactivated(WindowEvent arg0) {
				}

				@Override
				public void windowDeiconified(WindowEvent arg0) {
				}

				@Override
				public void windowIconified(WindowEvent arg0) {
				}

				@Override
				public void windowOpened(WindowEvent arg0) {					
				}
			});
		}
		
	}
}
