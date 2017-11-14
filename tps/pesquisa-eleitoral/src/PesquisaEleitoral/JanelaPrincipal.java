/**
 * 
 */
package PesquisaEleitoral;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import javax.swing.JButton;
import javax.swing.JFrame;

/**
 *  Janela principal do programa 
 */
public class JanelaPrincipal extends JFrame {
	private static final long serialVersionUID = 3956935555239378814L;
	
	Repositorio repositorio;
	private JButton btoLista;
	private JButton btoNovo;
	private JButton btoSair;
	
	public JanelaPrincipal(Repositorio repositorio) {
		super("Pesquisa Eleitoral");
		this.repositorio = repositorio;
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		getContentPane().setLayout(new GridLayout(3, 1, 0, 0));
		criarControles();
		setMnemonicos();
		setSize(400, 200);
		setLocationRelativeTo(null);
		setVisible(true);
	}

	private void criarControles() {
		btoNovo = new JButton("Novo questionário...");
		btoNovo.addActionListener(new ActionListener( ) {
			public void actionPerformed(ActionEvent e) {
				novoQuestionario();
			}
		});
		add(btoNovo);

		btoLista = new JButton("Exibir questionários...");
		btoLista.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				exibirQuestionarios();
			}
		});
		add(btoLista);

		btoSair = new JButton("Sair");
		btoSair.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});
		add(btoSair);	
	}

	private void exibirQuestionarios() {
		new JanelaExibirQuestionarios(this, repositorio);
	}
	
	private void novoQuestionario() {
		new JanelaNovoQuestionario(this, repositorio);
	}

	private void setMnemonicos() {
		btoNovo.setMnemonic(KeyEvent.VK_N);
		btoLista.setMnemonic(KeyEvent.VK_X);
		btoSair.setMnemonic(KeyEvent.VK_R);
	}
}
