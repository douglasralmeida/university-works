package pagamentos;

public class Dinheiro implements Pagamento {

	String nome;
	
	public Dinheiro() {
		nome = "Cartão";
	}
	
	@Override
	public String toString() {
		return this.nome;
	}
	
	@Override
	public boolean autorizar() {
		return true;
	}

}
