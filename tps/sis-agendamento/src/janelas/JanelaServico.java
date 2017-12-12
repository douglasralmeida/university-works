package janelas;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.URL;
import javax.swing.BorderFactory;
import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.swing.JToolBar;
import javax.swing.SpringLayout;
import javax.swing.border.Border;

import entidades.Especialidade;
import entidades.Exame;
import entidades.Servico;
import sistema.Aplicacao;
import sistema.ArgumentoInvalidoException;

public class JanelaServico extends JDialog
							   implements ActionListener {

	private static final long serialVersionUID = -4148117580479967832L;
	String[] tipoServico = {"Especialidade Médica", "Exame Médico"};
	private JLabel labelNome = new JLabel("Nome:");
	private JLabel labelTipo = new JLabel("Tipo:");
	private JTextField textoNome = new JTextField();
	private JPanel painel;
	private JPanel painelInfoGerais;
	JRadioButton[] radios = new JRadioButton[2];
	private JLabel titulo = new JLabel("Novo serviço");
	private JLabel subtitulo = new JLabel("NOVO - SERVIÇO");
	private SpringLayout layoutControles;
	
	public JanelaServico(JFrame frame) {
		super(frame, "Serviço");
		setLayout(new BorderLayout());
		painel = new JPanel(new BorderLayout());
		criarBarraFerramentas();
		criarControles();
		painel.setPreferredSize(new Dimension(400, 200));
		add(painel, BorderLayout.CENTER);
		pack();
		setLocationRelativeTo(null);
		setVisible(true);
	}
	
	private void ajustarControlesGerais(JLabel[] labels, JTextField[] fields, JRadioButton[] radios) {
		layoutControles.putConstraint(SpringLayout.WEST, labels[0], 4, SpringLayout.WEST, painelInfoGerais);
		layoutControles.putConstraint(SpringLayout.WEST, labels[1], 4, SpringLayout.WEST, painelInfoGerais);
		
		layoutControles.putConstraint(SpringLayout.WEST, fields[0], 4, SpringLayout.EAST, labels[0]);
		layoutControles.putConstraint(SpringLayout.NORTH, fields[0], 8, SpringLayout.NORTH, painelInfoGerais);
		layoutControles.putConstraint(SpringLayout.EAST, fields[0], -4, SpringLayout.EAST, painelInfoGerais);
		
		layoutControles.putConstraint(SpringLayout.NORTH, radios[0], 4, SpringLayout.SOUTH, fields[0]);
		layoutControles.putConstraint(SpringLayout.NORTH, radios[1], 4, SpringLayout.SOUTH, fields[0]);
		layoutControles.putConstraint(SpringLayout.WEST, radios[0], 0, SpringLayout.WEST, fields[0]);
		layoutControles.putConstraint(SpringLayout.WEST, radios[1], 4, SpringLayout.EAST, radios[0]);
		
		layoutControles.putConstraint(SpringLayout.NORTH, labels[0], 3, SpringLayout.NORTH, fields[0]);
		layoutControles.putConstraint(SpringLayout.NORTH, labels[1], 4, SpringLayout.NORTH, radios[0]);
	}

	private void criarControles() {
		JPanel painelCabecalho = new JPanel(new GridLayout(0, 1));	
		Font fonteNova = new Font(titulo.getFont().getFontName(), Font.PLAIN, 16);
		titulo.setFont(fonteNova);
		painelCabecalho.add(subtitulo);
		painelCabecalho.add(titulo);
		
		JPanel painelVazio = new JPanel();
		painelVazio.setSize(10, 16);
		painelCabecalho.add(painelVazio);
		
		JLabel tituloGerais = new JLabel("Dados Gerais");
		Border borda = BorderFactory.createMatteBorder(0, 0, 1, 0, SystemColor.controlShadow);
		tituloGerais.setBorder(borda);
		painelCabecalho.add(tituloGerais);
		
		Border bordaVazia = BorderFactory.createEmptyBorder(8, 8, 8, 8);
		painel.setBorder(bordaVazia);
		painel.add(painelCabecalho, BorderLayout.NORTH);
		
		layoutControles = new SpringLayout();
		painelInfoGerais = new JPanel(layoutControles);
		criarControlesGerais(painelInfoGerais);
		painel.add(painelInfoGerais, BorderLayout.CENTER);
	}

	private void criarControlesGerais(JPanel painel) {
		int i;
		ButtonGroup bg = new ButtonGroup();
		JLabel[] labels = {labelNome, labelTipo};
		JTextField[] fields = {textoNome};
		painel.add(labels[0]);
		painel.add(labels[1]);
		painel.add(fields[0]);
		for (i = 0; i < radios.length; i++) {
			radios[i] = new JRadioButton(tipoServico[i]);
			painel.add(radios[i]);
			bg.add(radios[i]);
		}
		
		ajustarControlesGerais(labels, fields, radios);
	}

	private void criarBarraFerramentas() {
		JToolBar barraFerramentas = new JToolBar();
		JButton botao = null;
		
		barraFerramentas.setFloatable(false);
		botao = criarBotaoFerramenta("botaoSalvar", "SALVAR", "Salvar");
		barraFerramentas.add(botao);
		barraFerramentas.addSeparator();
		
		add(barraFerramentas, BorderLayout.NORTH);		
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

	@Override
	public void actionPerformed(ActionEvent ev) {
		Servico novoServico = null;
		if (ev.getActionCommand() == "SALVAR") {	
			try {
				if (!(radios[0].isSelected() || radios[1].isSelected())) {
					Aplicacao.exibirMsgErro("Selecione um tipo de serviço antes de continuar.");
					return;
				}
				if (radios[0].isSelected())
					novoServico = new Especialidade(textoNome.getText());
				else
					novoServico = new Exame(textoNome.getText());
				Aplicacao.getServicos().adicionar(novoServico);
				setVisible(false);
				dispose();
			} catch (ArgumentoInvalidoException ex) {
				Aplicacao.exibirMsgErro(ex.getMessage());
			}
		}
		
	}

}
