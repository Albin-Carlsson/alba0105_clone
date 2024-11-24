package org.ioopm.calculator.ast;

public class Negation extends Unary {
    public Negation(SymbolicExpression child) {
        super(child);
    }

    public String getName() {
        return "-";
    }

    public String toString() {
        if (child.isConstant() || child instanceof Unary) {
            return getName() + child.toString();
        }
        return getName() + "(" + child.toString() + ")";
    }

    public SymbolicExpression eval(Environment vars) throws IllegalAssignmentException {
        child = child.eval(vars);
        if (child.isConstant()) {
            return new Constant(-child.getValue());
        }
        return this;
    }
}
