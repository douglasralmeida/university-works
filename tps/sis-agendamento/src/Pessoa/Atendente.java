package pessoa;

import entidades.Servico;

public class Atendente extends Funcionario {
	private Servico servico;
	
	public Atendente(int matricula, Servico servico) {
		super(matricula);
		
		this.servico = servico;
	}

	public Servico getServico() {
		return this.servico;
	}
}
