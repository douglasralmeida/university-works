package entidades;

public class Especialidade implements Servico {

	String nome;
	
	public Especialidade(String nome) {
		this.nome = nome;
	}

	@Override
	public String getNome() {
		return this.nome;
	}
	
	@Override
	public String toString() {
		return this.nome;
	}
}
