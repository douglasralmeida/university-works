package pessoa;
import sistema.ArgumentoInvalidoException;
import sistema.Validadores;

public class Pessoa {
	private String cpf;
	private String nome;
	
	public Pessoa() {
	}
	
	public String getCpf() {
		return this.cpf;
	}
	
	public String getNome() {
		return this.nome;
	}
	
	public void setCpf(String cpf) throws ArgumentoInvalidoException {
		ArgumentoInvalidoException.throwSeNuloOuBranco(cpf, "O número do CPF não foi informado.");
		ArgumentoInvalidoException.throwSeNaoENumero(cpf, "O CPF informado não é numérico.");
		if (!Validadores.ehValidoCPF(cpf))
			new ArgumentoInvalidoException("O CPF informado é inválido.");
		
		this.cpf = cpf;
	}
	
	public void setNome(String nome) throws ArgumentoInvalidoException {
		ArgumentoInvalidoException.throwSeNuloOuBranco(nome, "O nome não foi informado.");
		
		this.nome = nome;
	}
}