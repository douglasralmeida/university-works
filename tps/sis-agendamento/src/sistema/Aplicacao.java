package sistema;

import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

/**
 * Aplicação da Pesquisa Eleitoral 
 */
public class Aplicacao {

	/**
	 * Confira a aparência da aplicação tal qual utilizada pelo sistema operacional
	 */
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
	 * Função Main
	 */
	public static void main(String[] args) {
		setAppTheme();
		new JanelaPrincipal();
	}

}
