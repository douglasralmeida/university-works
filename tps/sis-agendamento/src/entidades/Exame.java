package entidades;

public class Exame implements Servico {

	private String nome;
	
	public Exame(String nome) {
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
