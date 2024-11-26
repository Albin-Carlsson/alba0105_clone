import static org.junit.jupiter.api.Assertions.*;

import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Test;

import java.io.IOException;

public class ParserTests {
    Constant c5 = new Constant(5);
    Constant c10 = new Constant(10);
    Constant piii = new Constant(Constants.namedConstants.get("pi"));
    Constant pi2= new Constant(Constants.namedConstants.get("pi")/2);


    Variable varx = new Variable("x");
    Variable vary = new Variable("y");

    NamedConstant nconst = new NamedConstant("n", 3);

    Addition add1 = new Addition(c5, c10);

    Multiplication mult1 = new Multiplication(c5, c10); //5 *10
    Multiplication mult2 = new Multiplication(c5, varx); //5 * x

    Negation n1 = new Negation(mult1); // -(5 * 10)
    Exp e = new Exp(c5); // e^5
    Exp ex = new Exp(varx); // e^x
    Cos cos = new Cos(pi2);// nästan noll
    Cos cosx = new Cos(varx); // cos(x)
    Sin sin = new Sin(piii); // nästan noll
    Sin sinx = new Sin(varx); // sin(x)
    Log log = new Log(c10);// 1
    Log logx = new Log(varx);// log(x)

    Vars v22 = new Vars();
    Quit q = new Quit();
    Clear clear = new Clear();
    Environment vars = new Environment();
    CalculatorParser calculatorParser = new CalculatorParser();


    @Test
    void parserConstant(){
        String orgConst= c10.toString(); //"10"
        try{
            SymbolicExpression parsedConst =  calculatorParser.parse(orgConst, vars);

            assertTrue(parsedConst.toString().equals(orgConst));

        } catch (IOException e){
            System.out.println("Nu blev de nå galet");
        }

    }


    @AfterEach
    void tearDown() {
    }

    @AfterAll
    static void tearDownAll() {
    }


}
