package agendamento;

import java.time.LocalTime;
import java.time.format.DateTimeFormatter;

import pessoa.Cliente;

public class Atendimento {
	LocalTime hora;
	Cliente cliente = null;
	
	public Atendimento(LocalTime hora) {
		this.hora = hora;
		this.hora.format(DateTimeFormatter.ISO_LOCAL_TIME);
	}
	
	public boolean estaOcupado() {
		return (this.cliente != null);
	}
	
	public void desmarcar() {
		this.cliente = null;
	}
	
	public void marcar(Cliente cliente) {
		this.cliente = cliente;
	}
	
	public String toString() {
		return hora.toString();
	}

}
