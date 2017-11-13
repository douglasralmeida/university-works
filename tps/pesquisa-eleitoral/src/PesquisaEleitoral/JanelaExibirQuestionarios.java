/**
 * 
 */
package PesquisaEleitoral;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRootPane;
import javax.swing.JScrollPane;
import javax.swing.KeyStroke;

/**
 *  Janela para exibir todos os questionários 
 */
public class JanelaExibirQuestionarios extends JDialog {

	private static final long serialVersionUID = 1143872209310784376L;
	
	private Repositorio repositorio;
	private JButton botao;
	private JList<Questionario> lista;

	public JanelaExibirQuestionarios(JFrame Parent, Repositorio repositorio) {
		super(Parent, "Questionários Cadastrados", true);
		this.repositorio = repositorio;
		criarControles();
		setMnemonicos();		
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setResizable(false);
		setSize(400, 300);
		setLocationRelativeTo(Parent);
		setVisible(true);
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
	private DefaultListModel<Questionario> criarModelo() {
		int i;
		DefaultListModel<Questionario> modelo = new DefaultListModel<>();
		
		for (i = 0; i < repositorio.getSize(); i++) {
			modelo.addElement(repositorio.getQuestionario(i));
		}

		return modelo;		
	}
	private void criarControles() {
		setTitle("Questionários Cadastrados: " + repositorio.getSize() + " questionário(s)");
		lista = new JList<Questionario>(criarModelo());
		lista.setCellRenderer(new RenderizadorQuestionario());
		lista.addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent ev) {
				if ((ev.getClickCount() == 2) && (lista.getSelectedIndex() > -1))
					exibirQuestionario(lista.getSelectedIndex());
			}
		});
		lista.addKeyListener(new KeyAdapter() {
			public void keyPressed(KeyEvent ev) {
				switch (ev.getKeyCode()) {
				case KeyEvent.VK_ENTER:
					if (lista.getSelectedIndex() > -1)
						exibirQuestionario(lista.getSelectedIndex());
					break;
				}
			}
		});
		JScrollPane controleLista = new JScrollPane(lista);
		controleLista.setPreferredSize(new Dimension(200, 80));
		add(controleLista, BorderLayout.CENTER);
		
		JPanel panelRodape = new JPanel(new FlowLayout(FlowLayout.CENTER));
		botao = new JButton("OK");
		botao.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ev) {
				fecharJanela();
			}
		});
		panelRodape.add(botao);
		add(panelRodape, BorderLayout.SOUTH);
	}
	
	private void exibirQuestionario(int index) {
		Questionario questionario = repositorio.getQuestionario(index); 
		JOptionPane.showMessageDialog(null, questionario, "Pesquisa Eleitoral", JOptionPane.INFORMATION_MESSAGE);
	}
	
	private void fecharJanela() {
		setVisible(false);
	}
	
	private void setMnemonicos() {
		botao.setMnemonic(KeyEvent.VK_O);
	}
}