package org.ioopm.calculator.ast;

public abstract class Binary extends SymbolicExpression {

    protected SymbolicExpression lhs = null;
    protected SymbolicExpression rhs = null;

    public Binary(SymbolicExpression lhs, SymbolicExpression rhs) {
        this.lhs = lhs;
        this.rhs = rhs;
    }

    public String toString() {
        String s = "";

        if (lhs.getPriority() < getPriority()) {
            s += "(" + lhs + ")";
        } else {
            s += lhs;
        }

        s += " " + getName() + " ";

        if (rhs.getPriority() < getPriority()) {
            s += "(" + rhs + ")";
        } else {
            s += rhs;
        }

        return s;
    }

    public boolean equals(Object other) {
        if (this == other) {
            return true;
        }
        if (other == null || getClass() != other.getClass()) {
            return false;
        }

        return lhs.equals(((Binary) other).lhs) && rhs.equals(((Binary) other).rhs);
    }

    public int hashCode() {
        return 31 * lhs.hashCode() + rhs.hashCode();
    }
}