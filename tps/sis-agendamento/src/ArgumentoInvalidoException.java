
public class ArgumentoInvalidoException extends IllegalArgumentException {

	public ArgumentoInvalidoException(String s) {
		super(s);
	}
	
	static void throwSeNuloOuBranco(String testString, String mensagem) {
		if (testString == null || testString.trim().isEmpty())
			throw new ArgumentoInvalidoException(mensagem);
	}
}
