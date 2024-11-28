package org.ioopm.calculator.test;

import static org.junit.jupiter.api.Assertions.*;


import org.ioopm.calculator.ast.*;
import org.junit.jupiter.api.*;

public class AstTest {

    @BeforeAll
    static void initAll() {

    }

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



    @BeforeEach
    void init() {
    }

    @Test
    public void additionTest() {
        assertTrue(a1.equals(a2));
        assertFalse(a1.isConstant());
        assertEquals(a1.getName(), "+");
        assertEquals(a1.getPriority(),50 );
        assertEquals(a1.toString(), "5 + 10");
    }

    @Test
    public void subtractionTest(){
        assertTrue(sub1.equals(sub2));
        assertTrue(sub2.equals(sub1));
        assertFalse(sub2.isConstant());
        assertEquals(sub1.getName(), "-");
        assertEquals(sub1.getPriority(), 50);
        //assertEquals(sub1.getValue(), 5);
        assertEquals(sub1.toString(), "10 - 5");
   }

    @Test
    public void constantTest(){
        assertTrue(c1.isConstant());
        assertTrue(c2.isConstant());
        assertFalse(c1.equals(c2));
        assertEquals(c1.getPriority(), 100);

    }

     @Test
     public void multiplicationTest(){
        assertFalse(m2.isConstant());
        assertEquals(m2.getName(), "*");
        assertFalse(m2.isCommand());
        assertEquals(m2.getPriority(), 100);
        assertEquals(m2.toString(), "10 * 5");
        assertTrue(m2.equals(m22));
        assertFalse(m2.equals(m1));

     }

    @Test
    public void variableTest(){
        assertFalse(v.isConstant());
        assertEquals(v.getName(), "x");
        assertEquals(v.toString(), "x");

    }

    @Test
    public void sinTest(){
        assertEquals(sin.getName(), "Sin");
        assertEquals(sin.toString(), "Sin(" + piii + ")");

    }

    @Test
    public void cosTest(){
        assertEquals(cos.getName(), "Cos");
        assertEquals(cos.toString(), "Cos(" + piii + ")");
    }

    @Test
    public void expTest(){
        assertEquals(e.getName(), "Exp");
        assertEquals(e.toString(), "Exp(" + 5 + ")");
    }

    @Test
    public void negationTest(){
        assertEquals(n1.getName(), "-");
        assertEquals(n1.toString(), "-" +"(" + m1 + ")");
    }

    @Test
    public void logTest(){
        assertEquals(log.getName(), "Log");
        assertEquals(log.toString(), "Log(" + 10 + ")");
    }


    @Test
    public void commandTest(){
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
    public void assignTest(){
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
