package pagamentos;

public class Convenio implements Pagamento {

	String nome;
	
	public Convenio() {
		nome = "Convênio";
	}
	
	@Override
	public String toString() {
		return this.nome;
	}
	
	@Override
	public boolean autorizar() {
		return false;
	}
	
}
