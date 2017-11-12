/**
 * 
 */
package PesquisaEleitoral;

import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

/**
 * @author Douglas
 *
 */
public class Aplicacao {

	private static void setAppTheme() {
		try {
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch (ClassNotFoundException | InstantiationException | IllegalAccessException
				| UnsupportedLookAndFeelException e1) {
			e1.printStackTrace();
			return;
		}
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Repositorio repositorio = new Repositorio();
		setAppTheme();
		new JanelaPrincipal(repositorio);
	}

}
