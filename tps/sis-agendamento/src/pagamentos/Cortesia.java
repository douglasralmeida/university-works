package pagamentos;

public class Cortesia implements Pagamento {

	String nome;
	
	public Cortesia() {
		nome = "Cortesia";
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
