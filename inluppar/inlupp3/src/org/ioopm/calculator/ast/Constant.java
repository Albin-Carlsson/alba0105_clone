package org.ioopm.calculator.ast;

public class Constant extends Atom {

    private final double value;

    public Constant(double value) {
        this.value = value;
    }

    public boolean isConstant() {
        return true;
    }

    public double getValue() {
        return this.value;
    }

    public String getName() {
        if (this.value == (int) this.value) {
            // return String.format("%d", (int) this.value);
            return String.valueOf((int) this.value);
        } else {
            // return String.format("%f", this.value);
            return String.valueOf(this.value);
        }
    }

    public boolean equals(Object other) {
        if (this == other) {
            return true;
        }
        if (other == null || getClass() != other.getClass()) {
            return false;
        }

        return equals((Constant) other);
    }

    public boolean equals(Constant other) {
        return this.value == other.value;
    }

    public int hashCode() {
        return 31 * (int) value;
    }

    public SymbolicExpression eval(Environment vars) {
        return this;
    }
}

