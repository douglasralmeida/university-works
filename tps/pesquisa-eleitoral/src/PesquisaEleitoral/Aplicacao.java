/**
 * 
 */
package PesquisaEleitoral;

/**
 * @author Douglas
 *
 */
public class Aplicacao {
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Repositorio repositorio = new Repositorio();
		new JanelaPrincipal(repositorio);
	}

}