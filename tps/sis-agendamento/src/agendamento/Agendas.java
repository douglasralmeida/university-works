package agendamento;

import java.util.ArrayList;

public class Agendas {
	private ArrayList<Agenda> itens;
	
	public Agendas() {
		itens = new ArrayList<Agenda>();
	}

	public void adicionar(Agenda agendas) {
		itens.add(agendas);
	}
		
	public Agenda getAgenda(int index) {
		return itens.get(index);
	}
	
	public int getSize() {
		return itens.size();
	}
	
	public void remover(int index) {
		itens.remove(index);
	}
	
	public void setAgenda(int index, Agenda agenda) {
		itens.set(index, agenda);
	}
}
