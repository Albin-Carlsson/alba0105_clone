package org.ioopm.calculator.ast;

public abstract class Unary extends SymbolicExpression {

    protected SymbolicExpression child;

    public Unary(SymbolicExpression child) {
        this.child = child;
    }

    public String toString() {
        return getName() + "(" + child.toString() + ")";
    }

    public boolean equals(Object other) {
        if (this == other) {
            return true;
        }
        if (other == null || getClass() != other.getClass()) {
            return false;
        }

        return child.equals(((Unary) other).child);
    }

    public int hashCode() {
        return 31 * child.hashCode();
    }
}
