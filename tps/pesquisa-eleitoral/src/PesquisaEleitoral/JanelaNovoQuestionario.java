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
import java.awt.event.KeyAdapter;
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
	Repositorio repositorio;
	final String strTitulo = "<html><span style='font-size:12px; color: #003399;'>Pesquisa espontânea para Presidente</span></html>";
	final String[] strsBotoes = {
			"Salvar",
			"Imprimir",
			"Cancelar"
	};
	final String[] strsRotulos = {
			"Nome do candidato: ",
			"Sexo do eleitor: ",
			"Nível de escolaridade: ",
			"Idade do eleitor: ",
			"Renda familiar do eleitor: "
	};
	private Escolaridade escolaridadeEscolhida = Escolaridade.NENHUM;
	private Idade idadeEscolhida = Idade.NENHUM;
	private Renda rendaEscolhida = Renda.NENHUM;
	private Sexo sexoEscolhido = Sexo.NENHUM;	
	private JTextField editCandidato;
	private JPanel panelPrincipal;
	private JLabel txtTitulo;
	private JButton[] botoes;
	private ButtonGroup[] grupos;
	private JRadioButton[][] radios;
	private JLabel[] rotulos;
	private SpringLayout layout;
	
	public JanelaNovoQuestionario(JFrame Parent, Repositorio repositorio) {
		super(Parent, "Novo Questionário", true);
		this.repositorio = repositorio;
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setResizable(false);
		getContentPane().setLayout(new BorderLayout());
		
		criarControles();
		setMnemonicos();
		setJanelaLayout();
		
		pack();
		setLocationRelativeTo(Parent);
		setVisible(true);
	}
	
	private void criarControles() {
		int i, j;
		
		JPanel panelTitulo = new JPanel(new GridLayout(0, 1));
		txtTitulo = new JLabel(strTitulo, SwingConstants.CENTER);
		panelTitulo.add(txtTitulo);
		
		layout = new SpringLayout();
		panelPrincipal = new JPanel();
		panelPrincipal.setLayout(layout);
		panelPrincipal.setPreferredSize(new Dimension(716, 140));
		grupos = new ButtonGroup[4];
		radios = new JRadioButton[4][];
		rotulos = new JLabel[strsRotulos.length];
		for (i = 0; i < grupos.length; i++)
			grupos[i] = new ButtonGroup();
		for (i = 0; i < rotulos.length; i++) {
			rotulos[i] = new JLabel(strsRotulos[i]);
			panelPrincipal.add(rotulos[i]);
		}
		editCandidato = new JTextField(20);
		panelPrincipal.add(editCandidato);
		radios[0] = new JRadioButton[Sexo.getLength()-1];
		radios[1] = new JRadioButton[Escolaridade.getLength()-1];
		radios[2] = new JRadioButton[Idade.getLength()-1];
		radios[3] = new JRadioButton[Renda.getLength()-1];
		//Opção de seleção Sexo
		for (i = 0; i < radios[0].length; i++) {
			radios[0][i] = new JRadioButton(Sexo.values()[i+1].toString());
			radios[0][i].setActionCommand(Sexo.values()[i+1].name());
			radios[0][i].addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent ev) {
					sexoEscolhido = Sexo.valueOf(ev.getActionCommand());
				}
			});
			radios[0][i].addKeyListener(new KeyAdapter() {
				public void keyReleased(KeyEvent e) {
					switch (e.getKeyCode()) {
					case KeyEvent.VK_UP:
					case KeyEvent.VK_DOWN:
					case KeyEvent.VK_LEFT:
					case KeyEvent.VK_RIGHT:
						sexoEscolhido = Sexo.valueOf(grupos[0].getSelection().getActionCommand());
						break;
					default:
						break;
					}
				}
			});
		}
		//Opção de seleção Escolaridade
		for (i = 0; i < radios[1].length; i++) {
			radios[1][i] = new JRadioButton(Escolaridade.values()[i+1].toString());
			radios[1][i].setActionCommand(Escolaridade.values()[i+1].name());
			radios[1][i].addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent ev) {
					escolaridadeEscolhida = Escolaridade.valueOf(ev.getActionCommand());
				}
			});
			radios[1][i].addKeyListener(new KeyAdapter() {
				public void keyReleased(KeyEvent e) {
					switch (e.getKeyCode()) {
					case KeyEvent.VK_UP:
					case KeyEvent.VK_DOWN:
					case KeyEvent.VK_LEFT:
					case KeyEvent.VK_RIGHT:
						escolaridadeEscolhida = Escolaridade.valueOf(grupos[1].getSelection().getActionCommand());
						break;
					}
				}
			});
		}
		//Opção de seleção Idade
		for (i = 0; i < radios[2].length; i++) {
			radios[2][i] = new JRadioButton(Idade.values()[i+1].toString());
			radios[2][i].setActionCommand(Idade.values()[i+1].name());
			radios[2][i].addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent ev) {
					idadeEscolhida = Idade.valueOf(ev.getActionCommand());
				}
			});
			radios[2][i].addKeyListener(new KeyAdapter() {
				public void keyReleased(KeyEvent e) {
					switch (e.getKeyCode()) {
					case KeyEvent.VK_UP:
					case KeyEvent.VK_DOWN:
					case KeyEvent.VK_LEFT:
					case KeyEvent.VK_RIGHT:
						idadeEscolhida = Idade.valueOf(grupos[2].getSelection().getActionCommand());
						break;
					}
				}
			});
		}
		//Opção de seleção Renda
		for (i = 0; i < radios[3].length; i++) {
			radios[3][i] = new JRadioButton(Renda.values()[i+1].toString());
			radios[3][i].setActionCommand(Renda.values()[i+1].name());
			radios[3][i].addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent ev) {
					rendaEscolhida = Renda.valueOf(ev.getActionCommand());
				}
			});
			radios[3][i].addKeyListener(new KeyAdapter() {
				public void keyReleased(KeyEvent e) {
					switch (e.getKeyCode()) {
					case KeyEvent.VK_UP:
					case KeyEvent.VK_DOWN:
					case KeyEvent.VK_LEFT:
					case KeyEvent.VK_RIGHT:
						rendaEscolhida = Renda.valueOf(grupos[3].getSelection().getActionCommand());
						break;
					}
				}
			});
		}
		for (i = 0; i < radios.length; i++)
			for (j = 0; j < radios[i].length; j++) {
				grupos[i].add(radios[i][j]);
				panelPrincipal.add(radios[i][j]);
			}
		
		JPanel panelRodape = new JPanel(new FlowLayout(FlowLayout.CENTER));
		botoes = new JButton[strsBotoes.length];
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
		getRootPane().setDefaultButton(botoes[0]);
		//Botao Imprimir
		botoes[1].addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ev) {
				exibirQuestionario();
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
			public void actionPerformed(ActionEvent ev) {
				fecharJanela();
			}
	    };
	    JRootPane panelRaiz = new JRootPane();
	    KeyStroke stroke = KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0);
	    panelRaiz.registerKeyboardAction(actionListener, stroke, JComponent.WHEN_IN_FOCUSED_WINDOW);
	    return panelRaiz;
	  }
	
	private void exibirQuestionario() {
		Questionario novoQuestionario = new Questionario(repositorio.getSize() + 1);
		try {
			novoQuestionario.setCandidato(editCandidato.getText());
			novoQuestionario.setSexo(sexoEscolhido);
			novoQuestionario.setEscolaridade(escolaridadeEscolhida);
			novoQuestionario.setIdade(idadeEscolhida);
			novoQuestionario.setRenda(rendaEscolhida);
			JOptionPane.showMessageDialog(null, novoQuestionario, "Pesquisa Eleitoral", JOptionPane.INFORMATION_MESSAGE);
		}
		catch (IOException ex) {
			JOptionPane.showMessageDialog(null, ex.getMessage(), "Pesquisa Eleitoral", JOptionPane.ERROR_MESSAGE);
		}		
	}
	
	private void fecharJanela() {
		setVisible(false);
	}
	
	private void popularQuestionario() {
		Questionario novoQuestionario = new Questionario(repositorio.getSize() + 1);
		try {
			novoQuestionario.setCandidato(editCandidato.getText());
			novoQuestionario.setSexo(sexoEscolhido);
			novoQuestionario.setEscolaridade(escolaridadeEscolhida);
			novoQuestionario.setIdade(idadeEscolhida);
			novoQuestionario.setRenda(rendaEscolhida);
			repositorio.adicionarQuestionario(novoQuestionario);
			fecharJanela();
		}
		catch (IOException ex) {
			JOptionPane.showMessageDialog(null, ex.getMessage(), "Pesquisa Eleitoral", JOptionPane.ERROR_MESSAGE);
		}
	}
	
	private void setJanelaLayout() {
		int i, j;
		
		for (i = 0; i < rotulos.length; i++)
			layout.putConstraint(SpringLayout.WEST, rotulos[i], 4, SpringLayout.WEST, panelPrincipal);
		layout.putConstraint(SpringLayout.WEST, editCandidato, 4, SpringLayout.EAST, rotulos[4]);
		layout.putConstraint(SpringLayout.NORTH, editCandidato, 8, SpringLayout.NORTH, panelPrincipal);
		layout.putConstraint(SpringLayout.NORTH, rotulos[0], 3, SpringLayout.NORTH, editCandidato);
		layout.putConstraint(SpringLayout.NORTH, radios[0][0], 4, SpringLayout.SOUTH, editCandidato);
		for (i = 1; i < radios.length; i++) {
			layout.putConstraint(SpringLayout.NORTH, radios[i][0], 4, SpringLayout.SOUTH, radios[i-1][0]);
		}
		for (i = 0; i < radios.length; i++) {
			layout.putConstraint(SpringLayout.WEST, radios[i][0], 0, SpringLayout.WEST, editCandidato);
			for (j = 1; j < radios[i].length; j++) {
				layout.putConstraint(SpringLayout.WEST, radios[i][j], 4, SpringLayout.EAST, radios[i][j-1]);
				layout.putConstraint(SpringLayout.NORTH, radios[i][j], 0, SpringLayout.NORTH, radios[i][0]);
			}
		}
		for (i = 1; i < rotulos.length; i++)
			layout.putConstraint(SpringLayout.NORTH, rotulos[i], 4, SpringLayout.NORTH, radios[i-1][0]);
	}
	
	private void setMnemonicos() {
		rotulos[0].setDisplayedMnemonic('n');
		rotulos[0].setLabelFor(editCandidato);
		botoes[0].setMnemonic(KeyEvent.VK_S);
		botoes[1].setMnemonic(KeyEvent.VK_I);
		botoes[2].setMnemonic(KeyEvent.VK_C);
	}	
}
