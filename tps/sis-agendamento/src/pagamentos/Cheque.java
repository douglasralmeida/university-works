package pagamentos;

import java.util.Random;

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
		Random r = new Random();		
		int x = r.nextInt(2);
		
		return (x == 0);
	}
}
