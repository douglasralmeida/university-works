package entidades;

import java.util.ArrayList;

public class Servicos {
	private ArrayList<Servico> itens;
	
	public Servicos() {
		itens = new ArrayList<Servico>();
	}

	public void adicionar(Servico servico) {
		itens.add(servico);
	}
		
	public Servico getServico(int index) {
		return itens.get(index);
	}
	
	public int getSize() {
		return itens.size();
	}
	
	public void remover(int index) {
		itens.remove(index);
	}
	
	public void setServico(int index, Servico servico) {
		itens.set(index, servico);
	}
}
