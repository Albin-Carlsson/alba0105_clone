package org.ioopm.calculator;

import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;

import java.util.Scanner;


public class Calculator {

    public static void main(String[] args) {
        Calculator calculator = new Calculator();
        calculator.run();
    }

    private void run() {
        Scanner scanner = new Scanner(System.in);
        Environment vars = new Environment();
        CalculatorParser calculatorParser = new CalculatorParser();

        int expressions = 0;
        int evals = 0;
        int fullEvals = 0;

        System.out.println("Welcome to Symbolic Calculator!");

        while (true) {
            // get input
            System.out.print("Enter expression: ");
            String input = scanner.nextLine();

            try {
                // parse
                SymbolicExpression result = calculatorParser.parse(input, vars);

                if (result.isCommand()) {
                    ((Command) result).execute(vars, expressions, evals, fullEvals);
                } else {
                    // eval
                    result = result.eval(vars);

                    expressions++;
                    evals++;
                    if (result instanceof Constant) {
                        fullEvals++;
                    }

                    vars.put(new Variable("ans"), result);
                    // print
                    System.out.println(result);
                }
            } catch (IllegalAssignmentException | SyntaxErrorException | IllegalExpressionException e) {
                System.out.println(e.getMessage());
            } catch (Exception e) {
                System.out.println("Could not parse expression!");
                // System.out.println(e.getMessage());
            }
            System.out.println();
        }
    }

}
