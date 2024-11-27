package org.ioopm.calculator.ast;

public class Sin extends Unary {

    public Sin(SymbolicExpression child) {
        super(child);
    }

    public String getName() {
        return "Sin";
    }

    public SymbolicExpression eval(Environment vars) throws IllegalAssignmentException {
        child = child.eval(vars);
        if (child.isConstant()) {
            return new Constant(Math.sin(child.getValue()));
        }
        return this;
    }
}
