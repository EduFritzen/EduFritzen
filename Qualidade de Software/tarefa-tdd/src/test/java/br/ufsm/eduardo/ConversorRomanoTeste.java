package br.ufsm.eduardo;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class ConversorRomanoTeste {

	@Test
	void converteOSimboloI() {
		ConversorRomano conversor = new ConversorRomano();
		int obtido = conversor.converte("I");
		assertEquals(1, obtido);
	}
	
	@Test
	void converteOSimboloV() {
		ConversorRomano conversor = new ConversorRomano();
		int obtido = conversor.converte("V");
		assertEquals(5, obtido);
	}
	
	@Test
	void converteOSimboloC() {
		ConversorRomano conversor = new ConversorRomano();
		int obtido = conversor.converte("C");
		assertEquals(100, obtido);
	}
	
	@Test
	void converteOSimboloII() {
		ConversorRomano conversor = new ConversorRomano();
		int obtido = conversor.converte("II");
		assertEquals(2, obtido);
	}
	
	@Test
	void converteOSimboloXXII() {
		ConversorRomano conversor = new ConversorRomano();
		int obtido = conversor.converte("XXII");
		assertEquals(22, obtido);
	}
	
	@Test
	void converteOSimboloIV() {
		ConversorRomano conversor = new ConversorRomano();
		int obtido = conversor.converte("IV");
		assertEquals(4, obtido);
	}

}
