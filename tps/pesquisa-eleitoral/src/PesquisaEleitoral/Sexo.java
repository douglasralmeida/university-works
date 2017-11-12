/**
 * 
 */
package PesquisaEleitoral;

/**
 * @author Douglas
 *
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
