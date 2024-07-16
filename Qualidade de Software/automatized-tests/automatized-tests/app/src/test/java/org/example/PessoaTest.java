package br.ufsm;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class PessoaTest {
	
	Pessoa obj1 = new Pessoa(20, "Ana");

	@Test
	void testGetIdade() {
		assertEquals(20, obj1.getIdade());		
	}

	@Test
	void testGetNome() {
		assertEquals("Ana", obj1.getNome());	
	}

}
