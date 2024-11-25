package org.ioopm.calculator.ast;


/**
 * Basic implementation of Symbolic Calculator, which is using a parser
 * to create an AST, which is evaluated to an expression later on.
 * Authors: Emilio Funes, Annika Kuusrainen, Alexandra Barbu
 * Date: 21 November 2024
 */
public abstract class SymbolicExpression {

    protected int priority = 100;

    /**
     * Controls if the SymbolicExpression is a constant
     * @return boolean
     */
    public boolean isConstant() {
        return false;
    }

    /**
     * Controls if the SymbolicExpression is a command (vars, quit, clear)
     * @return boolean, true if it is, false otherwise
     */
    public boolean isCommand() {
        return false;
    }

    /**
     * Retrieves the name of a SymbolicExpression
     * @return String, the name
     */
    public String getName() {
        throw new RuntimeException("getName() called on expression with no operator");
    }

    /**
     * Retrieves the priority field of a SymbolicExpression
     * @return int, the priority
     */
    public int getPriority() {
        return priority;
    }

    /**
     * Retrieves the value of a SymbolicExpression
     * @return double, the value retrieved
     */
    public double getValue() {
        throw new RuntimeException("getValue() called on expression with no value");
    }

    /**
     * Converts object to string
     * @return String with the object's name
     */
    public String toString() {
        return getName();
    }

    /**
     * Reduces SymbolicExpression as much as possible
     * @param vars Environment with saved variables
     * @return SymbolicExpression, the result of the evaluation
     * @throws IllegalAssignmentException
     */
    public abstract SymbolicExpression eval(Environment vars) throws IllegalAssignmentException;
}
