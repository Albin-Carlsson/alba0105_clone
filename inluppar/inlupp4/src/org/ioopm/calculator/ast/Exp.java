package org.ioopm.calculator.ast;

public class Exp extends Unary {

    public Exp(SymbolicExpression child) {
        super(child);
    }

    public String getName() {
        return "exp";
    }

    public SymbolicExpression eval(Environment vars) throws IllegalAssignmentException {
        child = child.eval(vars);
        if (child.isConstant()) {
            return new Constant(Math.exp(child.getValue()));
        }
        return this;
    }
}
