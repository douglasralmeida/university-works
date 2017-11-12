/**
 * 
 */
package PesquisaEleitoral;

import java.awt.BorderLayout;
import java.awt.Dimension;

import javax.swing.DefaultListModel;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JScrollPane;
import javax.swing.ListModel;
import javax.swing.ListSelectionModel;

/**
 * @author Douglas
 *
 */
public class JanelaExibirQuestionarios extends JDialog {

	private static final long serialVersionUID = 1143872209310784376L;
	
	private Repositorio repositorio;
	private JList<Questionario> lista;

	public JanelaExibirQuestionarios(JFrame Parent, Repositorio repositorio) {
		super(Parent, "Questionários Cadastrados", true);
		this.repositorio = repositorio;
		
		criarControles();
		exibirQuestionarios();
		
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setResizable(false);
		setSize(500, 200);
		setLocationRelativeTo(Parent);
		setVisible(true);
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
		lista = new JList<Questionario>(criarModelo());
		lista.setCellRenderer(new RenderizadorQuestionario());

		JScrollPane controleLista = new JScrollPane(lista);
		controleLista.setPreferredSize(new Dimension(250, 80));
		add(controleLista, BorderLayout.CENTER);
	}
	
	private void exibirQuestionarios() {

	}
}