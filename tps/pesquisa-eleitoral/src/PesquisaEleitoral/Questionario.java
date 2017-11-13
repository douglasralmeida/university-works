package PesquisaEleitoral;
/**
 * 	CLASSE QUESTIONARIO
 */

/**
 * @author Douglas
 *
 */
import java.io.IOException;

/**
 *  Classe que representa o questionário 
 */
public class Questionario {
	private int ID;
	private String candidato;
	private Sexo sexo;
	private Escolaridade escolaridade;
	private Idade idade;
	private Renda renda;
	
	/**
	 *  Construtor do Questionário
	 *  @param ID identificação do questionário no repositório 
	 */
	public Questionario(int ID) {
		this.ID = ID;
	}
	
	/**
	 * Retorna o identificador do questionário
	 * @return  identificador do questioário
	 */
	public int getID() {
		return ID;
	}
	
	/**
	 * Retorna o nome do candidato no questionário
	 * @return  o nome do candidato
	 */
	public String getCandidato() {
		return candidato;
	}
	
	/**
	 * Retorna a escolaridade do eleitor no questionário
	 * @return  a escolaridade do eleitor
	 */
	public Escolaridade getEscolaridade() {
		return escolaridade;
	}
	
	/**
	 * Retorna a idade do eleitor no questionário
	 * @return  a idade do eleitor
	 */
	public Idade getIdade() {
		return idade;
	}
	
	/**
	 * Retorna a renda do eleitor no questionário
	 * @return  a renda do eleitor
	 */
	public Renda getRenda() {
		return renda;
	}
	
	/**
	 * Retorna o sexo do eleitor no questionário
	 * @return  o sexo do eleitor
	 */
	public Sexo getSexo() {
		return sexo;
	}
	
	/**
	 * Altera o nome do candidato no questionário
	 * @param candidato  o nome do candidato
	 * @exception IOException  Gera uma exceção caso o nome seja vazio
	 */
	public void setCandidato(String candidato) throws IOException {
		if (!candidato.isEmpty())
			this.candidato = candidato;
		else
			throw new IOException("O nome do candidato não foi informado.");
	}
	
	/**
	 * Altera a escolaridade do eleitor no questionário
	 * @param escolaridade  a escolaridade do eleitor
	 * @exception IOException  Gera uma exceção caso a escolaridade não tenha sido escolhida
	 */
	public void setEscolaridade(Escolaridade escolaridade) throws IOException {
		if (escolaridade != Escolaridade.NENHUM)
			this.escolaridade = escolaridade;
		else
			throw new IOException("A escolaridade do eleitor não foi selecionada.");
	}
	
	/**
	 * Altera a idade do eleitor no questionário
	 * @param idade  a idade do eleitor
	 * @exception IOException  Gera uma exceção caso a idade não tenha sido escolhida
	 */
	public void setIdade(Idade idade) throws IOException {
		if (idade != Idade.NENHUM)
			this.idade = idade;
		else
			throw new IOException("A idade do eleitor não foi selecionada.");
	}
	
	/**
	 * Altera a renda do eleitor no questionário
	 * @param renda  a renda do eleitor
	 * @exception IOException  Gera uma exceção caso a renda não tenha sido escolhida
	 */
	public void setRenda(Renda renda) throws IOException {
		if (renda != Renda.NENHUM)
			this.renda = renda;
		else
			throw new IOException("A renda familiar do eleitor não foi selecionada.");
	}
	
	/**
	 * Altera o sexo do eleitor no questionário
	 * @param sexo  o sexo do eleitor
	 * @exception IOException  Gera uma exceção caso o sexo não tenha sido escolhida
	 */
	public void setSexo(Sexo sexo) throws IOException {
		if (sexo != Sexo.NENHUM)
			this.sexo = sexo;
		else
			throw new IOException("O sexo do eleitor não foi selecionado.");
	}
	
	/**
	 * Returna uma representação em uma cadeia de caracteres do questionário e de seus campos.
	 * @return a representação em uma cadeia de caracteres
	 */
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
