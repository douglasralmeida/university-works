package pessoa;

import java.util.ArrayList;

public class Pessoas {
	private ArrayList<Pessoa> itens;
	
	public Pessoas() {
		itens = new ArrayList<Pessoa>();
	}

	public void adicionar(Pessoa pessoa) {
		itens.add(pessoa);
	}
		
	public Pessoa getPessoa(int index) {
		return itens.get(index);
	}
	
	public int getSize() {
		return itens.size();
	}
	
	public void remover(int index) {
		itens.remove(index);
	}
	
	public void setPessoa(int index, Pessoa pessoa) {
		itens.set(index, pessoa);
	}
}
