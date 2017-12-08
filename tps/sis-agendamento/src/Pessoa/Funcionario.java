package Pessoa;

public class Funcionario extends Core {
	int matricula;
	
	public Funcionario(int matricula) {
		this.matricula = matricula;
	}
	
	public int getMatricula() {
		return this.matricula;
	}
}
