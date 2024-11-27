package org.ioopm.calculator.ast;

public class Cos extends Unary {

    public Cos(SymbolicExpression child) {
        super(child);
    }

    public String getName() {
        return "Cos";
    }

    public SymbolicExpression eval(Environment vars) throws IllegalAssignmentException {
        child = child.eval(vars);
        if (child.isConstant()) {
            return new Constant(Math.cos(child.getValue()));
        }
        return this;
    }
}
