package br.ufsm;

import static org.junit.Assert.assertEquals;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.TestMethodOrder; 
import org.junit.jupiter.api.MethodOrderer.OrderAnnotation;
 

@TestMethodOrder(OrderAnnotation.class)
public class OrderAnnotationUnitTest {
    private static StringBuilder output = new StringBuilder("");
    
    @Test
    @Order(1)    
    void firstTest() {
        output.append("a");
    }
    
    @Test
    @Order(2)    
    void secondTest() {
        output.append("b");
    }
 
    @Test
    @Order(3)    
    void thirdTest() {
        output.append("c");
    }
 
    @AfterAll
    public static void assertOutput() {
        assertEquals("abc", output.toString());
    }
}