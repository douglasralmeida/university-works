package pagamentos;

import java.util.ArrayList;

public class Pagamentos {
	ArrayList<Pagamento> itens = new ArrayList<Pagamento>();

	public Pagamentos() {
		
		itens.add(new Cartao());
		itens.add(new Cheque());
		itens.add(new Convenio());
		itens.add(new Cortesia());
		itens.add(new Dinheiro());
	}

	public int getSize() {
		return itens.size();
	}

	public Pagamento getPagamento(int i) {
		return itens.get(i);
	}

}
