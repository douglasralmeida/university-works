package pagamentos;

import java.util.Random;

public class Convenio implements Pagamento {

	int contador = 0;
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
		contador++;
		if (contador == 10) {
			contador = 0;
			Random r = new Random();		
			int x = r.nextInt(2);
			
			return (x == 0);
		}		
		return true;
	}
	
}
