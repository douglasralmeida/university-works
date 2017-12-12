package pagamentos;

public class Cheque implements Pagamento {

	String nome;
	
	public Cheque() {
		nome = "Cheque";
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
