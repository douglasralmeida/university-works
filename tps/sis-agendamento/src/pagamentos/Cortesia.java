package pagamentos;

public class Cortesia implements Pagamento {

	int contador = 0;
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
		contador++;
		if (contador == 5) {
			contador = 0;
			return false;
		}		
		return true;
	}
	
}
