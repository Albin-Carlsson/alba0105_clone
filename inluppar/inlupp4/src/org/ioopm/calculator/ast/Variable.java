package org.ioopm.calculator.ast;

public class Variable extends Atom {

    private final String identifier;

    public Variable(String identifier) {
        this.identifier = identifier;
    }

    public String getName() {
        return identifier;
    }

    public String toString() {
        return this.identifier;
    }

    public boolean equals(Object other) {
        if (this == other) {
            return true;
        }
        if (other == null || getClass() != other.getClass()) {
            return false;
        }

        return equals((Variable) other);
    }

    public boolean equals(Variable other) {
        return this.identifier.equals(other.identifier);
    }

    public int hashCode() {
        return identifier.hashCode();
    }

    public SymbolicExpression eval(Environment vars) throws IllegalAssignmentException {
        if (vars.containsKey(this)) {
            return vars.get(this).eval(vars);
        }
        return this;
    }
}