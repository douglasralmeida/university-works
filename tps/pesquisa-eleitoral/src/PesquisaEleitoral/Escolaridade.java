/**
 * 
 */
package PesquisaEleitoral;

/**
 * @author Douglas
 *
 */
public enum Escolaridade {
	NENHUM(""),
	SUPERIOR("Superior"),
	MEDIO("Ens. Médio"),
	FUNDAMENTAL("Ens. Fundamental"),
	NAOESCOLARIZADO("Não escolarizado");
	
	private String descricao;
	
	private Escolaridade(String descricao) {
		this.descricao = descricao;
	};
	
	public static final int getLength() {
		return values().length;
	}
	
	public String toString() {
		return descricao;
	}
}
