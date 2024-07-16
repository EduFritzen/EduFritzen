package br.ufsm.eduardo;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class NumberTest {

	@BeforeEach
	void beforeEachMethod() {
		System.out.println("Executando o beforeEachMethod");
	}
	
	@AfterEach
	void afterEachMethod() {
		System.out.println("Executando o afterEachMethod");
	}
	
	@Test
	void test() {
		Number number = new Number(1);
		assertEquals(false, number.isEven());
	}
	
	@Test
	void test2() {
		Number number = new Number(1);
		assertEquals(true, number.isOdd());
	}
	
	@Test
	void negativeNumberTest() {
		Number number = new Number(-1);
		assertEquals(true, number.isOdd());
		assertEquals(false, number.isEven());
	}	

}
