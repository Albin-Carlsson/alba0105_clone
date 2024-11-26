package org.ioopm.calculator.test;

import static org.junit.Assert.*;

import org.ioopm.calculator.ast.*;
import org.junit.Assert;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;

public class unitTestsAST {

    Constant c1 = new Constant(10);
    Constant c2 = new Constant(5);
    Constant c3= new Constant(15);
    Constant piii = new Constant(Constants.namedConstants.get("pi"));

    Addition a1 = new Addition(c2, c1); //15
    Addition a2 = new Addition(c2, c1); //15
    Subtraction sub1 = new Subtraction(c1, c2); // 5
    Subtraction sub2 = new Subtraction(c1, c2); // 5

    Variable v = new Variable("x");
    Assignment assignment = new Assignment(v, c1); // x = 10 kommer att faila


    Multiplication m1 = new Multiplication(c1, v); // 10 * x
    Multiplication m2 = new Multiplication(c1, c2); // 10 * 5
    Multiplication m22 = new Multiplication(c1, c2); // 10 * 5
    Division d = new Division(c1, c2); // 2

    Negation n1 = new Negation(m1); // -(10 * x)
    Exp e = new Exp(c2); // e^5
    Cos cos = new Cos(piii); // -1
    Sin sin = new Sin(piii); // 0
    Log log = new Log(c1); // 1

    Vars vars = new Vars();
    Quit q = new Quit();
    Clear clear = new Clear();

//    int expressions = 0;
//    int evals = 0;
//    int fullEvals = 0;


    @BeforeAll
    static void initAll() {
    
    }

    @Test
    void additionTest() {
        assertTrue(a1.equals(a2));
        assertFalse(a1.isConstant());
        assertEquals(a1.getName(), "+");
        assertEquals(a1.getPriority(),50 );
        assertEquals(a1.toString(), "5 + 10");
//        Environment vars=new Environment();
//        assertEquals(a1.eval(a1), c3);

    }

    @Test
    void subtractionTest(){
        assertTrue(sub1.equals(sub2));
        assertTrue(sub2.equals(sub1));
        assertFalse(sub2.isConstant());
        assertEquals(sub1.getName(), "-");
        assertEquals(sub1.getPriority(), 50);
        //assertEquals(sub1.getValue(), 5);
        assertEquals(sub1.toString(), "10 - 5");
   }

    @Test
    void constantTest(){
        assertTrue(c1.isConstant());
        assertTrue(c2.isConstant());
        assertFalse(c1.equals(c2));
        assertEquals(c1.getPriority(), 100);

    }

     @Test
     void multiplicationTest(){
        assertFalse(m2.isConstant());
        assertEquals(m2.getName(), "*");
        assertFalse(m2.isCommand());
        assertEquals(m2.getPriority(), 100);
        assertEquals(m2.toString(), "10 * 5");
        assertTrue(m2.equals(m22));
        assertFalse(m2.equals(m1));

     }

    @Test
    void variableTest(){
        assertFalse(v.isConstant());
        assertEquals(v.getName(), "x");
        assertEquals(v.toString(), "x");

    }

    @Test
    void sinTest(){
        assertEquals(sin.getName(), "sin");
        assertEquals(sin.toString(), "sin(" + piii + ")");

    }

    @Test
    void cosTest(){
        assertEquals(cos.getName(), "cos");
        assertEquals(cos.toString(), "cos(" + piii + ")");
    }

    @Test
    void expTest(){
        assertEquals(e.getName(), "exp");
        assertEquals(e.toString(), "exp(" + 5 + ")");
    }

    @Test
    void negationTest(){
        assertEquals(n1.getName(), "-");
        assertEquals(n1.toString(), "-" +"(" + m1 + ")");
    }

    @Test
    void logTest(){
        assertEquals(log.getName(), "log");
        assertEquals(log.toString(), "log(" + 10 + ")");
    }


    @Test
    void commandTest(){
       assertTrue(q.isCommand());
       assertTrue(clear.isCommand());
       assertFalse(q.isConstant());
       assertFalse(clear.isConstant());

        boolean thrown = false;

        try {
            q.getName();
        } catch (RuntimeException e) {
            thrown = true;
        }

        assertTrue(thrown);
    }

    @Test
    void assignTest(){
        assertEquals(assignment.getName(), "=");
        assertEquals(assignment.getPriority(), 0);
        assertFalse(assignment.isConstant());
        assertFalse(assignment.isCommand());
        boolean thrown = false;

        try {
            assignment.getValue();
        } catch (RuntimeException e) {
            thrown = true;
        }

        assertTrue(thrown);
    }

    @AfterEach
    void tearDown() {
    }

    @AfterAll
    static void tearDownAll() {
    }
    
}
