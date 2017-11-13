/**
 * 
 */
package PesquisaEleitoral;

/**
 * Enumeração para a renda do eleitor 
 */
public enum Renda {
	NENHUM(""),
	MENOSDE3SM("Menos de 3 salários mínimos"),
	ENTRE3E5SM("Entre 3 e 5 salários mínimos"),
	ACIMADE5SM("Mais de 5 salários mínimos");
	
	private String descricao;
	
	private Renda(String descricao) {
		this.descricao = descricao;
	};
	
	public static final int getLength() {
		return values().length;
	}
	
	public String toString() {
		return descricao;
	}	
}
