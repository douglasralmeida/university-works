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
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

/**
 * @author Douglas
 *
 */
public class JanelaPrincipal extends JFrame {
	private static final long serialVersionUID = 3956935555239378814L;
	
	Repositorio repositorio;
	final private JButton btoLista;
	final private JButton btoNovo;
	final private JButton btoSair;
	
	public JanelaPrincipal(Repositorio repositorio) {
		super("Pesquisa Eleitoral");
		this.repositorio = repositorio;
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setFrameTheme();
		getContentPane().setLayout(new GridLayout(3, 1, 0, 0));
		
		btoNovo = new JButton("Novo questionário...");
		btoNovo.setMnemonic(KeyEvent.VK_N);
		btoNovo.addActionListener(new ActionListener( ) {
			public void actionPerformed(ActionEvent e) {
				btoNovoClick();
			}
		});
		add(btoNovo);
						
		btoLista = new JButton("Exibir questionários...");
		btoLista.setMnemonic(KeyEvent.VK_X);
		btoLista.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				btoListaClick();
			}
		});
		add(btoLista);
						
		btoSair = new JButton("Sair");
		btoSair.setMnemonic(KeyEvent.VK_R);
		btoSair.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				btoSairClick();
			}
		});
		add(btoSair);
		
		setSize(400, 200);
		setLocationRelativeTo(null);
		setVisible(true);
	}
	
	private void btoListaClick() {
		new JanelaExibirQuestionarios(this, repositorio);
	}
	
	private void btoNovoClick() {
		new JanelaNovoQuestionario(this, repositorio);
	}
	
	private void btoSairClick() {
		System.exit(0);
	}
	
	private void setFrameTheme() {		
		try {
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch (ClassNotFoundException e) {
			return;
		} catch (InstantiationException e) {
			return;
		} catch (IllegalAccessException e) {
			return;
		} catch (UnsupportedLookAndFeelException e) {
			return;
		}
	}
}
