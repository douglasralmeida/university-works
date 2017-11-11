package PesquisaEleitoral;
/**
 * 	CLASSE QUESTIONARIO
 */

/**
 * @author Douglas
 *
 */
import java.io.IOException;

public class Questionario {
	private int ID;
	private String candidato;
	private Sexo sexo;
	private Escolaridade escolaridade;
	private Idade idade;
	private Renda renda;
	public Questionario(int ID) {
		this.ID = ID;
	}
	public int getID() {
		return ID;
	}
	public String getCandidato() {
		return candidato;
	}
	public void setCandidato(String candidato) throws IOException {
		if (candidato.length() > 0)
			this.candidato = candidato;
		else
			throw new IOException("O nome do candidato não foi informado.");
	}
	public Sexo getSexo() {
		return sexo;
	}
	public void setSexo(Sexo sexo) {
		this.sexo = sexo;
	}
	public Escolaridade getEscolaridade() {
		return escolaridade;
	}
	public void setEscolaridade(Escolaridade escolaridade) {
		this.escolaridade = escolaridade;
	}
	public Idade getIdade() {
		return idade;
	}
	public void setIdade(Idade idade) {
		this.idade = idade;
	}
	public Renda getRenda() {
		return renda;
	}
	public void setRenda(Renda renda) {
		this.renda = renda;
	}
	public String toString() {
		StringBuilder stringBuilder = new StringBuilder();

		stringBuilder.append("Questionario " + this.ID + "\n  Candidato: " + this.candidato);
		stringBuilder.append("\n  Sexo: " + this.sexo.toString());
		stringBuilder.append("\n  Escolaridade: " + this.escolaridade.toString());
		stringBuilder.append("\n  Idade: " + this.idade.toString());
		stringBuilder.append("\n  Renda: " + this.renda.toString());

		return stringBuilder.toString();
	}
}
