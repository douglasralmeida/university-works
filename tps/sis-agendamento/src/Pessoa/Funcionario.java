package pessoa;

public class Funcionario extends Pessoa {
	int matricula;
	
	public Funcionario(int matricula) {
		this.matricula = matricula;
	}
	
	public int getMatricula() {
		return this.matricula;
	}
}
