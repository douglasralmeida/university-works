package testes;
import static org.junit.Assert.assertEquals;

import org.junit.jupiter.api.Test;
import pessoa.Pessoa;

public class PessoaTest {
	
	@Test
	public void testNomeNulo() {
		Pessoa pessoa = new Pessoa();
		try {
			pessoa.setNome(null);
		} catch (Exception ex) {
			assertEquals("OK", ex.getMessage(), "O nome não foi informado.");
		}
	}
	
	@Test
	public void testNomeBranco() {
		Pessoa pessoa = new Pessoa();
		try {
			pessoa.setNome("");
		} catch (Exception ex) {
			assertEquals("OK", ex.getMessage(), "O nome não foi informado.");
		}
	}
	
	@Test
	public void testCpfNulo() {
		Pessoa pessoa = new Pessoa();
		try {
			pessoa.setCpf(null);
		} catch (Exception ex) {
			assertEquals("OK", ex.getMessage(), "O número do CPF não foi informado.");
		}
	}
	
	@Test
	public void testCpfBranco() {
		Pessoa pessoa = new Pessoa();
		try {
			pessoa.setCpf("");
		} catch (Exception ex) {
			assertEquals("OK", ex.getMessage(), "O número do CPF não foi informado.");
		}
	}
	
	@Test
	public void testCpfValido() {
		Pessoa pessoa = new Pessoa();
		pessoa.setCpf("07287584662");
	}
	
	@Test
	public void testCpfComLetras() {
		Pessoa pessoa = new Pessoa();
		try {
			pessoa.setCpf("124a1345");
		} catch (Exception ex) {
			assertEquals("OK", ex.getMessage(), "O CPF informado não é numérico.");
		}
	}
	
	@Test
	public void testCpfInvalido() {
		Pessoa pessoa = new Pessoa();
		try {
			pessoa.setNome("123456789");
		} catch (Exception ex) {
			assertEquals("OK", ex.getMessage(), "O CPF informado é inválido.");
		}
	}
}