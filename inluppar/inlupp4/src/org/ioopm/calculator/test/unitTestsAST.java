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
    Constant piii = new Constant(Constants.namedConstants.get("pi"));

    Addition a1 = new Addition(c2, c1);
    Addition a2 = new Addition(c2, c1);
    Subtraction sub1 = new Subtraction(c1, c2);
    Subtraction sub2 = new Subtraction(c1, c2);

    Variable v = new Variable("x");
    Assignment assignment = new Assignment(v, c1); // x = 10

    Multiplication m1 = new Multiplication(c1, v); // 10 * x
    Division d = new Division(c1, c2); // 2

    Negation n1 = new Negation(m1); // -(10 * x)
    Exp e = new Exp(c2); // e^5
    Cos cos = new Cos(piii); // -1
    Sin sin = new Sin(piii); // 0
    Log log = new Log(c1); // 1

    Vars vars = new Vars();
    Quit q = new Quit();
    Clear clear = new Clear();
        

    @BeforeAll
    static void initAll() {
    
    }

    @Test
    void additionTest() {
        assertTrue(a1.equals(a2));
        assertFalse(a1.isConstant());
        assertEquals(a1.getName(), "+");
        assertEquals(a1.getPriority(),0 ); // 50 ?? 

    }

    @Test
    void subtractionTest(){
        assertTrue(sub1.equals(sub2));
        assertTrue(sub2.equals(sub1));
        assertFalse(a2.isConstant());
        assertEquals(sub1.getName(), "-");
        assertEquals(a1.getPriority(), 50);
    }

    @Test
    void constantTest(){
        assertTrue(c1.isConstant());
        assertTrue(c2.isConstant());
        assertFalse(c1.equals(c2));
        assertEquals(c1.getPriority(), 100); // Är en constants prio 100 ?
        
    }

    // @Test
    // void 



    @AfterEach
    void tearDown() {
    }

    @AfterAll
    static void tearDownAll() {
    }
    
}
