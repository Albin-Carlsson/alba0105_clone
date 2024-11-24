package org.ioopm.calculator.ast;

public class Multiplication extends Binary {

    public Multiplication(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
    }

    public String getName() {
        return "*";
    }

    public SymbolicExpression eval(Environment vars) throws IllegalAssignmentException {
        lhs = lhs.eval(vars);
        rhs = rhs.eval(vars);
        if (lhs.isConstant() && rhs.isConstant()) {
            return new Constant(lhs.getValue() * rhs.getValue());
        }
        return this;
    }
}

