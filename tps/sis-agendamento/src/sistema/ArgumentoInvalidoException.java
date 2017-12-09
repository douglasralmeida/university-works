package sistema;
public class ArgumentoInvalidoException extends IllegalArgumentException {

	private static final long serialVersionUID = 2917178681935810241L;

	public ArgumentoInvalidoException(String s) {
		super(s);
	}
	
	public static void throwSeNuloOuBranco(String testString, String mensagem) {
		if (testString == null || testString.trim().isEmpty())
			throw new ArgumentoInvalidoException(mensagem);
	}
	
	public static void throwSeNaoENumero(String testString, String mensagem) {
		if (!testString.matches("\\d+"))
			throw new ArgumentoInvalidoException(mensagem);
	}
}
