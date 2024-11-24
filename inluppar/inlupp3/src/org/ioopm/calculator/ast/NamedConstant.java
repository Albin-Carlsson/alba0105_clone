package org.ioopm.calculator.ast;

public class NamedConstant extends Atom {

    private final String identifier;
    private final double value;

    public NamedConstant(String identifier, double value) {
        this.identifier = identifier;
        this.value = value;
    }

    public boolean isConstant() {
        return true;
    }

    public double getValue() {
        return value;
    }

    public String getName() {
        return String.valueOf(this.value);
    }

    public SymbolicExpression eval(Environment vars) {
        return this;
    }
}
