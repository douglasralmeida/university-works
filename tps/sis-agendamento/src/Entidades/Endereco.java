package Entidades;
import Excecoes.ArgumentoInvalidoException;

public class Endereco {
	private String logradouro;
	private String complemento;
	private String bairro;
	private String cidade;
	private String estado;
	private String cep;
	
	public String getLogradouro() {
		return logradouro;
	}
	
	public String getComplemento() {
		return complemento;
	}
	
	public String getBairro() {
		return bairro;
	}
	
	public String getCidade() {
		return cidade;
	}
	
	public String getEstado() {
		return estado;
	}
	
	public String getCep() {
		return cep;
	}
	
	public void setLogradouro(String logradouro) throws ArgumentoInvalidoException {
		ArgumentoInvalidoException.throwSeNuloOuBranco(logradouro, "O logradouro não foi informado.");
		this.logradouro = logradouro;
	}

	public void setComplemento(String complemento) {
		this.complemento = complemento;
	}

	public void setBairro(String bairro) throws ArgumentoInvalidoException {
		ArgumentoInvalidoException.throwSeNuloOuBranco(bairro, "O bairro não foi informado.");
		this.bairro = bairro;
	}

	public void setCidade(String cidade) throws ArgumentoInvalidoException {
		ArgumentoInvalidoException.throwSeNuloOuBranco(cidade, "A cidade não foi informada.");
		this.cidade = cidade;
	}

	public void setEstado(String estado) throws ArgumentoInvalidoException {
		ArgumentoInvalidoException.throwSeNuloOuBranco(estado, "O estado não foi informado.");
		this.estado = estado;
	}

	public void setCep(String cep) throws ArgumentoInvalidoException {
		ArgumentoInvalidoException.throwSeNuloOuBranco(cep, "O CEP não foi informado.");
		ArgumentoInvalidoException.throwSeNaoENumero(cep, "O CEP informado não é numérico");
		if (cep.length() != 8)
			new ArgumentoInvalidoException("O CEP informado é inválido");
		this.cep = cep;
	}
}