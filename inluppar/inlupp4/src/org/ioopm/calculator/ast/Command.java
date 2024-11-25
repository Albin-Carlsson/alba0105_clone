package org.ioopm.calculator.ast;

public abstract class Command extends SymbolicExpression {

    public SymbolicExpression eval(Environment vars) {
        throw new RuntimeException("Cannot evaluate command!");
    }

    public boolean isCommand() {
        return true;
    }

    // public abstract void execute(Environment vars, int expressions, int evals, int fullEvals);
    public abstract void execute(Object... args);
}
