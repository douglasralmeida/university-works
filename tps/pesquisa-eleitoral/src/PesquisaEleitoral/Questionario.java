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
	public Escolaridade getEscolaridade() {
		return escolaridade;
	}
	public Idade getIdade() {
		return idade;
	}
	public Renda getRenda() {
		return renda;
	}
	public Sexo getSexo() {
		return sexo;
	}
	public void setCandidato(String candidato) throws IOException {
		if (!candidato.isEmpty())
			this.candidato = candidato;
		else
			throw new IOException("O nome do candidato não foi informado.");
	}
	public void setEscolaridade(Escolaridade escolaridade) throws IOException {
		if (escolaridade != Escolaridade.NENHUM)
			this.escolaridade = escolaridade;
		else
			throw new IOException("A escolaridade do eleitor não foi selecionada.");
	}
	public void setIdade(Idade idade) throws IOException {
		if (idade != Idade.NENHUM)
			this.idade = idade;
		else
			throw new IOException("A idade do eleitor não foi selecionada.");
	}
	public void setRenda(Renda renda) throws IOException {
		if (renda != Renda.NENHUM)
			this.renda = renda;
		else
			throw new IOException("A renda familiar do eleitor não foi selecionada.");
	}
	public void setSexo(Sexo sexo) throws IOException {
		if (sexo != Sexo.NENHUM)
			this.sexo = sexo;
		else
			throw new IOException("O sexo do eleitor não foi selecionado.");
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
