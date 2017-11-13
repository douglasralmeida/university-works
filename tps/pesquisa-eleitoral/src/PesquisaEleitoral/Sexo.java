/**
 * 
 */
package PesquisaEleitoral;

/**
 * Enumeração para o sexo do eleitor 
 */
public enum Sexo {
	NENHUM(""),
	FEMININO("Feminino"),
	MASCULINO("Masculino");
	
	private String descricao;
	
	private Sexo(String descricao) {
		this.descricao = descricao;
	};
	
	public static final int getLength() {
		return values().length;
	}
	
	public String toString() {
		return descricao;
	}
}
