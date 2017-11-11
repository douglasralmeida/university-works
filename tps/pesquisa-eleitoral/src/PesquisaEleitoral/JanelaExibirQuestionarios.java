/**
 * 
 */
package PesquisaEleitoral;

import javax.swing.JDialog;
import javax.swing.JFrame;

/**
 * @author Douglas
 *
 */
public class JanelaExibirQuestionarios extends JDialog {

	private static final long serialVersionUID = 1143872209310784376L;

	public JanelaExibirQuestionarios(JFrame Parent) {
		super(Parent, "Questionários Cadastrados", true);
		
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setResizable(false);
		setSize(500, 200);
		setLocationRelativeTo(Parent);
		setVisible(true);
	}
}