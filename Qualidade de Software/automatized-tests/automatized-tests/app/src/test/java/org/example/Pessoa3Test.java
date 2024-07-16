package br.ufsm;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;

 

	@Tag("development")
	public class Pessoa3Test
	{
	    @Test
	    @Tag("development")	    
	    void testCaseA() {
	    	System.out.println("development");
	    }
	
	    @Test
	    @Tag("production")	    
	    void testCaseB() {
	    	System.out.println("production");
	    }
	    

   }
