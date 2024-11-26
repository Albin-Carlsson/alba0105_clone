import static org.junit.jupiter.api.Assertions.*;

import org.ioopm.calculator.ast.*;
import org.junit.Assert;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;

public class integrationTests{
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
    Division d = new Division(c1, c2); // 10/5 2
    Subtraction sub3 = new Subtraction(d, m2); // 10/5 - 10*5
    Addition treeAdd = new Addition(sub3, v); // 10/5 + 10*5 + x
    Multiplication treeMult = new Multiplication(treeAdd, c3); // (10/5 + 10*5 + x) * 7

    Negation n1 = new Negation(m1); // -(10 * x)
    Exp e = new Exp(c2); // e^5
    Cos cos = new Cos(piii); // -1
    Sin sin = new Sin(piii); // 0
    Log log = new Log(c1); // 1

    Vars vars = new Vars();
    Quit q = new Quit();
    Clear clear = new Clear();
    Environment empty = new Environment();

    @BeforeAll
    static void initAll() {

    }


    @Test
    additionEvalEquals(){

    }

    @Test
    @Test
    @Test


    @AfterEach
    void tearDown() {
    }

    @AfterAll
    static void tearDownAll() {
    }

}