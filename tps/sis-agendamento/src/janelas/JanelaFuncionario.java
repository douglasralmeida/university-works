package janelas;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.URL;
import java.text.NumberFormat;
import java.text.ParseException;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFormattedTextField;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.JToolBar;
import javax.swing.SpringLayout;
import javax.swing.border.Border;
import javax.swing.text.MaskFormatter;
import javax.swing.text.NumberFormatter;

public class JanelaFuncionario extends JDialog
							   implements ActionListener {
	
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
		painel.setPreferredSize(new Dimension(400, 200));
		add(painel, BorderLayout.CENTER);
		pack();
		setLocationRelativeTo(null);
		setVisible(true);
	}
	
	private void ajustarControlesGerais(JLabel[] labels, JTextField[] fields) {
		int i, j;
		
		for (i = 0; i < labels.length; i++)
			layoutControles.putConstraint(SpringLayout.WEST, labels[i], 4, SpringLayout.WEST, painelInfoGerais);
		
		layoutControles.putConstraint(SpringLayout.WEST, fields[0], 4, SpringLayout.EAST, labels[2]);
		layoutControles.putConstraint(SpringLayout.NORTH, fields[0], 8, SpringLayout.NORTH, painelInfoGerais);
		layoutControles.putConstraint(SpringLayout.EAST, fields[0], -4, SpringLayout.EAST, painelInfoGerais);
		
		for (i = 1; i < fields.length; i++) {
			layoutControles.putConstraint(SpringLayout.NORTH, fields[i], 4, SpringLayout.SOUTH, fields[i-1]);
			layoutControles.putConstraint(SpringLayout.WEST, fields[i], 0, SpringLayout.WEST, fields[i-1]);
			layoutControles.putConstraint(SpringLayout.EAST, fields[i], 0, SpringLayout.EAST, fields[i-1]);
		}
		
		for (i = 0; i < fields.length; i++)
			layoutControles.putConstraint(SpringLayout.NORTH, labels[i], 3, SpringLayout.NORTH, fields[i]);
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
		JLabel labelNome = new JLabel("Nome:");
		JTextField textoNome = new JTextField();
		JLabel labelCpf = new JLabel("CPF:");
		JTextField textoCpf = null;
		JTextField textoMatricula = null;
		
		try {
			textoCpf = new JFormattedTextField(new MaskFormatter("###.###.###-##"));
			
			NumberFormat formatoNumerico = NumberFormat.getInstance();
		    NumberFormatter mascaraNumerica = new NumberFormatter(formatoNumerico);
		    mascaraNumerica.setValueClass(Integer.class);
		    mascaraNumerica.setMinimum(0);
		    mascaraNumerica.setMaximum(Integer.MAX_VALUE);
		    mascaraNumerica.setAllowsInvalid(false);
		    mascaraNumerica.setCommitsOnValidEdit(true);
			textoMatricula = new JFormattedTextField(mascaraNumerica);
		}
		catch (ParseException e) {
			System.err.println("Erro ao definir formatador de CPF: " + e.getMessage());	
		}
		JLabel labelMatricula = new JLabel("Matrícula:");		
		
		JLabel[] labels = {labelNome, labelCpf, labelMatricula};
		JTextField[] fields = {textoNome, textoCpf, textoMatricula};
		for (int i = 0; i < labels.length; i++) {
			painel.add(labels[i]);
			painel.add(fields[i]);	
		}

		ajustarControlesGerais(labels, fields);
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
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		
	}

}
