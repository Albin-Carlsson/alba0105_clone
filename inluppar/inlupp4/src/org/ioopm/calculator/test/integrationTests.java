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
    //vars kommer vara tom eftersom ans behandlas i Calculator klassen
    Constant c1 = new Constant(10);
    Constant c2 = new Constant(5);
    Constant c3= new Constant(15);
    Constant c4 = new Constant(2);
    Constant piii = new Constant(Constants.namedConstants.get("pi"));
    Constant pi2= new Constant(Constants.namedConstants.get("pi")/2);

    Addition a1 = new Addition(c2, c1); //15
    Addition a2 = new Addition(c2, c1); //15
    Subtraction sub1 = new Subtraction(c1, c2); // 5
    Subtraction sub2 = new Subtraction(c1, c2); // 5

    Variable v = new Variable("x");
    Variable y= new Variable("y");
    NamedConstant nconst= new NamedConstant("n", 3);
    Assignment assignment = new Assignment(v, c1); // x = 10 kommer att faila
    Assignment assignG= new Assignment(c1, v);  //10 = x


    Multiplication m1 = new Multiplication(c1, v); // 10 * x
    Multiplication m2 = new Multiplication(c1, c2); // 10 * 5
    Multiplication m22 = new Multiplication(c1, c2); // 10 * 5
    Division d = new Division(c1, c2); // 10/5 2
    Subtraction sub3 = new Subtraction(d, m2); // 10/5 - 10*5
    Addition treeAdd = new Addition(sub3, v); // 10/5 + 10*5 + x
    Multiplication treeMult = new Multiplication(treeAdd, c3); // (10/5 + 10*5 + x) * 7


    Negation n1 = new Negation(m2); // -(10 * 5)
    Exp e = new Exp(c2); // e^5
    Exp ex = new Exp(v); // e^x
    Cos cos = new Cos(pi2);// nästan noll
    Cos cosx = new Cos(v); // cos(x)
    Sin sin = new Sin(piii); // nästan noll
    Sin sinx = new Sin(v); // sin(x)
    Log log = new Log(c1);// 1
    Log logx = new Log(v);// log(x)

    Vars v22 = new Vars();
    Quit q = new Quit();
    Clear clear = new Clear();
    Environment vars = new Environment();


    public void testEvaluating(SymbolicExpression expected, SymbolicExpression actual, Environment vars) {
        String expectedString = expected.toString();
        try {
            SymbolicExpression r1 = expected.eval(vars);
            SymbolicExpression r2 = actual.eval(vars);

            assertTrue(r1.equals(r2));
            System.out.println("Passed: " + expectedString + ", value: " + r2 + ", vars: " + vars);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    @BeforeAll
    static void initAll() {

    }


    @Test
    void additionEvalEquals(){
        SymbolicExpression addActual = a1;  //10 +5
        Addition addExpected = a1;  //10 +5
        SymbolicExpression addx = new Addition(c1,v); //10 + x
        Addition checkx = new Addition(c1,v);

        testEvaluating(addExpected,addActual,vars); //actual addition
        testEvaluating(checkx, addx, vars);  //with a variable
    }

    @Test
    void subtractionEquals(){
        SymbolicExpression subActual = sub1;
        Subtraction subExpected = sub1;
        SymbolicExpression subx = new Subtraction(c1, v);
        Subtraction ss = new Subtraction(c1, v);

        testEvaluating(subExpected, subActual, vars);
        testEvaluating(subx, ss, vars);
    }




    @Test
    void multiplicationEvalEquals(){
        SymbolicExpression multActual = m2;  //10 +5
        Multiplication addExpected = m22;  //10 +5
        SymbolicExpression addx = new Addition(c1,v); //10 + x
        Addition checkx = new Addition(c1,v);

        testEvaluating(addExpected,multActual,vars); //actual multiplication
        testEvaluating(checkx, addx, vars);  //with a variable
    }

    @Test
    void divisionEvalEquals(){
        SymbolicExpression divActual = d;  //10/5
        Division  divExpected = d;  //10 +5
        SymbolicExpression divxActual = new Division(c1,v); //10 / x
        Division divxExpected = new Division(c1,v);

        testEvaluating(divActual, divExpected, vars); //actual division
        testEvaluating(divxActual, divxExpected, vars);  //with a variable
    }

    @Test
    void negationEvalEquals(){
        SymbolicExpression negActual = n1; //-(10 * 5)
        Negation negExpected = n1;
        SymbolicExpression negxA = new Negation(new Addition(c1,v)); //- (10 + x)
        Negation negxE = new Negation(new Addition(c1,v));

        testEvaluating(negExpected,negActual,vars); //actual addition
        testEvaluating(negxA, negxE, vars);  //with a variable
    }

    @Test
    void variablesEvalEquals(){
        SymbolicExpression varAddActual= new Addition(v,y); //x+y
        Addition varAddExpected= new Addition(v,y);

        SymbolicExpression nConstActual= new Addition(nconst, y); //n +y, n=3
        Addition nConstExpected= new Addition(nconst, y);

        testEvaluating(nConstActual, nConstExpected, vars);
        testEvaluating(varAddActual, varAddExpected, vars);
    }

    @Test
    void unaryEvalEquals(){
        SymbolicExpression sinActual = sin;
        SymbolicExpression sinxActual = sinx;
        SymbolicExpression cosActual = cos;
        SymbolicExpression cosxActual = cosx;
        SymbolicExpression logActual = log;
        SymbolicExpression logxActual = logx;
        SymbolicExpression expActual = e;
        SymbolicExpression eActual = ex;

        testEvaluating(sinActual, sin, vars);
        testEvaluating(sinxActual, sinx, vars);

        testEvaluating(cosActual, cos, vars);
        testEvaluating(cosxActual, cosx, vars);

        testEvaluating(logActual, log, vars);
        testEvaluating(logxActual, logx, vars);

        testEvaluating(expActual, e, vars);
        testEvaluating(eActual, ex, vars);

    }

    @Test
    void assignEvalEqual(){
        SymbolicExpression assignWrong= assignment;
        try {
            SymbolicExpression fail= assignWrong.eval(vars);
        }
        catch (IllegalAssignmentException e){
            assertTrue(true);
            System.out.println(assignWrong.toString() + " is an illegal assignment.");
        }

        SymbolicExpression assignGood= assignG;
        Assignment assignExpected= assignG;

        testEvaluating(assignExpected, assignGood, vars);
    }


    @AfterEach
    void tearDown() {
    }

    @AfterAll
    static void tearDownAll() {
    }

}