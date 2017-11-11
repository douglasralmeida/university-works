/**
 * 
 */
package PesquisaEleitoral;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.io.IOException;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JRootPane;
import javax.swing.JTextField;
import javax.swing.KeyStroke;
import javax.swing.SpringLayout;
import javax.swing.SwingConstants;

/**
 * @author Douglas
 *
 */
public class JanelaNovoQuestionario extends JDialog  {
	private static final long serialVersionUID = -4644227182969398152L;
	final String strTitulo = "<html><span style='font-size:12px; color: #003399;'>Pesquisa espontânea para Presidente</span></html>";
	final String[] strsBotoes = {
			"Salvar",
			"Imprimir",
			"Cancelar"
	};
	final String[] strsRotulos = {
			"Nome do candidato: ",
			"Sexo do eleitor: ",
			"Nível de escolaridade: "
	};
	final String[] strsSexo = {
			"Feminino",
			"Masculino",
			"Não informado"
	};
	private JTextField editCandidato;
	private JPanel panelPrincipal;
	private JLabel txtTitulo;
	private JLabel txtCandidato;
	private JLabel txtSexo;
	private JLabel txtEscolaridade;
	private JButton[] botoes;
	private JRadioButton[] radiosSexo;
	private JRadioButton[] radiosEscolaridade;
	
	private SpringLayout layout;

	public JanelaNovoQuestionario(JFrame Parent) {
		super(Parent, "Novo Questionário", true);
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setResizable(false);
		
		getContentPane().setLayout(new BorderLayout());
		
		createControls();
		setLayoutControls();
		
		pack();
		setLocationRelativeTo(Parent);
		setVisible(true);
	}
	
	private void createControls() {
		int i;
		JPanel panelTitulo = new JPanel(new GridLayout(0, 1));
		JPanel panelRodape = new JPanel();
		radiosSexo = new JRadioButton[strsSexo.length];
		radiosEscolaridade = new JRadioButton[Escolaridade.getLength()];
		botoes = new JButton[strsBotoes.length];
				
		txtTitulo = new JLabel(strTitulo, SwingConstants.CENTER);
		panelTitulo.add(txtTitulo);
		
		layout = new SpringLayout();
		panelPrincipal = new JPanel();
		panelPrincipal.setLayout(layout);
		panelPrincipal.setPreferredSize(new Dimension(400, 100));
		txtCandidato = new JLabel(strsRotulos[0]);
		editCandidato = new JTextField(20);
		panelPrincipal.add(txtCandidato);
		panelPrincipal.add(editCandidato);			
		txtSexo = new JLabel(strsRotulos[1]);
		panelPrincipal.add(txtSexo);
		ButtonGroup grupoSexo = new ButtonGroup();
		for (i = 0; i < strsSexo.length; i++) {
			radiosSexo[i] = new JRadioButton(strsSexo[i]);
			grupoSexo.add(radiosSexo[i]);
			panelPrincipal.add(radiosSexo[i]);
		}			
		txtEscolaridade = new JLabel(strsRotulos[2]);
		panelPrincipal.add(txtEscolaridade);
		ButtonGroup grupoEscolaridade = new ButtonGroup();
		for (i = 0; i < Escolaridade.getLength() - 1; i++) {
			radiosEscolaridade[i] = new JRadioButton(Escolaridade.values()[i+1].toString());
			grupoEscolaridade.add(radiosEscolaridade[i]);
			panelPrincipal.add(radiosEscolaridade[i]);

		}
		
		panelRodape.setLayout(new FlowLayout(FlowLayout.CENTER));
		for (i = 0; i < strsBotoes.length; i++) {
			botoes[i] = new JButton(strsBotoes[i]);
			panelRodape.add(botoes[i]);
		}
		//Botao Salvar		
		botoes[0].addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ev) {
				popularQuestionario();
			}
		});
		//Botao Imprimir
		botoes[1].addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ev) {
				//popularQuestionario();
			}
		});
		//Botao Cancelar
		botoes[2].addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ev) {
				fecharJanela();
			}
		});

		add(panelTitulo, BorderLayout.NORTH);
		add(panelPrincipal, BorderLayout.CENTER);
		add(panelRodape, BorderLayout.SOUTH);
	}
	
	//Pressionar ESC para sair da janela
	protected JRootPane createRootPane() {
		ActionListener actionListener = new ActionListener() {
			public void actionPerformed(ActionEvent actionEvent) {
				setVisible(false);
			}
	    };
	    JRootPane rootPane = new JRootPane();
	    KeyStroke stroke = KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0);
	    rootPane.registerKeyboardAction(actionListener, stroke, JComponent.WHEN_IN_FOCUSED_WINDOW);
	    return rootPane;
	  }
	
	private void fecharJanela() {
		setVisible(false);
	}
	
	private void popularQuestionario() {
		Questionario novoQuestionario = new Questionario(1);
		try {
			novoQuestionario.setCandidato(editCandidato.getText());
		}
		catch (IOException ex) {
			JOptionPane.showMessageDialog(null, ex.getMessage(), "Pesquisa Eleitoral", JOptionPane.ERROR_MESSAGE);
		}				
	}
	
	private void setLayoutControls() {
		int i;
		
		layout.putConstraint(SpringLayout.WEST, txtCandidato, 4, SpringLayout.WEST, panelPrincipal);
		layout.putConstraint(SpringLayout.WEST, editCandidato, 16, SpringLayout.EAST, txtCandidato);
		layout.putConstraint(SpringLayout.NORTH, editCandidato, 8, SpringLayout.NORTH, panelPrincipal);
		layout.putConstraint(SpringLayout.NORTH, txtCandidato, 3, SpringLayout.NORTH, editCandidato);
		
		layout.putConstraint(SpringLayout.WEST, txtSexo, 4, SpringLayout.WEST, panelPrincipal);
		layout.putConstraint(SpringLayout.WEST, radiosSexo[0], 0, SpringLayout.WEST, editCandidato);
		for (i = 1; i < radiosSexo.length; i++)
			layout.putConstraint(SpringLayout.WEST, radiosSexo[i], 4, SpringLayout.EAST, radiosSexo[i-1]);
		for (i = 0; i < radiosSexo.length; i++)
			layout.putConstraint(SpringLayout.NORTH, radiosSexo[i], 4, SpringLayout.SOUTH, editCandidato);
		layout.putConstraint(SpringLayout.NORTH, txtSexo, 4, SpringLayout.NORTH, radiosSexo[0]);
		
		layout.putConstraint(SpringLayout.WEST, txtEscolaridade, 4, SpringLayout.WEST, panelPrincipal);
		layout.putConstraint(SpringLayout.WEST, radiosEscolaridade[0], 0, SpringLayout.WEST, editCandidato);
		for (i = 1; i < radiosEscolaridade.length-1; i++)
			layout.putConstraint(SpringLayout.WEST, radiosEscolaridade[i], 4, SpringLayout.EAST, radiosEscolaridade[i-1]);
		layout.putConstraint(SpringLayout.WEST, radiosEscolaridade[3], 0, SpringLayout.WEST, radiosEscolaridade[0]);
		for (i = 0; i < radiosEscolaridade.length-1; i++)
			layout.putConstraint(SpringLayout.NORTH, radiosEscolaridade[i], 4, SpringLayout.SOUTH, radiosSexo[0]);
		layout.putConstraint(SpringLayout.NORTH, radiosEscolaridade[3], 0, SpringLayout.SOUTH, radiosEscolaridade[0]);
		layout.putConstraint(SpringLayout.NORTH, txtEscolaridade, 4, SpringLayout.NORTH, radiosEscolaridade[0]);		
	}
}
