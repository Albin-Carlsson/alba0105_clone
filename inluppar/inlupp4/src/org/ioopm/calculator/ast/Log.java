package org.ioopm.calculator.ast;

public class Log extends Unary {

    public Log(SymbolicExpression child) {
        super(child);
    }

    public String getName() {
        return "Log";
    }

    public SymbolicExpression eval(Environment vars) throws IllegalAssignmentException {
        child = child.eval(vars);
        if (child.isConstant()) {
            return new Constant(Math.log(child.getValue()));
        }
        return this;
    }
}
