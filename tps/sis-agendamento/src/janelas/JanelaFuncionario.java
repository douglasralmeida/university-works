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
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.swing.JToolBar;
import javax.swing.SpringLayout;
import javax.swing.border.Border;
import agendamento.Agenda;
import entidades.Servico;
import pessoa.Atendente;
import pessoa.Medico;
import sistema.Aplicacao;
import sistema.ArgumentoInvalidoException;

public class JanelaFuncionario extends JDialog
							   implements ActionListener {

	private static final long serialVersionUID = -4148117580479967832L;
	private String[] stringTipos = {"Técnico", "Médico"};
	private JTextField textoMatricula = new JTextField();
	private JLabel labelNome = new JLabel("Nome:");
	private JTextField textoNome = new JTextField();
	private JLabel labelCpf = new JLabel("CPF:");
	private JTextField textoCpf = new JTextField();
	private JLabel labelTipo = new JLabel("Tipo:");
	private JLabel labelServico = new JLabel("Servico:");
	private JRadioButton[] radios = new JRadioButton[2];
	private JComboBox<Servico> comboServico = new JComboBox<Servico>();
	private JPanel painel;
	private JPanel painelInfoGerais;
	private JLabel titulo = new JLabel("Novo funcionário");
	private JLabel subtitulo = new JLabel("NOVO - FUNCIONÁRIO");
	private SpringLayout layoutControles;
	
	public JanelaFuncionario(JFrame frame) {
		super(frame, "Funcionário");
		setLayout(new BorderLayout());
		painel = new JPanel(new BorderLayout());
		criarBarraFerramentas();
		criarControles();
		painel.setPreferredSize(new Dimension(400, 250));
		add(painel, BorderLayout.CENTER);
		pack();
		setLocationRelativeTo(null);
		setVisible(true);
	}
	
	private void ajustarControlesGerais(JLabel[] labels, JTextField[] fields) {
		int i;
		
		for (i = 0; i < labels.length; i++)
			layoutControles.putConstraint(SpringLayout.WEST, labels[i], 4, SpringLayout.WEST, painelInfoGerais);
		layoutControles.putConstraint(SpringLayout.WEST, labelTipo, 4, SpringLayout.WEST, painelInfoGerais);
		layoutControles.putConstraint(SpringLayout.WEST, labelServico, 4, SpringLayout.WEST, painelInfoGerais);
		
		layoutControles.putConstraint(SpringLayout.WEST, fields[0], 4, SpringLayout.EAST, labels[2]);
		layoutControles.putConstraint(SpringLayout.NORTH, fields[0], 8, SpringLayout.NORTH, painelInfoGerais);
		layoutControles.putConstraint(SpringLayout.EAST, fields[0], -4, SpringLayout.EAST, painelInfoGerais);
		
		for (i = 1; i < fields.length; i++) {
			layoutControles.putConstraint(SpringLayout.NORTH, fields[i], 4, SpringLayout.SOUTH, fields[i-1]);
			layoutControles.putConstraint(SpringLayout.WEST, fields[i], 0, SpringLayout.WEST, fields[i-1]);
			layoutControles.putConstraint(SpringLayout.EAST, fields[i], 0, SpringLayout.EAST, fields[i-1]);
		}
		
		layoutControles.putConstraint(SpringLayout.WEST, radios[0], 0, SpringLayout.WEST, fields[0]);
		layoutControles.putConstraint(SpringLayout.WEST, radios[1], 4, SpringLayout.EAST, radios[0]);
		layoutControles.putConstraint(SpringLayout.WEST, comboServico, 0, SpringLayout.WEST, fields[0]);
		
		layoutControles.putConstraint(SpringLayout.NORTH, radios[0], 4, SpringLayout.SOUTH, fields[fields.length-1]);
		layoutControles.putConstraint(SpringLayout.NORTH, radios[1], 0, SpringLayout.NORTH, radios[0]);
		layoutControles.putConstraint(SpringLayout.NORTH, comboServico, 4, SpringLayout.SOUTH, radios[1]);
		
		layoutControles.putConstraint(SpringLayout.EAST, comboServico, -4, SpringLayout.EAST, painelInfoGerais);
		
		for (i = 0; i < fields.length; i++)
			layoutControles.putConstraint(SpringLayout.NORTH, labels[i], 3, SpringLayout.NORTH, fields[i]);
		
		layoutControles.putConstraint(SpringLayout.NORTH, labelTipo, 3, SpringLayout.NORTH, radios[0]);
		layoutControles.putConstraint(SpringLayout.NORTH, labelServico, 3, SpringLayout.NORTH, comboServico);
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
		ButtonGroup bg = new ButtonGroup();
		JLabel labelMatricula = new JLabel("Matrícula:");		
		
		JLabel[] labels = {labelNome, labelCpf, labelMatricula};
		JTextField[] fields = {textoNome, textoCpf, textoMatricula};
		for (int i = 0; i < labels.length; i++) {
			painel.add(labels[i]);
			painel.add(fields[i]);	
		}
		
		painel.add(labelTipo);
		painel.add(labelServico);
		for (int i = 0; i < radios.length; i++) {
			radios[i] = new JRadioButton(stringTipos[i]);
			painel.add(radios[i]);
			bg.add(radios[i]);
		}
		radios[0].addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ev) {
				popularComobo("Exame");
			}
		});
		radios[1].addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ev) {
				popularComobo("Especialidade");
			}
		});
		painel.add(comboServico);
		ajustarControlesGerais(labels, fields);
	}

	protected void popularComobo(String string) {
		int i;
		int max = Aplicacao.getServicos().getSize();
		Servico servico;
		
		comboServico.removeAllItems();
		for (i = 0; i < max; i++) {
			servico = Aplicacao.getServicos().getServico(i);
			if (servico.getClass().getSimpleName().equals(string))
				comboServico.addItem(servico);
		}
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
		Atendente novaPessoa;
		if (ev.getActionCommand() == "SALVAR") {
			String txtMatricula = textoMatricula.getText();
			if (txtMatricula.isEmpty())
				return;
			
			try {
				novaPessoa = new Medico(Integer.parseInt(txtMatricula), (Servico) comboServico.getSelectedItem());
				novaPessoa.setCpf(textoCpf.getText());
				novaPessoa.setNome(textoNome.getText());
				gerarAgenda(novaPessoa, novaPessoa.getServico());
				Aplicacao.getPessoas().adicionar(novaPessoa);				
				setVisible(false);
				dispose();
			} catch (ArgumentoInvalidoException ex) {
				Aplicacao.exibirMsgErro(ex.getMessage());
			}
		}
		
	}

	private void gerarAgenda(Atendente novaPessoa, Servico servico) {
		Agenda novaagenda = new Agenda(servico, novaPessoa);
		novaagenda.gerarAtendimentos();
		
		Aplicacao.getAgendas().adicionar(novaagenda);
	}

}
