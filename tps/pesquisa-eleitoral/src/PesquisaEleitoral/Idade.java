/**
 * 
 */
package PesquisaEleitoral;

/**
 * Enumeração para a idade do eleitor 
 */
public enum Idade {
	NENHUM(""),
	MENOSDE20("Menos de 20 anos"),
	ENTRE20E30("Entre 20 e 30 anos"),
	ENTRE30E40("Entre 30 e 40 anos"),
	ENTRE40E50("Entre 40 e 50 anos"),
	MAISDE50("Mais de 50 anos");
	
	private String descricao;
	
	private Idade(String descricao) {
		this.descricao = descricao;
	}
	
	public static final int getLength() {
		return values().length;
	}
	
	public String toString() {
		return descricao;
	}	
}
