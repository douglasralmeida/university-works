package janelas;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.URL;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JToolBar;
import javax.swing.ListSelectionModel;

import componentes.AppPanel;

public class PainelGestao extends AppPanel
						  implements ActionListener {
	
	private static final long serialVersionUID = -435738107568975424L;
	String[] nomeColunas = {"Nome do funcionário", "Atividade"}; 
	JPanel painel = new JPanel(new BorderLayout());
	JFrame parent = null;
	
	public PainelGestao(JFrame parent) {
		super("Gestão da Clínica");
		this.parent = parent;
		add(painel, BorderLayout.CENTER);
		criarBarraFerramentas();
		criarControles();
	}
	
	private void criarBarraFerramentas() {
		JToolBar barraFerramentas = new JToolBar();
		JButton botao = null;
		
		barraFerramentas.setFloatable(false);
		botao = criarBotaoFerramenta("botaoNovo", "AD_FUNCIONARIO", "Novo funcionário");
		barraFerramentas.add(botao);
		botao = criarBotaoFerramenta("botaoEditar", "EDIT_FUNCIONARIO", "Editar funcionário");
		barraFerramentas.add(botao);
		botao = criarBotaoFerramenta("botaoExcluir", "EXC_FUNCIONARIO", "Excluir funcionário");
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
		String[][] dataFuncionarios = {{"Maria José da Silva", "Médico"},
									 {"João Antônia da Silva", "Técnico"}};
		JTable tabela = new JTable(dataFuncionarios, nomeColunas);
		JScrollPane listaScroll = new JScrollPane(tabela);

		tabela.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		painel.add(listaScroll, BorderLayout.CENTER);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getActionCommand() == "AD_FUNCIONARIO")
			new JanelaFuncionario(parent);
	}
}
