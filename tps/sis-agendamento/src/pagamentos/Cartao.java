package pagamentos;

public class Cartao implements Pagamento {

	String nome;
	
	public Cartao() {
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
