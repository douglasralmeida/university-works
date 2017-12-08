package Pessoa;
import java.time.LocalDate;

import Entidades.Endereco;
import Excecoes.ArgumentoInvalidoException;

public class Cliente extends Core{
	private LocalDate dataNascimento;
	private String identidade;
	private Endereco endereco;
	private String telefone;
	
	public Cliente() {
	}

	public LocalDate getDataNascimento() {
		return dataNascimento;
	}
	
	public Endereco getEndereco() {
		return endereco;
	}

	public String getIdentidade() {
		return identidade;
	}

	public String getTelefone() {
		return telefone;
	}
	
	public void setDataNascimento(LocalDate dataNascimento) throws ArgumentoInvalidoException {
		if (dataNascimento.isBefore(LocalDate.of(1900, 1, 1)))
			new ArgumentoInvalidoException("A data de nascimento informada não pode ser menor que 01/01/1900.");
		if (dataNascimento.isAfter(LocalDate.now()))
			new ArgumentoInvalidoException("A data de nascimento informada não pode ser maior que a data de hoje.");
		this.dataNascimento = dataNascimento;
	}

	public void setIdentidade(String identidade) throws ArgumentoInvalidoException {
		ArgumentoInvalidoException.throwSeNuloOuBranco(identidade, "A identidade não foi informada.");
		this.identidade = identidade;
	}

	public void setEndereco(Endereco endereco) {
		this.endereco = endereco;
	}

	public void setTelefone(String telefone) throws ArgumentoInvalidoException {
		ArgumentoInvalidoException.throwSeNuloOuBranco(telefone, "O número de telefone não foi informado.");
		ArgumentoInvalidoException.throwSeNaoENumero(telefone, "O telefone informado não é numérico.");
		if (telefone.length() < 8 || telefone.charAt(0) != '0')
			new ArgumentoInvalidoException("O número de telefone informado é inválido.");
		this.telefone = telefone;
	}

}