package org.ioopm.calculator;

import org.ioopm.calculator.ast.*;

public class Test {

    public static void main(String[] args) {
        Test test = new Test();
        test.runTests();
    }

    void runTests() {
        testPrint1();
        testPrint2();

        testPriority1();
        testPriority2();
        testPriority3();
        testPriority4();
        testPriority5();
        testPriority6();

        testEval1(new Environment());
        testEval21(new Environment());
        testEval22(new Environment());

        testEval0(new Environment(), 2);
        testEval0(new Environment(), 0.5);
        testEval0(new Environment(), 10);

    }

    private void testEval0(Environment vars, double value) {
        vars.put(new Variable("x"), new Constant(value));

        Constant c1 = new Constant(10);
        Variable v = new Variable("x");
        Multiplication m1 = new Multiplication(c1, v);

        Negation n1 = new Negation(m1);

        Constant c2 = new Constant(50);
        Addition a1 = new Addition(c2, n1);

        SymbolicExpression se1 = a1;

        SymbolicExpression se2 = vars.get(new Variable("x"));
        Multiplication m2 = new Multiplication(c1, se2);
        Negation n2 = new Negation(m2);
        Constant c3 = new Constant(50);
        Addition a2 = new Addition(c3, n2);

        SymbolicExpression se3 = a2;
        testEvaluating(se1, se3, vars);
    }

    private void testEval1(Environment vars) {
        SymbolicExpression a = new Addition(new Constant(5), new Constant(37));
        SymbolicExpression b = new Constant(42);
        testEvaluating(b, a, vars);
    }

    private void testEval21(Environment vars) {
        Constant c1 = new Constant(5);
        Constant c2 = new Constant(2);
        Multiplication m = new Multiplication(c1, c2);

        Negation n = new Negation(m);

        Constant c3 = new Constant(20);
        Addition a = new Addition(c3, n);

        Constant c4 = new Constant(10);
        Division d = new Division(a, c4);

        Log l = new Log(d);

        SymbolicExpression se1 = l;
        SymbolicExpression se2 = new Constant(0);
        testEvaluating(se2, se1, vars);
    }

    private void testEval22(Environment vars) {
        Constant c1 = new Constant(5);
        Constant c2 = new Constant(2);
        Multiplication m = new Multiplication(c1, c2);

        Negation n = new Negation(m);

        Constant c3 = new Constant(20);
        Addition a = new Addition(c3, n);

        Constant c4 = new Constant(10);
        Division d = new Division(a, c4);

        Log l = new Log(d);

        SymbolicExpression se1 = l;
        SymbolicExpression se2 = new Constant(0);
        testEvaluating(se1, se2, vars);
    }

    private void testPriority1() {
        Constant c1 = new Constant(5);
        Constant c2 = new Constant(2);
        Addition a1 = new Addition(c1, c2);

        Constant c3 = new Constant(10);
        Constant c4 = new Constant(220);
        Addition a2 = new Addition(c3, c4);

        Multiplication m = new Multiplication(a1, a2);

        testPrinting("(5 + 2) * (10 + 220)", m);
    }

    private void testPriority2() {
        Constant c1 = new Constant(5);
        Constant c2 = new Constant(2);
        Addition a = new Addition(c1, c2);

        Constant c3 = new Constant(10);
        Constant c4 = new Constant(220);
        Division d = new Division(c3, c4);

        Multiplication m = new Multiplication(a, d);

        testPrinting("(5 + 2) * 10 / 220", m);
    }

    private void testPriority3() {
        Constant c1 = new Constant(5);
        Constant c2 = new Constant(2);
        Multiplication m1 = new Multiplication(c1, c2);

        Constant c3 = new Constant(10);
        Constant c4 = new Constant(220);
        Division d = new Division(c3, c4);

        Multiplication m2 = new Multiplication(m1, d);

        testPrinting("5 * 2 * 10 / 220", m2);
    }

    private void testPriority4() {
        Constant c1 = new Constant(5);
        Constant c2 = new Constant(2);
        Addition a1 = new Addition(c1, c2);

        Constant c3 = new Constant(10);
        Multiplication m = new Multiplication(c3, a1);

        Constant c4 = new Constant(210);
        Division d = new Division(m, c4);

        testPrinting("10 * (5 + 2) / 210", d);
    }

    private void testPriority5() {
        Constant c1 = new Constant(5);
        Constant c2 = new Constant(2);
        Multiplication a1 = new Multiplication(c1, c2);

        Constant c3 = new Constant(10);
        Addition m = new Addition(c3, a1);

        Constant c4 = new Constant(210);
        Division d = new Division(m, c4);

        testPrinting("(10 + 5 * 2) / 210", d);
    }

    private void testPriority6() {
        Constant c1 = new Constant(5);
        Constant c2 = new Constant(2);
        Multiplication m = new Multiplication(c1, c2);

        Negation n = new Negation(m);

        Constant c3 = new Constant(10);
        Addition a = new Addition(c3, n);

        Constant c4 = new Constant(210);
        Division d = new Division(a, c4);

        testPrinting("(10 + -(5 * 2)) / 210", d);
    }

    void testPrint1() {
        Constant c1 = new Constant(5);
        // Constant c2 = new Constant(2);
        Negation c2 = new Negation(new Constant(2));
        Variable v = new Variable("x");
        Addition a = new Addition(c1, v);
        Multiplication m = new Multiplication(a, c2);

        testPrinting("(5 + x) * -2", m);

        // System.out.println("\nBorde vara 2: " + c2.getValue());
    }

    void testPrint2() {
        Constant c1 = new Constant(5);
        Variable v = new Variable("x");
        Addition a = new Addition(c1, v);

        Cos c = new Cos(a);

        Constant c2 = new Constant(2);
        Constant c3 = new Constant(3);
        Multiplication m = new Multiplication(c2, c3);

        Sin s = new Sin(m);
        Negation n = new Negation(s);

        Multiplication m2 = new Multiplication(c, n);

        Log l = new Log(m2);

        testPrinting("log(cos(5 + x) * -sin(2 * 3))", l);
    }

    public static void testPrinting(String expected, SymbolicExpression e) {
        if (expected.equals(e.toString())) {
            System.out.println("Passed: " + e);
        } else {
            System.out.println("Error: expected '" + expected + "' but got '" + e + "'");
        }
    }

    public void testEvaluating(SymbolicExpression expected, SymbolicExpression se, Environment vars) {
        String expectedString = expected.toString();
        try {
            SymbolicExpression r1 = expected.eval(vars);
            SymbolicExpression r2 = se.eval(vars);

            if (r1.equals(r2)) {
                System.out.println("Passed: " + expectedString + ", value: " + r2 + ", vars: " + vars);
            } else {
                System.out.println("Error: expected '" + expected + "' but got '" + r2 + "'");
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}

