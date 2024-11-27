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

    Assignment assignmentInvalid = new Assignment(varx, c10); // x = 10 kommer att faila
    Assignment assignmentValid = new Assignment(c10, varx); // 10 = x

    NamedConstant nconst = new NamedConstant("n", 3);

    Exp e = new Exp(c5); // e^5
    Exp ex = new Exp(varx); // e^x
    Cos cos = new Cos(pi2);// nästan noll
    Cos cosx = new Cos(varx); // cos(x)
    Sin sin = new Sin(piii); // nästan noll
    Sin sinx = new Sin(varx); // sin(x)
    Log log = new Log(c10);// 1
    Log logx = new Log(varx);// log(x)

    Addition add1 = new Addition(c5, c10);
    Addition addx= new Addition(c5, varx); //5 + x
    Addition addPi = new Addition(piii, piii);
    Addition addUnary= new Addition(c5, sin);

    Subtraction sub1 = new Subtraction(c5, c10);
    Subtraction subx= new Subtraction(c5, varx); //5 + x
    Subtraction subPi = new Subtraction(piii, piii);
    Subtraction subUnary= new Subtraction(c5, log);


    Multiplication mult1 = new Multiplication(c5, c10); //5 *10
    Multiplication mult2 = new Multiplication(c5, varx); //5 * x
    Multiplication multUnary = new Multiplication(c5, log); //5 * x

    Division div1 = new Division(c5, c10); //5 *10
    Division divx = new Division(c5, varx); //5 * x
    Division divUnary = new Division(c5, log); //5 * x
    Division divComplex= new Division(c5, add1);

    Negation n1 = new Negation(mult1); // -(5 * 10)
    Negation nx= new Negation(varx);
    Negation nnconst= new Negation(nconst);
    Negation nn= new Negation(nx);

    SymbolicExpression complex= new Addition(new Multiplication(divComplex, n1), subx);
    SymbolicExpression complex2= new Multiplication(new Subtraction(sinx, nx), nnconst);

    Vars v22 = new Vars();
    Quit q = new Quit();
    Clear clear = new Clear();
    Environment vars = new Environment();
    CalculatorParser calculatorParser = new CalculatorParser();

    public void parserTester(SymbolicExpression seOriginal, Environment vars, Boolean toPrint){
        String orgSe = seOriginal.toString();
        try {
            SymbolicExpression parsedSe = calculatorParser.parse(orgSe, vars);
            String parsedStr = parsedSe.toString();
            assertTrue(orgSe.equals(parsedStr));
            if(toPrint){
                System.out.println("Expected: " + orgSe + " actual: " + parsedStr);
            }
        }
        catch( IOException e){
            assertFalse(true);
            System.out.println("IO exception caught in parserTester");
            System.out.println(orgSe);
        }
    }


    @Test
    void parserConstant(){
        parserTester(c5, vars, true);
    }

    @Test
    void parserAssign(){
        parserTester(assignmentValid, vars, true);
        try {
            parserTester(assignmentInvalid, vars, true);
        } catch (SyntaxErrorException e){
            assertTrue(true);
        }
    }

    @Test
    void parserVariable(){
        parserTester(varx, vars, true);
        parserTester(vary, vars, true);
    }

    @Test
    void parserAddition(){
        parserTester(add1, vars, true);
        parserTester(addx, vars, true);
        parserTester(addPi, vars, true);
        parserTester(addUnary, vars,true);

    }

    @Test
    void parserSubtraction(){
        parserTester(sub1, vars, true);
        parserTester(subx, vars, true);
        parserTester(subPi, vars, true);
        parserTester(subUnary, vars, true);
    }


    @Test
    void parserMultiplication(){
        parserTester(mult1, vars, true);
        parserTester(mult2, vars, true);
        parserTester(multUnary, vars, true);
    }

    @Test
    void parserDivision(){
        parserTester(div1, vars, true);
        parserTester(divx, vars, true);
        parserTester(divUnary, vars, true);
    }

//    @Test
//    void parserNegation(){
//        parserTester(n1, vars, true);
//        parserTester(nx, vars, true);
//        parserTester(nnconst, vars, true);
//        parserTester(nn, vars, true);
//    }

    @Test
    void parserComplex(){
        parserTester(complex, vars, true);
//        parserTester(complex2, vars, true);
    }

    @AfterEach
    void tearDown() {
    }

    @AfterAll
    static void tearDownAll() {
    }


}
