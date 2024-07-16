package br.ufsm.eduardo;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class PersonTest {

	@Test
	void test() {
		Person person = new Person();
		assertEquals("hello", person.hello());
	}

}
