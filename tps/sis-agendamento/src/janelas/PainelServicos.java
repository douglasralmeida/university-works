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
import entidades.Servico;
import sistema.Aplicacao;

public class PainelServicos extends AppPanel
							implements ActionListener {
	
	private static final long serialVersionUID = 4120394099853208810L;
	DefaultTableModel data = new DefaultTableModel();
	String[] nomeColunas = {"Nome do serviço", "Tipo"};
	JTable tabela;
	JPanel painel = new JPanel(new BorderLayout());
	JFrame parent = null;
	
	public PainelServicos(JFrame parent) {
		super("Gestão de Serviços");
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
		botao = criarBotaoFerramenta("botaoNovo", "AD_SERVICO", "Novo serviço");
		barraFerramentas.add(botao);
		botao = criarBotaoFerramenta("botaoEditar", "EDIT_SERVICO", "Editar serviço");
		botao.setEnabled(false);
		barraFerramentas.add(botao);
		botao = criarBotaoFerramenta("botaoExcluir", "EXC_SERVICO", "Excluir serviço");
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
		Servico servico;
		
		for (i = 0; i < max; i++)
			data.removeRow(i);
		max = Aplicacao.getServicos().getSize();
		for (i = 0; i < max; i++) {
			servico = Aplicacao.getServicos().getServico(i);
			String[] item = {servico.getNome(), servico.getClass().getSimpleName()};
			data.addRow(item);
		}
		data.fireTableDataChanged();
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getActionCommand() == "AD_SERVICO") {
			JanelaServico janelaServico = new JanelaServico(parent);
			janelaServico.addWindowListener(new WindowListener() {

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