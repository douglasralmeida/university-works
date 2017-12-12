package sistema;

import pessoa.Cliente;

public class Buscador {

	public Buscador() {
		// TODO Auto-generated constructor stub
	}
	
	public static Cliente PesquisarClientes(String consulta) throws Exception {
		int i;
		int max;
		Cliente clienteEncontrado = null;
		
		if (consulta.isEmpty()) {
			new Exception("O número do CPF não foi informado");
			return null;
		}
		
		max = Aplicacao.pessoas.getSize();
		for (i = 0; i < max; i++) {
			if (Aplicacao.pessoas.getPessoa(i).getCpf().equals(consulta))
				clienteEncontrado = (Cliente) Aplicacao.pessoas.getPessoa(i);
		}
		return clienteEncontrado;
	}
}
