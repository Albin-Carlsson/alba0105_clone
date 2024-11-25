package org.ioopm.calculator.ast;

public class Assignment extends Binary {

    public Assignment(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
        priority = 0;
    }

    public String getName() {
        return "=";
    }

    public SymbolicExpression eval(Environment vars) throws IllegalAssignmentException {
        if (rhs.isConstant()) {
            throw new IllegalAssignmentException("Error: cannot redefine named constant '" + rhs.getName() + "'");
        }
        lhs = lhs.eval(vars);
        vars.put((Variable) rhs, lhs);
        if (lhs.isConstant()) {
            return new Assignment(new Constant(lhs.getValue()), rhs);
        }
        return this;
    }
}
